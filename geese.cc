#include <iostream>
#include "geese.h"
#include "player.h"

using namespace std;

Geese::Geese() : NonProperty{"Goose Nesting"} {}

void Geese::passBy(Player &p) {}

void Geese::landOnAction(Player &p) {
    cout << "Ooooops! You are attacked by a flock of geese!" << endl;
}