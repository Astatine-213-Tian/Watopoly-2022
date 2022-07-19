#include <utility>
#include "academicBuilding.h"
#include "monopolyBlock.h"

AcademicBuilding::AcademicBuilding(std::string name, float cost, std::vector<float> tuition, MonopolyBlock &mb) :
    Property{std::move(name), cost}, tuition{std::move(tuition)}, mb{&mb} {
    mb.addNewBuilding(*this);
}

float AcademicBuilding::calculateRent(Player &p) const {
    int improve = mb->getImprove();
    return tuition[improve];
}

int AcademicBuilding::getImprove() const {
    return mb->getImprove();
}

bool AcademicBuilding::addImprove(Player &p) {
    if (&p != owner || !mb->isMonopolizedBy(p) || mb->getImprove() >= 5) return false;
    mb->addImprove();
    return true;
}

bool AcademicBuilding::removeImprove(Player &p) {
    if (&p != owner || mb->getImprove() <= 0) return false;
    mb->removeImprove();
    return true;
}


