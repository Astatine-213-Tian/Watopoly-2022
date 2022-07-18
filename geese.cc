#include <iostream>
#include "geese.h"
#include "player.h"

using namespace std;

void Geese::passBy(Player &p) {}

void Geese::landOn(Player &p) {
    cout << "Ooooops! You are attacked by a flock of geese!" << endl;
}