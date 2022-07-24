#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
class Property;
class AcademicBuilding;
class GameBoard;

class Player {
  std::string name;
  char displayChar;
  double cash;
  int numCup;
  int curLocation;
  int numToMove;
  bool goToOSAP;
  bool isInTimsLine;
  bool shouldMoveToTims;
  int rollTimes;
  bool canRoll;
  int numGym;
  int numRes;
  double debtAmount;
  Player *creditor;

 public:
  Player(std::string name, char displayChar, int timCups, double cash, int position, bool isInTimsLine, int timsLineRound);
  std::string getName() const;
  double getCash() const;
  char getDisplayChar() const;
  int getNumCup() const;
  int getLocation() const;
  void setLocation(int index);
  int getNumToMove() const;
  void setNumToMove(int num);
  void addCups(int num);
  void useCup();
  void pay(double value, Player *receiver = nullptr); // reject if not enough cash
  void forcePay(double value, Player *receiver = nullptr); // cause debt if not enough cash
  void receiveMoney(double value);
  bool inTimsLine() const;
  void sentToTimsLine(int index);
  void setShouldMoveToTims();
  bool getShouldMoveToTims() const;
  void setGoToOSAP(bool state);
  bool getGoToOSAP() const;
  void removeFromTimsLine();
  int getRollTimes() const;
  void addRollTimes();
  void initRollTimes();
  bool getRollState() const;
  void setRollState(bool state);
  double getDebtAmount() const;
  Player *getCreditor() const;
  void payDebt();
  void addGym();
  int getGym() const;
  void addRes();
  int getRes() const;
};

#endif