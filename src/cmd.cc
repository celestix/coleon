#include "cmd.h"

void Command::addFlag(std::string flagName, BaseFlag* flag) {
    flags[flagName] = flag;
}
