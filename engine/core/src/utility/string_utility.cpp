#include <utility/string_utility.h>
#include <glog/logging.h>

std::vector<std::string> split(std::string strToSplit, int8 delimeter) {
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

template<typename T>
std::string hex(T first, T last, bool use_uppercase, bool insert_spaces) {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    if (use_uppercase)
        ss << std::uppercase;
    while (first != last) {
        ss << std::setw(2) << static_cast<int>(*first++);
        if (insert_spaces && first != last)
            ss << " ";
    }
    return ss.str();
}
