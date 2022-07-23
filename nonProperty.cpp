#include "nonProperty.h"
#include "info.h"

NonProperty::NonProperty(const std::string&name): Cell{name} {}

Info NonProperty::getInfo() const {
    return Info{-1, cellIndex, name, playersOnCell};
}