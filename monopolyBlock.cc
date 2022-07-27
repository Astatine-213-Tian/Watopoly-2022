#include <utility>
#include "monopolyBlock.h"
#include "academicBuilding.h"

MonopolyBlock::MonopolyBlock(std::string name, double improveCost): name{std::move(name)}, buildings{}, improveCost{improveCost}, numImprove{0} {}

void MonopolyBlock::addNewBuilding(AcademicBuilding *a) { buildings.emplace_back(a);}

double MonopolyBlock::getImproveCost() const { return improveCost; }

int MonopolyBlock::getImproveNum() const { return numImprove; }

void MonopolyBlock::addImprove() {
    ++numImprove;
    for (auto ab: buildings) {
        ab->notifyObservers();
    }
}

void MonopolyBlock::removeImprove() {
    --numImprove;
    for (auto ab: buildings) {
        ab->notifyObservers();
    }
}

bool MonopolyBlock::isMonopolized() const {
    if (buildings.empty()) return false;
    Player *monopoly = buildings[0]->getOwner();
    for (auto b: buildings) {
        if (b->getOwner() != monopoly) return false;
    }
    return true;
}

void MonopolyBlock::initImproveNum(int num) {
    numImprove = num;
}

std::string MonopolyBlock::getName() const { return name; }
