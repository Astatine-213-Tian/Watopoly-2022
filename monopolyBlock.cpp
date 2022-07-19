#include <utility>
#include "monopolyBlock.h"
#include "academicBuilding.h"
#include "error.h"

MonopolyBlock::MonopolyBlock(std::string name, double improveCost): name{std::move(name)}, buildings{}, improveCost{improveCost}, numImprove{0} {}

void MonopolyBlock::addNewBuilding(AcademicBuilding *a) { buildings.emplace_back(a);}

double MonopolyBlock::getImproveCost() const { return improveCost; }

int MonopolyBlock::getImproveNum() const { return numImprove; }

void MonopolyBlock::addImprove() {
    if (numImprove >= 5) {
        throw MaxImprove{name};
    }
    ++numImprove;
}

void MonopolyBlock::removeImprove() {
    if (numImprove <= 0) {
        throw ZeroImprove{name};
    }
    --numImprove;
}

void MonopolyBlock::checkMonopoly() const {
    if (buildings.empty()) return;
    Player *monopoly = buildings[0]->getOwner();
    for (auto b: buildings) {
        if (b->getOwner() != monopoly) throw NotMonopolized{name};
    }
}

std::string MonopolyBlock::getName() const { return name; }