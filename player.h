#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
class Property;
class AcademicBuilding;

class Player {
  std::string name;
  char displayChar;
  //std::vector<Property *> properties;
  double cash;
  int numCup;
  int curLocation;
  bool isInTimsLine;
  bool shouldMoveToTims;
  int rollTimes;
  bool canRoll;
  int numGym;
  int numRes;
  double debtAmount;
  Player *creditor;

 public:
  Player(std::string name, char displayChar, int timCups, double cash, int position);
  std::string getName() const;
  double getCash() const;
  int getNumCup() const;
  void move(int index);
  void addCups(int num);
  void useCup();
  void pay(double value, Player *receiver = nullptr); // reject if not enough cash
  void forcePay(double value, Player *receiver = nullptr); // cause debt if not enough cash
  void receiveMoney(double value);
  bool inTimsLine() const;
  void sentToTimsLine(int timsIndex);
  void setShouldMoveToTims();
  bool getShouldMoveToTims() const;
  void removeFromTimsLine();
  int getRollTimes() const;
  void addRollTimes();
  void initRollTimes();
  int getLocation() const;
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