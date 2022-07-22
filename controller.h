#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <string>
#include <memory>

class GameBoard;

class Controller {
  GameBoard *g = nullptr;
//  void processUsualCmd(const std::string &cmd);
  void next();
  void roll();
  void trade();
  void improve();
  void mortgage();
  void unmortgage();
  void payDebt();
  void bankrupt();
  void save(std::string& filename);
  static bool yesOrNoResponse();

 public:
  Controller();
  void setGameBoard(GameBoard *gb);
  void addPlayers();
  void play();
  void load(const std::string& filename);
  static bool askTradeResponse(const std::string &curName, const std::string &toName, const std::string &curGive, const std::string &curReceive);
  static std::pair<std::string, double> auction(const std::vector<std::string> &properties, const std::vector<std::string> &playersName);
};

#endif