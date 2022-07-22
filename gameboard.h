#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <vector>
#include <string>
#include <memory>
#include "controller.h"
#include "dice.h"
#include "cell.h"
#include "player.h"

class Property;
class AcademicBuilding;
class Observer;
class TextDisplay;

class GameBoard {
  std::vector<std::unique_ptr<Player>> players;
  std::vector<std::shared_ptr<Cell>> cells;
  std::vector<std::shared_ptr<Property>> properties;
  Player *curPlayer;
  std::unique_ptr<Dice> dice1;
  std::unique_ptr<Dice> dice2;
  const int timsLineIndex = 10;
  const int osapIndex = 0;

  std::unique_ptr<Controller> controller;
  std::shared_ptr<Observer> ob;

  void move(int distance);
  Property *getPlayerProperty(const std::string &name, Player *player) const;
  Property *getProperty(const std::string &name) const;
//  AcademicBuilding *getPlayerAcademicBuilding(const std::string &name, Player *player) const;
  Player *getPlayer(const std::string &name) const;
  void trade(Player &toWhom, double value, Property &property);
  void trade(Player &toWhom, Property &p1, Property &p2);
  void trade(Player &toWhom, Property &property, double value);
  double assetsValue();
  static void noImprovementCheck(Property *p) ;

 public:
  GameBoard();
  void init();
  void setController(Controller &c);
  void start();
  void setProperty(const std::string &name, const std::string &owner, int improvements, bool mortgaged);
  void addPlayer(const std::string &name, char displayChar, int position, int timsCups = 0, double money = 1500, bool isInTims = false, int timsRound = 0);
  void roll();
  void roll(int d1, int d2);
  void next();
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

  void setObserver(std::shared_ptr<Observer> o);
  friend std::ostream &operator<<(std::ostream &out, const GameBoard &gb);
};

#endif