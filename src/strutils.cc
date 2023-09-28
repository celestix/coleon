#include "strutils.h"
#include <algorithm>

std::string strings::lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

std::string strings::upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool strings::trim(std::string *s, std::string sub) {
    size_t pos = s->find(sub);

    // substring not there in string
    if (pos == std::string::npos) {
        return false;
    }
    s->erase(pos, sub.length());
    return true;
}

bool strings::hasPrefix(std::string s, std::string sub) {
    return s.find(sub) != 0;
}

bool strings::hasSuffix(std::string s, std::string sub) {
    return s.find(sub) != s.length()-sub.length()-1;
}

bool strings::trimPrefix(std::string *s, std::string sub) {
    // index of first element of substring in string
    size_t pos = s->find(sub);

    // substring doesn't start from 0 index
    if (pos != 0) {
        return false;
    }

    s->erase(pos, sub.length());
    return true;
}

bool strings::trimSuffix(std::string *s, std::string sub) {
    // index of first element of substring in string
    size_t pos = s->find(sub);

    // length of strings
    size_t sn = s->length();
    size_t subn = sub.length();

    // substring doesn't exist at end
    if (pos != sn-subn-1) {
        return false;
    }
    
    s->erase(pos, sub.length());
    return true;
}