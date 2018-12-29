#include <jen/generator.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <utility/string_utility.h>
#include <filesystem>
#include <fstream>
#include <jen/serialization_generator.h>

DEFINE_string(fileList, "",
              "The list of files to process and generate definitions for. The files should be splitted using a ';' delimiter");
DEFINE_string(outputPath, ".", "The folder on which to output the generated files");
#define ERR_NO_FILES 1
DEFINE_string(includePath, "", "The list of directories to provide includes");


std::vector<shiroi::jen::IGenerator *> *createDefaultGenerators();

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
        LOG(INFO) << "Include directories (" << includeList.size() << ")";
        for (std::string &includeDir : includeList) {
            LOG(INFO) << '\'' << includeDir << '\'';
        }
    }
    LOG(INFO);
    auto clangArgs = std::vector<c_string>();
    clangArgs.push_back("-x");
    clangArgs.push_back("c++");
    for (std::string &includeDir : includeList) {
        clangArgs.push_back("-I");
        clangArgs.push_back(includeDir.c_str());
    }
    std::string argLine;
    auto totalArgs = clangArgs.size();
    for (int i = 0; i < totalArgs; ++i) {
        auto arg = clangArgs[i];
        argLine += arg;
        if (i != totalArgs - 1) {
            argLine += ' ';
        }
    }
    LOG(INFO) << "Clang args: '" << argLine << "'";
    auto generators = createDefaultGenerators();
    for (std::string &file : fileList) {
        std::filesystem::path filePath = std::filesystem::absolute(file);
        auto f = filePath.string();
        const char *filename = f.c_str();
        LOG(INFO) << "Processing file: " << filename;

        auto outputPath = outputDir / filePath.filename().replace_extension(".gen.inl");
        CXIndex index = clang_createIndex(false, false);
        try {
            auto sources = new shiroi::jen::GeneratedSources(filePath, clangArgs, generators);
            auto src = sources->toString();
            std::ofstream s(outputPath);
            s << src;
            s.close();
            delete sources;
        } catch (std::runtime_error &e) {
            LOG(FATAL) << e.what();
        }

    }
    delete generators;
}

std::vector<shiroi::jen::IGenerator *> *createDefaultGenerators() {
    auto vec = new std::vector<shiroi::jen::IGenerator *>();
    vec->push_back(new shiroi::jen::SerializationGenerator());
    return vec;
}