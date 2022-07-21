#include "player.h"
#include "academicBuilding.h"
#include "error.h"

using namespace std;

Player::Player(std::string name, char displayChar, int timCups, double cash, int position): name{name}, displayChar{displayChar}, cash{cash}, numCup{timCups}, curLocation{position}, isInTimsLine{false}, rollTimes{0}, canRoll{true} {}

string Player::getName() const{ return name; }

double Player::getCash() const{ return cash; }

int Player::getNumCup() const{ return numCup; }

void Player::move(const int index) { curLocation = index; }

void Player::sentToTimsLine(int timsIndex) {
    curLocation = timsIndex;
    shouldMoveToTims = false;
    isInTimsLine = true;
}

void Player::useCup() {
    if (numCup <= 0) throw NotEnoughCup{};
    numCup --;
}

void Player::receiveMoney(double value) { cash += value; }

bool Player::inTimsLine() const{ return isInTimsLine; }

void Player::removeFromTimsLine() { isInTimsLine = false; }

void Player::setShouldMoveToTims() { shouldMoveToTims = true; }

bool Player::getShouldMoveToTims() const { return shouldMoveToTims; }

int Player::getRollTimes() const{ return rollTimes; }

void Player::addRollTimes() { rollTimes++; }

void Player::initRollTimes() { rollTimes = 0; }

int Player::getLocation() const{ return curLocation; }

bool Player::getRollState() const{ return canRoll; }

void Player::setRollState(bool state) { canRoll = state; }

void Player::payMoney(double value) { cash -= value; }