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
  int curPlayerIndex;
  int rollTimes;
  bool canRoll;
  std::unique_ptr<Dice> dice1;
  std::unique_ptr<Dice> dice2;
  const int timsLineIndex = 10;
  const int osapIndex = 0;
  bool hasRolled;

  Controller *controller = nullptr;
  TextDisplay *td = nullptr;

  void move(int distance);
  Property *getPlayerProperty(const std::string &name, Player *player) const;
  Property *getProperty(const std::string &name) const;
  Player *getPlayer(const std::string &name) const;
  void trade(Player &toWhom, double value, Property &property);
  void trade(Player &toWhom, Property &p1, Property &p2);
  void trade(Player &toWhom, Property &property, double value);
  double tradableValue();
  double assetsValue();
  static void noImprovementCheck(Property *p) ;
  void processRoll();
  void moveToNextPlayer();
  int totalCups();

 public:
  GameBoard();
  void init();
  void setController(Controller *c);
  void setProperty(const std::string &name, const std::string &owner, int improvements, bool mortgaged);
  void addPlayer(const std::string &name, char displayChar, int position, int timsCups = 0, double money = 1500, bool isInTims = false, int timsRound = 0);
  std::pair<int, int> roll();
  void roll(int d1, int d2);
  void payTims();
  void useCups();
  bool inTimsLine();
  bool askToLeaveTims();
  bool mustLeaveTims();
  void next();
  std::string getCurPlayerName();
  std::vector<std::string> getAllPlayersName();
  std::unique_ptr<std::vector<std::tuple<std::string, char, int, double, int>>> getAllPlayersInfo();
  std::unique_ptr<std::vector<std::tuple<std::string, std::string, int, bool>>> getAllPropertiesInfo();
  void trade(const std::string &name, const std::string &give, const std::string &receive);
  void buyImprove(const std::string &name);
  void sellImprove(const std::string &name);
  void mortgage(const std::string &name);
  void unmortgage(const std::string &name);
  void payDebt();
  std::tuple<std::string, double, int, std::vector<std::string>> assets();
  std::tuple<std::string, double, int, std::vector<std::string>> assets(int playerIndex);
  int getTotalPlayersNum();
  bool isWin();
  void bankrupt();
  double debtAmount();

  void setTextDisplay(TextDisplay *td);
  friend std::ostream &operator<<(std::ostream &out, const GameBoard &gb);
};

#endif
