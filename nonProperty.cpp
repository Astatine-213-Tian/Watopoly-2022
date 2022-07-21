#include "nonProperty.h"

NonProperty::NonProperty(const std::string&name): Cell{name} {}

double NonProperty::getValue() const { return 0; }