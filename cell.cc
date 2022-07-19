#include "cell.h"

#include <utility>

using namespace std;

Cell::Cell(string name): name{std::move(name)} {}

string Cell::getName() { return name; }

Cell::~Cell() {}
