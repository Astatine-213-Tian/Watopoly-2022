#include <utility>
#include "academicBuilding.h"
#include "monopolyBlock.h"
#include "error.h"
#include "player.h"

AcademicBuilding::AcademicBuilding(std::string name, double cost, std::vector<double> tuition, MonopolyBlock &mb) :
    Property{std::move(name), cost}, tuition{std::move(tuition)}, mb{&mb} {
    mb.addNewBuilding(*this);
}

double AcademicBuilding::calculateRent() const {
    int improve = mb->getImproveNum();
    return tuition[improve];
}

int AcademicBuilding::getImproveNum() const {
    return mb->getImproveNum();
}

void AcademicBuilding::addImprove(Player &p) {
    if (&p != owner) {
        throw NotOwner{};
    } else if (!mb->isMonopolizedBy(p)) {
        throw NotMonopolized{};
    } else if (mb->getImproveNum() >= 5) {
        throw MaxImprove{};
    }
    p.payMoney(mb->getImproveCost());
    mb->addImprove();
}

void AcademicBuilding::sellImprove(Player &p) {
    if (&p != owner) {
        throw NotOwner{};
    } else if (mb->getImproveNum() <= 0) {
        throw ZeroImprove{};
    }
    mb->removeImprove();
    p.receiveMoney(mb->getImproveCost() / 2);
}


