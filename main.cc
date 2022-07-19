#include <iostream>
#include <string>
#include <sstream>
#include "controller.h"
#include "gameboard.h"

using namespace std;

int main(int argc, char *argv[]) {
    Controller c;
    if (argc == 1) {
        c.play();
    } else if (argc == 3) {
        c.load();
        c.play();
    } else if (argc == 2) {
        // TODO testing mode
    } else {
        cerr << "Incorrect number of command line arguments." << endl;
        return 1;
    }
    return 0;
}