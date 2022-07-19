#ifndef WATOPOLY__PROPERTY_H_
#define WATOPOLY__PROPERTY_H_

#include <string>
#include "cell.h"

class Player;

class Property : public Cell {
 protected:
  double cost;
  Player *owner;
  virtual double calculateRent() const = 0;

 public:
  Property(std::string name, double cost);
  double getCost() const;
  Player *getOwner() const;
  void setOwner(Player *p);
  void passBy(Player &p) override;
  void landOn(Player &p) override;
};

#endif //WATOPOLY__PROPERTY_H_
