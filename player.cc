#include <vector>
#include "player.h"
#include "academicBuilding.h"
#include "error.h"

using namespace std;

Player::Player(string name): name{name}, cash{0}, numCup{0}, isInTimsLine{false}, rollTimes{0} {}

string Player::getName() const{ return name; }

//vector<Property *> Player::getProperties() const{ return properties; }

double Player::getCash() const{ return cash; }

int Player::getNumCup() const{ return numCup; }

void Player::move(const int index) { curLocation = index; }

void Player::useCup() { numCup --;}

void Player::receiveMoney(double value) { cash += value; }

// void Player::addProperty(Property &p) { properties.emplace_back(&p); }

// void Player::removeProperty(Property &p) { 
//     for (vector<Property *>::iterator it = properties.begin(); it != properties.end(); it++) {
//         if (*it == &p) {
//             properties.erase(it);
//             break;
//         }
//     }
// }

// bool Player::hasProperty(Property &p) const{ 
//     for (auto i : properties) {
//         if (i == &p) { return true; }
//     }
//     return false;
// }

bool Player::inTims() const{ return isInTimsLine; }

void Player::setToTimsLine() { isInTimsLine = true; }

void Player::removeFromTimsLine() { isInTimsLine = false; }

int Player::getRollTimes() const{ return rollTimes; }

void Player::addRollTimes() { rollTimes++; }

void Player::initRollTimes() { rollTimes = 0; }

int Player::getLocation() const{ return curLocation; }

bool Player::getRollState() const{ return canRoll; }

void Player::setRollState(bool state) { canRoll = state; }

bool Player::payMoney(double value) {
    // TODO payMoney
    return false;
}


void Player::buyImprove(AcademicBuilding &ab) {
    if (ab.getOwner() != this) {
        throw NotOwner{name, ab.getName()};
    } else if (!ab.isMonopolized()) {
        throw NotMonopolized{ab.getBlockName()};
    } else if (ab.getImproveNum() >= 5) {
        throw MaxImprove{ab.getBlockName()};
    }
    payMoney(ab.getImproveCost());
    ab.addImprove();
}


void Player::sellImprove(AcademicBuilding &ab) {
    if (ab.getOwner() != this) {
        throw NotOwner{name, ab.getName()};
    } else if (ab.getImproveNum() <= 0) {
        throw ZeroImprove{ab.getBlockName()};
    }
    ab.removeImprove();
    receiveMoney(ab.getImproveCost() / 2);
}
