#include <utility>
#include "monopolyBlock.h"
#include "academicBuilding.h"

MonopolyBlock::MonopolyBlock(std::string name): name{std::move(name)}, buildings{}, numImprove{0} {}

void MonopolyBlock::addNewBuilding(AcademicBuilding &a) {
    buildings.emplace_back(&a);
}

int MonopolyBlock::getImprove() const {
    return numImprove;
}

void MonopolyBlock::addImprove() {
    ++numImprove;
}

void MonopolyBlock::removeImprove() {
    --numImprove;
}

bool MonopolyBlock::isMonopolizedBy(Player &p) const {
    for (auto b: buildings) {
        if (b->getOwner() != &p) {
            return false;
        }
    }

    return true;
}