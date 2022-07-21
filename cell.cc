#include "cell.h"
#include "player.h"
#include <utility>

using namespace std;

Cell::Cell(string name): name{std::move(name)} {}

string Cell::getName() const { return name; }

void Cell::landOn(Player &p) {
    playersOnCell.emplace_back(p.getDisplayChar());
    landOnAction(p);
}

void Cell::leave(char p) {
    playersOnCell.erase(remove(playersOnCell.begin(), playersOnCell.end(), p), playersOnCell.end());
}

Cell::~Cell() = default;
