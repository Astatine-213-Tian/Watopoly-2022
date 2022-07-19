#include <vector>
#include "player.h"

using namespace std;

Player::Player(string name): name{name}, cash{0}, numCup{0}, isInTimsLine{false}, rollTimes{0} {}

string Player::getName() const{ return name; }

vector<Property *> Player::getProperties() const{ return properties; }

double Player::getCash() const{ return cash; }

int Player::getNumCup() const{ return numCup; }

void Player::useCup() { numCup --;}