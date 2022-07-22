#include <utility>
#include "academicBuilding.h"
#include "monopolyBlock.h"
#include "player.h"
#include "error.h"

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
    if (isMortgaged) throw PropertyStillMortgage{name};
    if (!mb->isMonopolized()) throw NotMonopolized{mb->getName()};
    if (mb->getImproveNum() >= 5) throw MaxImprove{mb->getName()};
    owner->pay(mb->getImproveCost());
    mb->addImprove();
}

void AcademicBuilding::removeImprove() const{
    if (mb->getImproveNum() <= 0) throw ZeroImprove{mb->getName()};
    mb->removeImprove();
    owner->receiveMoney(mb->getImproveCost() / 2);
}

void AcademicBuilding::loadImproveNum(int num) const {
    mb->initImproveNum(num);
}

double AcademicBuilding::getImproveCost() const {
    return mb->getImproveCost();
}

double AcademicBuilding::getValueWhenUnMortgage() const {
    return cost / 2 + getImproveCost() / 2 * getImproveNum();
}
