#include <gflags/gflags.h>
#include <glog/logging.h>
#include <utility/string_utility.h>
#include <filesystem>
#include <fstream>
#include <jen/generation/cxxgenerator.h>
#include <jen/generation/serialization_generator.cpp>

DEFINE_string(fileList, "",
              "The list of files to process and generate definitions for. The files should be splitted using a ';' delimiter");
DEFINE_string(outputPath, ".", "The folder on which to output the generated files");
DEFINE_string(includePath, "", "The list of directories to provide includes, splitted using a ';' delimiter");

#define ERR_NO_FILES 1

#include <jen/reflection/cxxparser.h>

inline std::vector<shiroi::jen::generation::CXXGenerator *> createDefaultGenerators();

unsigned get_filesize(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    fseek(fp, 0, SEEK_END);
    auto size = ftell(fp);
    fclose(fp);
    return size;
}

CXSourceRange get_filerange(const CXTranslationUnit &tu, const char *filename) {
    CXFile file = clang_getFile(tu, filename);
    auto fileSize = get_filesize(filename);

    // get top/last location of the file
    CXSourceLocation topLoc = clang_getLocationForOffset(tu, file, 0);
    CXSourceLocation lastLoc = clang_getLocationForOffset(tu, file, fileSize);
    if (clang_equalLocations(topLoc, clang_getNullLocation()) ||
        clang_equalLocations(lastLoc, clang_getNullLocation())) {
        printf("cannot retrieve location\n");
        exit(1);
    }

    // make a range from locations
    CXSourceRange range = clang_getRange(topLoc, lastLoc);
    if (clang_Range_isNull(range)) {
        printf("cannot retrieve range\n");
        exit(1);
    }

    return range;
}

int main(int argc, char *args[]) {
    LOG(ERROR) << "Using CLang version '" << clang_getCString(clang_getClangVersion()) << "'";
    gflags::ParseCommandLineFlags(&argc, &args, false);
    auto fileList = shiroi::string_utility::split(FLAGS_fileList, ';');
    if (fileList.empty()) {
        LOG(ERROR) << "No files were provided. (You need to provide a list of files using '--fileList')";
        return ERR_NO_FILES;
    }

    auto outputDir = std::filesystem::absolute(std::filesystem::path(FLAGS_outputPath));
    LOG(INFO) << "Output folder: '" << outputDir.string() << '\'';
    LOG(INFO);
    LOG(INFO) << "Files to process (" << fileList.size() << "):";
    for (std::string &file : fileList) {
        LOG(INFO) << '\'' << file << '\'';
    }
    LOG(INFO);
    auto includeList = shiroi::string_utility::split(FLAGS_includePath, ';');
    if (includeList.empty()) {
        LOG(INFO)
                << "There are no include directories provided (You can specify them using the '--includePath {paths}' option, paths are separated by semi-colons)";
    } else {
        includeList.erase(std::remove_if(includeList.begin(), includeList.end(), [](std::string &str) {
            return str.empty();
        }), includeList.end());
        LOG(INFO) << "Include directories (" << includeList.size() << ")";
        for (std::string &includeDir : includeList) {
            LOG(INFO) << '\'' << includeDir << '\'';
        }
    }

    LOG(INFO);

    auto clangArgs = std::vector<std::string>();
    clangArgs.emplace_back("-x");
    clangArgs.emplace_back("c++");
    for (std::string &includeDir : includeList) {
        clangArgs.emplace_back("-I");
        clangArgs.emplace_back(includeDir.c_str());
    }
    std::vector<std::filesystem::path> paths(includeList.size());
    for (std::string &includeDir : includeList) {
        paths.push_back(std::filesystem::path(includeDir));
    }
    auto generators = createDefaultGenerators();
    for (std::string &file : fileList) {
        std::filesystem::path filePath = std::filesystem::absolute(file);
        auto f = filePath.string();
        const char *filename = f.c_str();
        LOG(INFO) << "Processing file: " << filename;


        try {
            auto unit = shiroi::jen::reflection::parse(filePath, paths);
            auto gen = createDefaultGenerators();
            auto &classes = unit.getClasses();
            for (const shiroi::jen::reflection::CXXClass &clazz : classes) {
                auto context = shiroi::jen::generation::CXXGenerationContext();
                for (shiroi::jen::generation::CXXGenerator * generator : gen) {
                    generator->generate(unit, clazz, context);
                }
                auto outputPath = outputDir / (clazz.getName() + ".gen.inl");

                std::ofstream s(outputPath);
                s << context;
                s.close();
            }

        } catch (std::runtime_error &e) {
            LOG(ERROR) << e.what();
        }
    }
}


std::vector<shiroi::jen::generation::CXXGenerator *> createDefaultGenerators() {
    auto vec = std::vector<shiroi::jen::generation::CXXGenerator *>();
    vec.push_back(new shiroi::jen::generation::SerializationGenerator());
    return vec;
}
