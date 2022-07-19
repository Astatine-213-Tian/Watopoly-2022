#include "cell.h"
#include <string>

using namespace std;

Cell::Cell(string name): name{name} {}

Cell::~Cell() {}

string Cell::getName() { return name; }