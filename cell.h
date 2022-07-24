#ifndef _CELL_H_
#define _CELL_H_

#include <string>
#include <vector>
#include "subject.h"
#include "info.h"

class Player;

class Cell: public Subject{
  int cellIndex;
  std::string name;
  std::vector<char> playersOnCell;
  virtual void landOnAction(Player &p) = 0;
  virtual int getImproveNum() const = 0;

 public:
  explicit Cell(std::string name);
  virtual ~Cell();
  Info getInfo() const;
  void leave(char p);
  virtual void passBy(Player &p) = 0;
  void initLandOn(Player &p);
  void landOn(Player &p);
  std::string getName() const;
  void setIndex(int idx);
};

#endif