#include "nonProperty.h"
#include "info.h"

NonProperty::NonProperty(const std::string&name): Cell{name} {}

Info &NonProperty::getInfo() {
    Info i;
    i.owner = '\0';
    i.numImprove = -1;
    i.cellIndex = cellIndex;
    i.cellName = name;
    i.players = playersOnCell;

    return i;
}