#include "cell.h"

#include <utility>

using namespace std;

Cell::Cell(string name): name{std::move(name)}, owner{nullptr} {}

string Cell::getName() const { return name; }

Player *Cell::getOwner() const { return owner; }

Cell::~Cell() {}
