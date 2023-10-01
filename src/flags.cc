#include <iostream>
#include "flags.h"


FlagType BoolFlag::type() {
    return FlagBool;
}

BoolFlag::BoolFlag() {
    value = false;
}

BoolFlag::BoolFlag(bool defaultValue) {
    value = defaultValue;
}

FlagType StringFlag::type() {
    return FlagString;
}

StringFlag::StringFlag() {
    value = "";
}

StringFlag::StringFlag(std::string defaultValue) {
    value = defaultValue;
}

FlagType IntFlag::type() {
    return FlagInt;
}

IntFlag::IntFlag() {
    value = 0;
}

IntFlag::IntFlag(int defaultValue) {
    value = defaultValue;
}

FlagType SizeTFlag::type() {
    return FlagSizeT;
}

SizeTFlag::SizeTFlag() {
    value = 0;
}

SizeTFlag::SizeTFlag(size_t defaultValue) {
    value = defaultValue;
}