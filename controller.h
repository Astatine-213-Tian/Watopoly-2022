#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <string>
#include <memory>

class GameBoard;
class Player;

class Controller {
  std::unique_ptr<GameBoard> g;

 public:
  Controller();
  bool askPlayerTradeResponse(Player *p);
  void play();
  void save(std::string filename);
  void load();
};

#endif