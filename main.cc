#include <iostream>
#include <string>
#include <sstream>
#include "controller.h"
#include "gameboard.h"
#include "textdisplay.h"

using namespace std;

void usage() {
    cerr << "Usage1: -load [filename]" << endl;
    cerr << "Usage2: -testing" << endl;
    cerr << "Usage3: -load [filename] -testing" << endl;
    cerr << "Usage4: -testing -load [filename]" << endl;
}

int main(int argc, char *argv[]) {
    Controller c;
    GameBoard gb;
    shared_ptr<TextDisplay> td;

    gb.setObserver(td);
    c.setGameBoard(gb);
    gb.setController(c);

    string cmd;
    string file;

    if (argc == 1) {
        c.play();
    } else if (argc == 3) {
        istringstream issCmd{argv[1]};
        istringstream issFile{argv[2]};
        issCmd >> cmd;
        issFile >> file;
        if (cmd == "-load") {
            c.load(file);
            c.play();
        } else {
            usage();
            return 1;
        }
    } else if (argc == 2) {
        istringstream issCmd{argv[1]};
        issCmd >> cmd;
        if (cmd == "-testing") {
            // TODO testing mode
        } else {
            usage();
            return 1;
        }
    } else if (argc == 4) {
        istringstream issCmd{argv[1]};
        issCmd >> cmd;
        if (cmd == "-load") {
            issCmd = istringstream{argv[2]};
            issCmd >> file;
            issCmd = istringstream{argv[3]};
            issCmd >> cmd;
            if (cmd == "-testing") {
                // load + test
            } else {
                usage();
                return 1;
            }
        } else if (cmd == "-testing") {
            issCmd = istringstream{argv[2]};
            issCmd >> cmd;
            if (cmd == "-load") {
                issCmd = istringstream{argv[3]};
                issCmd >> file;
                // load + test
            } else {
                usage();
                return 1;
            }
        } else {
            usage();
            return 1;
        }
    } else {
        usage();
        return 1;
    }
    return 0;
}