#include "player.h"
#include "error.h"

using namespace std;

Player::Player(std::string name, char displayChar, int timCups, double cash, int position, bool inTims, int timsRound):
    name{name}, displayChar{displayChar}, cash{cash}, numCup{timCups}, curLocation{position},
    isInTimsLine{inTims}, rollTimes{0}, canRoll{true}, inTimsRound{timsRound}, numGym{0}, numRes{0}, debtAmount{0}, creditor{nullptr} {}

string Player::getName() const{ return name; }

char Player::getDisplayChar() const { return displayChar; }

double Player::getCash() const{ return cash; }

int Player::getNumCup() const{ return numCup; }

void Player::setLocation(const int index) { curLocation = index; }

void Player::sentToTimsLine(int timsIndex) {
    curLocation = timsIndex;
    shouldMoveToTims = false;
    isInTimsLine = true;
    inTimsRound = 0;
    canRoll = false;
}

void Player::addCups(int num) {
    numCup += num;
}

void Player::useCup() {
    if (numCup <= 0) throw NotEnoughCup{};
    numCup--;
}

void Player::receiveMoney(double value) { cash += value; }

bool Player::inTimsLine() const{ return isInTimsLine; }

void Player::addTimsLineRound() { ++inTimsRound; }

int Player::getTimsLineRound() { return inTimsRound; }

void Player::removeFromTimsLine() {
    isInTimsLine = false;
    inTimsRound = 0;
}

void Player::setShouldMoveToTims() { shouldMoveToTims = true; }

bool Player::getShouldMoveToTims() const { return shouldMoveToTims; }

int Player::getRollTimes() const{ return rollTimes; }

void Player::addRollTimes() { rollTimes++; }

void Player::initRollTimes() { rollTimes = 0; }

int Player::getLocation() const{ return curLocation; }

bool Player::getRollState() const{
    return canRoll;
}

void Player::setRollState(bool state) { canRoll = state; }

void Player::pay(double value, Player *receiver) {
    if (cash < value) {
        throw NotEnoughCash{name};
    }
    cash -= value;
    if (receiver) receiver->receiveMoney(value);
}

void Player::forcePay(double value, Player *receiver) {
    if (cash < value) {
        if (receiver) receiver->receiveMoney(cash);
        cash = 0;
        debtAmount += value - cash;
        creditor = receiver;
        throw CauseDebt{name, debtAmount};
    }
    cash -= value;
    if (receiver) receiver->receiveMoney(value);
}

double Player::getDebtAmount() const { return debtAmount; }

Player* Player::getCreditor() const {
    return creditor;
}

void Player::payDebt() {
    pay(getDebtAmount(), creditor);
    creditor = nullptr;
}

int Player::getGym() const { return numGym; }

int Player::getRes() const { return numRes; }

void Player::addGym() { ++numGym; }

void Player::addRes() { ++numRes; }
