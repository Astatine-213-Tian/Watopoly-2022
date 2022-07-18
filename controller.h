#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <string>

class GameBoard;
class Controller {
    GameBoard *g;

    public:
    Controller();
    ~Controller();
    void init();
    void play();
    void save(std::string filename);
    void load();
};

#endif