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
  Property *getPlayerProperty(const std::string &name, Player *player) const;
  AcademicBuilding *getPlayerAcademicBuilding(const std::string &name, Player *player) const;
  Player *getPlayer(const std::string &name) const;
  void trade(Player &toWhom, double value, Property &property);
  void trade(Player &toWhom, Property &p1, Property &p2);
  void trade(Player &toWhom, Property &property, double value);
  static void noImprovementCheck(Property *p) ;

 public:
  GameBoard();
  void init();
  void addPlayer(const std::string &name, char displayChar, int position, int timsCups = 0, double money = 1500);
  void roll(); // save dice val, check dice, check num double
  void roll(int d1, int d2);
  void next(); // check can next,
  Player *getCurPlayer();
  void trade(const std::string &name, const std::string &give, const std::string &receive);
  void buyImprove(const std::string &name);
  void sellImprove(const std::string &name);
  void mortgage(const std::string &name);
  void unmortgage(const std::string &name);
  void payDebt();
  void assets(Player &p);
  void allAssets();
  void auction(int cellNum);
  bool isWin();
  void bankrupt();
  bool needDealWithDebt();
};

#endif