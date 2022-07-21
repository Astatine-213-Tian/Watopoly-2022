#ifndef WATOPOLY__MONOPOLYBLOCK_H_
#define WATOPOLY__MONOPOLYBLOCK_H_

#include <vector>
#include <string>

class AcademicBuilding;
class Player;

class MonopolyBlock {
  std::string name;
  std::vector<AcademicBuilding*> buildings;
  double improveCost;
  int numImprove;

 public:
  MonopolyBlock(std::string name, double improveCost);
  void addNewBuilding(AcademicBuilding *a);
  bool isMonopolized() const;
  std::string getName() const;
  double getImproveCost() const;
  int getImproveNum() const;
  void addImprove();
  void removeImprove();
  void initImproveNum(int num);
};

#endif //WATOPOLY__MONOPOLYBLOCK_H_
