#include <iostream>

namespace strings {
    // strings::lower returns a lowercase version of the string s.
    std::string lower(std::string s);

    // strings::upper returns an uppercase version of the string s.
    std::string upper(std::string s);

    // strings::contains returns true if the string s contains the substring sub.
    bool contains(std::string s, std::string sub);
    
    // strings::hasPrefix returns true if the string s starts with the substring sub.
    bool hasPrefix(std::string s, std::string sub);

    // strings::hasSuffix returns true if the string s ends with the substring sub.
    bool hasSuffix(std::string s, std::string sub);

    // strings::trim returns true if the string s contains the substring sub.
    bool trim(std::string *s, std::string sub);

    // strings::trimPrefix trims the prefix from the string s.
    // It also returns true if the string s starts with the substring sub.
    bool trimPrefix(std::string *s, std::string sub);
    
    // strings::trimSuffix trima the suffix from the string s.
    // It also returns true if the string s ends with the substring sub.
    bool trimSuffix(std::string *s, std::string sub);
};