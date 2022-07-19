#include <utility>
#include "monopolyBlock.h"
#include "academicBuilding.h"
#include "error.h"

MonopolyBlock::MonopolyBlock(std::string name, double improveCost): name{std::move(name)}, buildings{}, improveCost{improveCost}, numImprove{0} {}

void MonopolyBlock::addNewBuilding(AcademicBuilding *a) { buildings.emplace_back(a);}

double MonopolyBlock::getImproveCost() const { return improveCost; }

int MonopolyBlock::getImproveNum() const { return numImprove; }

void MonopolyBlock::addImprove() { ++numImprove; }

void MonopolyBlock::removeImprove() { --numImprove; }

bool MonopolyBlock::isMonopolized() const {
    if (buildings.empty()) return false;
    Player *monopoly = buildings[0]->getOwner();
    for (auto b: buildings) {
        if (b->getOwner() != monopoly) return false;
    }
    return true;
}

std::string MonopolyBlock::getName() const { return name; }