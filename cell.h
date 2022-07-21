#ifndef _CELL_H_
#define _CELL_H_

#include <string>

class Player;

class Cell{
 protected:
  std::string name;
  Player *owner;

 public:
  Cell(std::string name);
  virtual ~Cell();
  virtual void passBy(Player &p) = 0;
  virtual void landOn(Player &p) = 0;
  std::string getName() const;
  Player *getOwner() const;
  virtual double getValue() const = 0;
};

#endif