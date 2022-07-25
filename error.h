#ifndef WATOPOLY__ERROR_H_
#define WATOPOLY__ERROR_H_

#include <stdexcept>
#include <utility>

class Error : public std::exception {
 protected:
  std::string msg;
 public:
  explicit Error(const std::string &msg);
  const char * what() const noexcept override;
};

// throw when player is not the owner of a property
class NotOwner : public Error {
  std::string playerName;
  std::string propertyName;
 public:
  NotOwner(const std::string &playerName, const std::string &propertyName);
};

class NotMonopolized: public Error {
  std::string blockName;
 public:
  explicit NotMonopolized(const std::string &blockName);
};

class MaxImprove: public Error {
  std::string blockName;
 public:
  explicit MaxImprove(const std::string &blockName);
};


class ZeroImprove: public Error {
  std::string blockName;
 public:
  explicit ZeroImprove(const std::string &blockName);
};

class NotAcademicBuilding: public Error {
  std::string invalidName;
 public:
  explicit NotAcademicBuilding(const std::string &name);
};

class NotProperty: public Error {
  std::string invalidName;
 public:
  explicit NotProperty(const std::string &name);
};

class NotPlayer: public Error {
  std::string invalidName;
 public:
  explicit NotPlayer(const std::string &name);
};

class PropertyStillMortgage: public Error {
  std::string propertyName;
 public:
  explicit PropertyStillMortgage(const std::string &name);
};

class PropertyStillUnMortage: public Error {
  std::string propertyName;
 public:
  explicit PropertyStillUnMortage(const std::string &name);
};

class BuildingStillWithImprove: public Error {
  std::string propertyName;
 public:
  explicit BuildingStillWithImprove(const std::string &name);
};

class TradeMoneyWithMoney: public Error {
 public:
  TradeMoneyWithMoney();
};

class NotEnoughCup: public Error {
 public:
  NotEnoughCup();
};

class NotEnoughCash: public Error {
 public:
  explicit NotEnoughCash(const std::string &playerName);
};

class CauseDebt: public Error {
 public:
  CauseDebt(const std::string &playerName, double debtAmount);
};

class InvalidRoll : public Error {
 public:
  InvalidRoll();
};

class StillCanRoll: public Error {
 public:
  StillCanRoll();
};

class HasDebt: public Error {
 public:
  HasDebt();
};

class InvalidBankrupt : public Error {
 public:
  InvalidBankrupt();
};


#endif //WATOPOLY__ERROR_H_
