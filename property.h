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
  virtual void initImproveNum(int improveNum) const;
  void landOnAction(Player &p) override;
  // for gym and res to add num
  virtual void afterBoughtBy(Player &p);

 public:
  Property(std::string name, double cost);
  double getCost() const;
  void setMortgage();
  void setUnMortgage();
  bool getMortgageStatus() const;
  Player *getOwner() const;
  void setOwner(Player *p);
  double getTradableValue() const;
  void loadInfo(int improveNum, bool mortgaged);

  // For academic building only;
  // virtual double getImproveCost() const;
  virtual void addImprove();
  virtual void removeImprove();

  // override from Cell
  void passBy(Player &p) override;
  int getImproveNum() const override;

  void boughtBy(Player &p, double price);
};

#endif //WATOPOLY__PROPERTY_H_
