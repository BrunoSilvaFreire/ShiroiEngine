#include <utility/string_utility.h>
#include <glog/logging.h>

std::vector<std::string> shiroi::string_utility::split(std::string strToSplit, int8 delimeter) {
    std::string item;
    std::vector<std::string> splittedStrings;
    for (char c : strToSplit) {
        if (c == delimeter) {
            splittedStrings.push_back(item);
            item = "";
        } else {
            item += c;
        }
    }
    if (!item.empty()) {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}


std::string shiroi::string_utility::join(
        const std::vector<std::string> &strings,
        const std::string &separator,
        std::function<std::string(std::string)> transform
) {
    std::string str;
    auto end = strings.size();
    for (int i = 0; i < end; ++i) {
        auto s = strings[i];
        if (transform == nullptr) {
            str += s;
        } else {
            str += transform(str);
        }
        if (i != end - 1) {
            str += separator;
        }
    }
    return str;
}
