#ifndef WATOPOLY__ACADEMICBUILDING_H_
#define WATOPOLY__ACADEMICBUILDING_H_

#include <vector>
#include "property.h"

class MonopolyBlock;
class AcademicBuilding : public Property {
  float improveCost;
  std::vector<float> tuition;
  MonopolyBlock *mb;
 public:
  AcademicBuilding(std::string name, float cost, std::vector<float> tuition, MonopolyBlock &mb);
  float calculateRent(Player &p) const override;
  int getImprove() const;
  bool addImprove(Player &p);
  bool removeImprove(Player &p);
};

#endif //WATOPOLY__ACADEMICBUILDING_H_
