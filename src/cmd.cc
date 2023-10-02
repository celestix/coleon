#include "cmd.h"

void Command::addFlag(std::string flagName, BaseFlag* flag) {
    if (flag == NULL) {
        return;
    }
    int n = flagName.length();
    if (n > maxField) {
        maxField = n;
    }
    flags[flagName] = flag;
}

BaseFlag* Command::getFlag(std::string flagName) {
    return flags[flagName];
}