#ifndef _CELL_H_
#define _CELL_H_

#include <string>
#include "vector"

class Player;

class Cell{
 protected:
  std::string name;
  std::vector<char> playersOnCell;
  virtual void landOnAction(Player &p) = 0;

 public:
  Cell(std::string name);
  virtual ~Cell();
  void leave(char p);
  virtual void passBy(Player &p) = 0;
  void landOn(Player &p);
  std::string getName() const;
};

#endif