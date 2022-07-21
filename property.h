#ifndef WATOPOLY__PROPERTY_H_
#define WATOPOLY__PROPERTY_H_

#include <string>
#include "cell.h"

class Player;

class Property : public Cell {
 protected:
  double cost;
  bool isMortgaged;
  bool isMortgageInterestPaid;
  virtual double calculateRent() const = 0;
  virtual double getAllPossibleReturn () const;

 public:
  Property(std::string name, double cost);
  double getCost() const;
  double getUnMortgageCost() const;
  void setMortgage();
  void setUnMortgage();
  void setMortgageInterestPaid();
  bool getMortgageStatus() const;
  void setOwner(Player *p);
  void passBy(Player &p) override;
  void landOn(Player &p) override;
  double getValue() const override;
};

#endif //WATOPOLY__PROPERTY_H_
