#include <vector>
#include "player.h"

using namespace std;

Player::Player(string name): name{name}, cash{0} {}

string Player::getName() { return name; }

vector<Property *> Player::getProperties() { return properties; }

float Player::getCash() { return cash; }

int Player::getNumCup() { return numCup; }

void Player::useCup() { numCup --;}