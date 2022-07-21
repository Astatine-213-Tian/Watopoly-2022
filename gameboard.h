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
  const int timsLineLocation = 10;

  void forward(int diceSum);
  int getTotalRollCups();

 public:
  GameBoard();
  void init();
  void addPlayer(const std::string &name, char displayChar, int position, int timsCups = 0, double money = 1500);
  void roll(); // save dice val, check dice, check num double
  void roll(int d1, int d2);
  void next(); // check can next,
  Player *getCurPlayer();
  Player *getPlayer(const std::string &name) const;
  Property *getPlayerProperty(const std::string &name, Player *player) const;
  AcademicBuilding *getPlayerAcademicBuilding(const std::string &name, Player *player) const;
  void trade(const std::string &name, const std::string &give, const std::string &receive);
  void trade(Player &player, double value, Property &property);
  void trade(Player &player, Property &p1, Property &p2);
  void trade(Player &player, Property &property, double value);
  void buyImprove(const std::string &name);
  void sellImprove(const std::string &name);
  void mortgage(const std::string &name);
  void unmortgage(const std::string &name);
  void assets(Player &p);
  void allAssets();
  void auction(int cellNum);
  bool isWin();
  void bankrupt();
};

#endif