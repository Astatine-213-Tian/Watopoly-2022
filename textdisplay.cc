#include <sstream>
#include "textdisplay.h"
#include "subject.h"
#include "termcodes.h"

using namespace std;

TextDisplay::TextDisplay() : displayInfo{vector<Info>(40)}, toPrint{vector<vector<string>>(40)} {}

void TextDisplay::notify(Subject &whoFrom) {
    Info infoFrom = whoFrom.getInfo();
    displayInfo[infoFrom.cellIndex] = infoFrom;
    setDisplayContents(infoFrom.cellIndex);
}

void TextDisplay::separateCellName(const string &cellName, vector<string> &cell) {
    istringstream iss{cellName};
    string read = "";
    string line = "|";
    int remain = cellWidth;
    while (iss >> read) {
        if (remain == cellWidth && (int)read.length() <= cellWidth) {
            line.append(read);
            remain -= read.length();
        } else if (remain < cellWidth) {
            if ((int)read.length() < remain) {
                line.append(" ");
                line.append(read);
                remain = remain - read.length() - 1;
            } else {
                line.append(remain, ' ');
                cell.emplace_back(line);
                line = "|";
                remain = cellWidth - read.length();
                line.append(read);
            }
        }
    }
    line.append(remain, ' ');
    cell.emplace_back(line);
}

void TextDisplay::separatePlayers(const vector<char>& p, vector<string> &cell) {
    int numPlayers = p.size();
    string line;

    line.assign("|");
    for (int j = 0; j < min(numPlayers, 4); j++) {
        line += p[j];
        if (j < 3) line.append(" ");
    }
    line.append(cellWidth - line.length() + 1, ' ');
    cell.emplace_back(line);

    line.assign("|");
    for (int j = 4; j < numPlayers; j++) {
        line += p[j];
        if (j < 8) line.append(" ");
    }
    line.append(cellWidth - line.length() + 1, ' ');
    cell.emplace_back(line);

    line.assign("|").append(cellWidth, '_');
    cell.emplace_back(line);
}

void TextDisplay::setDisplayContents(int index) {
    string line;
    string read = "";
    vector<string> cell;
    line = "|";
    int numImprove = displayInfo[index].numImprove;

    if (numImprove == -1) {
        separateCellName(displayInfo[index].cellName, cell);
        int size = cell.size();
        for (int j = 0; j < 3 - size; j++) {
            line.assign("|").append(cellWidth, ' ');
            cell.emplace_back(line);
        }
        separatePlayers(displayInfo[index].players, cell);
    } else {
        line.append(numImprove, 'I');
        line.append(cellWidth - numImprove, ' ');
        cell.emplace_back(line);
        line.assign("|");
        line.append(cellWidth, '-');
        cell.emplace_back(line);
        separateCellName(displayInfo[index].cellName, cell);
        separatePlayers(displayInfo[index].players, cell);
    }
    toPrint[index] = cell;

}

void TextDisplay::printMid(ostream &out, const int left, const int right) const {
    const string spaces(cellWidth, ' ');

    for (int i = 0; i < cellHeight; i++) {
        out << toPrint[left][i] << "|";
        for (int j = 0; j < 9; j++) out << spaces;
        out << spaces << " " << toPrint[right][i] << "|" << endl;
    }
}

ostream &operator<< (ostream &out, const TextDisplay& td) {
    const string spaces(td.cellWidth, ' ');
    const string cellBound(td.cellWidth, '_');
    string printLine;

    printLine.assign(td.cellWidth * 11 + 12, '_');
    out << printLine << endl;

    for (int i = 0; i < td.cellHeight; i++) {
        for (int j = 20; j <= 30; j++) {
            out << td.toPrint[j][i];
        }
        out << "|" << endl;
    }

    for (int i = 19; i >= 12; i--) {
        td.printMid(out, i, 50 - i);
    }

    for (int i = 0; i < td.cellHeight; i++) {
        // TODO underscore
        if (i == td.cellHeight - 1) out << UNDERLINE;

        out << td.toPrint[11][i] << "|";

        for (int j = 0; j < 9; j++) {
            if (i != td.cellHeight - 1) {
                out << spaces;
            } else {
                out << spaces;
            }
        }
        (i != td.cellHeight - 1) ? (out << spaces << " " ) : (out << spaces << "_");

        out << td.toPrint[39][i] << "|" << endl;
        if (i == td.cellHeight - 1) out << DEFAULT;
    }

    for (int i = 0; i < td.cellHeight; i++) {
        for (int j = 10; j >= 0; j--) {
            out << td.toPrint[j][i];
        }
        out << "|" << endl;
    }

    return out;
}