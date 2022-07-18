#include <iostream>
#include <string>
#include <sstream>
#include "controller.h"
#include "gameboard.h"

using namespace std;

int main(int argc, char *argv[]) {
    Controller c;
    if (argc == 1) {
        c.init();
        c.play();
    } else if (argc == 3) {
        c.load();
        c.play();
    } else if (argc == 4) {
        istringstream die1{argv[2]};
        istringstream die2{argv[3]};
        int roll1;
        int roll2;
        die1 >> roll1;
        die2 >> roll2;
        // c.g->roll();
    } else {
        cerr << "Incorrect number of command line argumnents." << endl;
        return 1;
    }
    return 0;
}