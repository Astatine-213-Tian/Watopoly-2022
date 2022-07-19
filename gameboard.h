#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <vector>
#include <string>
#include "dice.h"
#include "cell.h"
#include "player.h"

class Property;
class AcademicBuilding;

class GameBoard {
  std::vector<std::unique_ptr<Player>> players;
  std::vector<std::unique_ptr<Cell>> cells;
  Player *curPlayer;
  std::unique_ptr<Dice> dice1;
  std::unique_ptr<Dice> dice2;

  bool checkInTimsLine();

 public:
  GameBoard();
  void init();
  void roll(); // save dice val, check dice, check num double
  void roll(int d1, int d2);
  void next(); // check can next,
  Player *getCurPlayer();
  Player *getPlayer(const std::string& name) const;
  Property *getProperty(const std::string& name) const;
  AcademicBuilding *getAcademicBuilding(const std::string& name) const;
  void trade(Player &player, double value, Property &property);
  void trade(Player &player, Property &p1, Property &p2);
  void trade(Player &player, Property &property, double value);
  void buyImprove(AcademicBuilding &ab);
  void sellImprove(AcademicBuilding &ab);
  void mortgage(Property &p);
  void unmortgage(Property &p);
  void assets(Player &p);
  void allAssets();
  void auction(int cellNum);
  bool isWin();
  void bankrupt();
};

#endif