#include "textdisplay.h"
#include "subject.h"

using namespace std;

void TextDisplay::notify(Subject &whoFrom) {
    Info &from = whoFrom.getInfo();
    theDisplay.at(from.cellIndex) = from;
}

ostream &operator<< (ostream &out, const Observer& td) {
    // TODO print grid
    return out;
}