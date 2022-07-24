#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <vector>
#include <string>
#include <memory>
#include "controller.h"
#include "dice.h"
#include "cell.h"
#include "player.h"
#include "monopolyBlock.h"

class Property;
class AcademicBuilding;
class TextDisplay;

class GameBoard {
  std::vector<std::unique_ptr<Player>> players;
  std::vector<std::shared_ptr<Cell>> cells;
  std::vector<std::unique_ptr<MonopolyBlock>> blocks;
  std::vector<std::shared_ptr<Property>> properties;
  Player *curPlayer;
  int curPlayerIndex;
  std::unique_ptr<Dice> dice1;
  std::unique_ptr<Dice> dice2;
  const int timsLineIndex = 10;
  const int osapIndex = 0;

  Controller *controller = nullptr;
  TextDisplay *td = nullptr;

  void move(int distance);
  Property *getPlayerProperty(const std::string &name, Player *player) const;
  Property *getProperty(const std::string &name) const;
  Player *getPlayer(const std::string &name) const;
  void trade(Player &toWhom, double value, Property &property);
  void trade(Player &toWhom, Property &p1, Property &p2);
  void trade(Player &toWhom, Property &property, double value);
  double assetsValue();
  static void noImprovementCheck(Property *p) ;
  void assets(Player *p);

 public:
  GameBoard();
  void init();
  void setController(Controller *c);
  void start();
  void setProperty(const std::string &name, const std::string &owner, int improvements, bool mortgaged);
  void addPlayer(const std::string &name, char displayChar, int position, int timsCups = 0, double money = 1500, bool isInTims = false, int timsRound = 0);
  void roll(bool testMode = false, int d1 = 0, int d2 = 0);
  bool inTimsLine();
  void next();
  std::string getCurPlayerName();
  std::unique_ptr<std::vector<std::tuple<std::string, char, int, double, int>>> getAllPlayersInfo();
  std::unique_ptr<std::vector<std::tuple<std::string, std::string, int, bool>>> getAllPropertiesInfo();
  void trade(const std::string &name, const std::string &give, const std::string &receive);
  void buyImprove(const std::string &name);
  void sellImprove(const std::string &name);
  void mortgage(const std::string &name);
  void unmortgage(const std::string &name);
  void payDebt();
  void assets();
  void allAssets();
  bool isWin();
  void bankrupt();
  bool needDealWithDebt();

  void setTextDisplay(TextDisplay *td);
  friend std::ostream &operator<<(std::ostream &out, const GameBoard &gb);
};

#endif