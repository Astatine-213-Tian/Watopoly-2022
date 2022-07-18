#ifndef WATOPOLY__PROPERTY_H_
#define WATOPOLY__PROPERTY_H_

#include <string>
#include "cell.h"

class Player;

class Property : Cell {
  float cost;
  Player *owner;
 public:
  Property(std::string name, float cost);
  float getCost() const;
  Player *getOwner() const;
  void setOwner(Player *p);
  virtual float calculateRent(Player &p) const = 0;
  void passBy(Player &p) override;
  void landOn(Player &p) override;
};

#endif //WATOPOLY__PROPERTY_H_
