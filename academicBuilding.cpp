#include <utility>
#include "academicBuilding.h"
#include "monopolyBlock.h"
#include "player.h"

AcademicBuilding::AcademicBuilding(std::string name, double cost, std::vector<double> tuition, MonopolyBlock &mb) :
    Property{std::move(name), cost}, tuition{std::move(tuition)}, mb{&mb} {
    mb.addNewBuilding(this);
}

double AcademicBuilding::calculateRent() const {
    int improve = mb->getImproveNum();
    if (mb->isMonopolized() && improve == 0) {
        return tuition[0] * 2;
    }
    return tuition[improve];
}

int AcademicBuilding::getImproveNum() const {
    return mb->getImproveNum();
}

void AcademicBuilding::addImprove() const{
    mb->addImprove();
}

void AcademicBuilding::removeImprove() const{
    mb->removeImprove();
}

bool AcademicBuilding::isMonopolized() const {
    return mb->isMonopolized();
}

std::string AcademicBuilding::getBlockName() const {
    return mb->getName();
}

double AcademicBuilding::getImproveCost() const {
    return mb->getImproveCost();
}

double AcademicBuilding::getAllPossibleReturn() const {
    return cost / 2 + getImproveCost() * getImproveNum();
}
