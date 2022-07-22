#ifndef _CELL_H_
#define _CELL_H_

#include <string>
#include <vector>
#include "subject.h"
#include "info.h"

class Player;

class Cell: public Subject{
 protected:
  char owner;
  int cellIndex;
  std::string name;
  std::vector<char> playersOnCell;
  virtual void landOnAction(Player &p) = 0;

 public:
  Cell(std::string name);
  virtual ~Cell();
  void leave(char p);
  virtual void passBy(Player &p) = 0;
  void initLandOn(Player &p);
  void landOn(Player &p);
  std::string getName() const;
  void setIndex(const int idx);
  virtual Info getInfo() const = 0;
};

#endif