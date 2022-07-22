#include <iostream>
#include <string>
#include <sstream>
#include "controller.h"
#include "gameboard.h"

using namespace std;

int main(int argc, char *argv[]) {
    Controller c;

    // gamebaord g
    // display td
    // c.setgameboard
    // c ctor
    // g.setcontroller
    // g.setobserver
    // g + set
    // g.init()
    // cell - setindex
    // init index - attach
    // c.play()

    if (argc == 1) {
        c.addPlayers();
        c.play();
    } else if (argc == 3) {
        c.load(argv[2]);
        c.play();
    } else if (argc == 2) {
        // TODO testing mode
    } else {
        cerr << "Incorrect number of command line arguments." << endl;
        return 1;
    }
    return 0;
}