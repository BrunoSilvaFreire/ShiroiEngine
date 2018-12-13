#include <utility/file_utility.h>
#include <glog/logging.h>
size_t shiroi::file_utility::getFileSize(const char *path) {
    std::ifstream file(path, std::ifstream::in | std::ifstream::binary);

    if (!file.is_open()) {
        LOG(WARNING) << "File not open";
        return 0;
    }

    file.seekg(0, std::ios::end);

    size_t fileSize = file.tellg();
    file.close();
    return fileSize;

}

size_t shiroi::file_utility::getFileSize(std::string &path) {
    return getFileSize(path.c_str());
}

size_t shiroi::file_utility::getFileSize(std::filesystem::path &path) {
    auto str = path.string();
    return getFileSize(str);
}