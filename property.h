#ifndef WATOPOLY__PROPERTY_H_
#define WATOPOLY__PROPERTY_H_

#include <string>
#include "cell.h"

class Player;

class Property : public Cell {
 protected:
  double cost;
  Player *owner;
  bool isMortgaged;
  bool isMortgageInterestPaid;
  virtual double calculateRent() const = 0;
  virtual double getValueWhenUnMortgage() const;
  virtual void loadImproveNum(int improveNum) const;

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
  double getTradableValue() const;
  void loadInfo(int improveNum, bool mortgaged);

  // For academic building only;
  virtual int getImproveNum() const;
  virtual double getImproveCost() const;
  virtual void addImprove() const;
  virtual void removeImprove() const;

  // override from Cell
  void passBy(Player &p) override;
  void landOnAction(Player &p) override;

};

#endif //WATOPOLY__PROPERTY_H_
