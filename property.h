#ifndef WATOPOLY__PROPERTY_H_
#define WATOPOLY__PROPERTY_H_

#include <string>
#include "cell.h"
#include "info.h"

class Player;

class Property : public Cell {
 protected:
  double cost;
  Player *owner;
  bool isMortgaged;
  bool isMortgageInterestPaid;
  int numImprove;
  virtual double calculateRent() const = 0;
  virtual double getValueWhenUnMortgage() const;

 public:
  Property(std::string name, double cost);
  double getCost() const;
  double getUnMortgageCost() const;
  void setMortgage();
  void setUnMortgage();
  void setMortgageInterestPaid();
  bool getMortgageStatus() const;
  Player *getOwner() const;
  void setOwner(Player *p);

  virtual int getImproveNum() const;
  virtual double getImproveCost() const;
  virtual void addImprove() const;
  virtual void removeImprove() const;
  virtual void initImprove(int improveNum) const;

  void passBy(Player &p) override;
  void landOnAction(Player &p) override;
  double getTradableValue() const;

  Info &getInfo() override;
};

#endif //WATOPOLY__PROPERTY_H_
