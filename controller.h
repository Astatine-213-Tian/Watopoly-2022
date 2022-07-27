#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <string>
#include <memory>

class GameBoard;

class Controller {
  GameBoard *g = nullptr;
  bool testMode;
//  void processUsualCmd(const std::string &cmd);
  void roll();
  void trade();
  void improve();
  void mortgage();
  void unmortgage();
  void payDebt();
  void bankrupt();
  void save();
  void leaveTims();
  static bool yesOrNoResponse();
  void printAssets(std::tuple<std::string, double, int, std::vector<std::string>> &info);

 public:
  Controller();
  void setGameBoard(GameBoard *gb);
  void addPlayers();
  void setToTestMode();
  void play();
  void next();
  void load(const std::string& filename);
  bool askTradeResponse(const std::string &toName, const std::string &curGive, const std::string &curReceive);
  static bool askBuyResponse(const std::string &propertyName, double cost);
  static bool askPayTuition();
  bool askUnMortgage(const std::string &receiverName, const std::string &propertyName);
  std::pair<std::string, double> auction(const std::vector<std::string> &properties);
};

#endif