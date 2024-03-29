#include "cell.h"
#include "player.h"
#include <utility>
#include <algorithm>

using namespace std;

Cell::Cell(string name): name{std::move(name)} {}

string Cell::getName() const { return name; }

void Cell::setIndex(const int idx) { cellIndex = idx; }

void Cell::initLandOn(Player &p) {
    playersOnCell.emplace_back(p.getDisplayChar());
    notifyObservers();
}

void Cell::landOn(Player &p) {
    playersOnCell.emplace_back(p.getDisplayChar());
    landOnAction(p);
    notifyObservers();
}

void Cell::leave(char p) {
    playersOnCell.erase(remove(playersOnCell.begin(), playersOnCell.end(), p), playersOnCell.end());
    notifyObservers();
}

Info Cell::getInfo() const {
    return Info{getImproveNum(), cellIndex, name, playersOnCell};
}

Cell::~Cell() = default;
