#ifndef WATOPOLY__ACADEMICBUILDING_H_
#define WATOPOLY__ACADEMICBUILDING_H_

#include <vector>
#include "property.h"


class MonopolyBlock;
class AcademicBuilding : public Property {
  std::vector<double> tuition;
  MonopolyBlock *mb;
  double calculateRent() const override;
  double getValueWhenUnMortgage() const override;
 public:
  AcademicBuilding(std::string name, double cost, std::vector<double> tuition, MonopolyBlock &mb);
  int getImproveNum() const override;
  double getImproveCost() const override;
  void addImprove() const override;
  void removeImprove() const override;
  void initImprove(int improveNum) const override;
//  bool isMonopolized() const;
//  std::string getBlockName() const;
};

#endif //WATOPOLY__ACADEMICBUILDING_H_
