#include <iostream>
#include "flags.h"


FlagType BoolFlag::type() {
    return FlagBool;
}

bool BoolFlag::isRequired() {
    return false;
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

bool StringFlag::isRequired() {
    return required;
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

bool IntFlag::isRequired() {
    return required;
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

bool SizeTFlag::isRequired() {
    return required;
}

SizeTFlag::SizeTFlag() {
    value = 0;
}

SizeTFlag::SizeTFlag(size_t defaultValue) {
    value = defaultValue;
}