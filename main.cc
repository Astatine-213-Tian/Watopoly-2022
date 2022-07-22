#include <iostream>
#include <string>
#include <fstream>
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

    if (argc == 1) c.addPlayers();

    for (int i = 1; i < argc; ++i) {
        string theArg = argv[i];
        if (theArg == "-load") {
            if (i + 1 < argc) {
                string filename = argv[++i];
                ifstream f(filename);
                if (f.good()) c.load(filename);
                else {
                    cerr << "File doesn't exist." << endl;
                    return 1;
                }
            } else {
                cerr << "Please provide a filename." << endl;
            }
        } else if (theArg == "-testing") {
            // TODO set testing
        } else if (theArg == "-enhanced") {
            // TODO set enhanced
        }
    }

    c.play();
    return 0;
}