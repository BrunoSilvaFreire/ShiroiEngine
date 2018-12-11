#include <gflags/gflags.h>
#include <glog/logging.h>
#include <filesystem>
#include <parser.h>
#include <iostream>
#include <fstream>

DEFINE_string(fileList, "",
              "The list of files to process and generate definitions for. The files should be splitted using a ';' delimiter");
DEFINE_string(outputPath, ".", "The folder on which to output the generated files");
#define ERR_NO_FILES 1

int main(int argc, char *args[]) {
    gflags::ParseCommandLineFlags(&argc, &args, false);
    auto files = FLAGS_fileList;
    auto list = split(files, ';');
    if (list.empty()) {
        LOG(ERROR) << "No files were provided. (You need to provide a list of files using '--fileList')";
        return ERR_NO_FILES;
    }

    auto outputDir = std::filesystem::absolute(std::filesystem::path(FLAGS_outputPath));
    LOG(INFO) << "Output folder: '" << outputDir.string() << '\'';
    LOG(INFO) << "Files to process:";
    for (std::string &file : list) {
        LOG(INFO) << '\'' << file << '\'';
    }
    for (std::string &file : list) {
        std::filesystem::path filePath = std::filesystem::absolute(file);
        LOG(INFO) << "Processing file: " << filePath;
        std::ifstream stream(filePath.string());
        std::stringstream source;
        int8 c;
        while (stream.get(c)) {
            source << c;
        }

        std::string outputFilePath = outputDir.string() + "\\" + filePath.filename().replace_extension( ".gen.inl").string();
        auto finalSource = source.str();
        LOG(INFO) << outputFilePath;
        generateTo(finalSource, std::filesystem::path(outputFilePath));
    }
}