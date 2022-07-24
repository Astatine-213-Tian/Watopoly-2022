#include "nonProperty.h"
#include "info.h"

NonProperty::NonProperty(const std::string&name): Cell{name} {}

int NonProperty::getImproveNum() const { return -1; }

double NonProperty::getCost() const { return 0; }

Player *NonProperty::getOwner() const { return nullptr; }
