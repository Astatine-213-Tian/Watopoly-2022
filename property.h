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
  virtual double calculateRent() const = 0;
  virtual double getImproveValue() const;
  virtual void loadImproveNum(int improveNum) const;

 public:
  Property(std::string name, double cost);
  double getCost() const override;
  void setMortgage();
  void setUnMortgage();
  bool getMortgageStatus() const;
  Player *getOwner() const override;
  void setOwner(Player *p);
  double getTradableValue() const;
  void loadInfo(int improveNum, bool mortgaged);

  // For academic building only;
  int getImproveNum() const override;
//  virtual double getImproveCost() const;
  virtual void addImprove();
  virtual void removeImprove();

  // override from Cell
  void passBy(Player &p) override;
  void landOnAction(Player &p) override;
};

#endif //WATOPOLY__PROPERTY_H_
