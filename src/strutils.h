#include <iostream>

namespace strings {
    std::string lower(std::string s);
    std::string upper(std::string s);
    bool hasPrefix(std::string s, std::string sub);
    bool hasSuffix(std::string s, std::string sub);
    bool trim(std::string *s, std::string sub);
    bool trimPrefix(std::string *s, std::string sub);
    bool trimSuffix(std::string *s, std::string sub);
};