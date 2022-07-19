#ifndef WATOPOLY__MONOPOLYBLOCK_H_
#define WATOPOLY__MONOPOLYBLOCK_H_

#include <vector>
#include <string>

class AcademicBuilding;
class Player;

class MonopolyBlock {
  std::string name;
  std::vector<AcademicBuilding*> buildings;
  int numImprove;

 public:
  explicit MonopolyBlock(std::string name);
  void addNewBuilding(AcademicBuilding &a);
  bool isMonopolizedBy(Player &p) const;
  int getImprove() const;
  void addImprove();
  void removeImprove();
};

#endif //WATOPOLY__MONOPOLYBLOCK_H_
