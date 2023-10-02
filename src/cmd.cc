#include "cmd.h"

void Command::addFlag(std::string flagName, BaseFlag* flag) {
    if (flag == NULL) {
        return;
    }
    flags[flagName] = flag;
}

BaseFlag* Command::getFlag(std::string flagName) {
    return flags[flagName];
}