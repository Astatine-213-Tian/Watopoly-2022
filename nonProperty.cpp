#include "nonProperty.h"
#include "info.h"

NonProperty::NonProperty(const std::string&name): Cell{name} {}

Info NonProperty::getInfo() {
    return Info{'\0', -1, cellIndex, name, playersOnCell};
}