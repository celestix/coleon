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

BoolFlag::BoolFlag(bool defaultValue, std::string desc) {
    value = defaultValue;
    description = desc;
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

StringFlag::StringFlag(std::string defaultValue, std::string desc) {
    value = defaultValue;
    description = desc;
}

StringFlag::StringFlag(std::string defaultValue, std::string desc, bool req) {
    value = defaultValue;
    description = desc;
    required = req;
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

IntFlag::IntFlag(int defaultValue, std::string desc) {
    value = defaultValue;
    description = desc;
}

IntFlag::IntFlag(int defaultValue, std::string desc, bool req) {
    value = defaultValue;
    description = desc;
    required = req;
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

SizeTFlag::SizeTFlag(size_t defaultValue, std::string desc) {
    value = defaultValue;
    description = desc;
}

SizeTFlag::SizeTFlag(size_t defaultValue, std::string desc, bool req) {
    value = defaultValue;
    description = desc;
    required = req;
}
