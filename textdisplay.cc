#include <sstream>
#include "textdisplay.h"
#include "subject.h"

using namespace std;

void TextDisplay::notify(Subject &whoFrom) {
    Info infoFrom = whoFrom.getInfo();
    displayInfo.at(infoFrom.cellIndex) = infoFrom;
}

void TextDisplay::separateCellName(const string &cellName, vector<string> &cell) {
    istringstream iss{cellName};
    string read = "";
    string line = "|";
    int remain = cellWidth;
    while (iss >> read) {
        if (remain == cellWidth && read.length() <= cellWidth) {
            line.append(read);
            remain -= read.length();
        } else if (remain < cellWidth) {
            if (read.length() < remain) {
                line.append(" ");
                line.append(read);
                remain = remain - read.length() - 1;
            } else {
                line.append(remain, ' ');
                cell.emplace_back(line);
                line = "|";
                remain = cellWidth;
                line.assign(read);
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
    cell.emplace_back(line);
    line.assign("|");
    for (int j = 4; j < numPlayers; j++) {
        line += p[j];
        if (j < 8) line.append(" ");
    }
    cell.emplace_back(line);
    line.assign("|").append(cellWidth, '_');
    cell.emplace_back(line);
}

void TextDisplay::setDisplayContents() {
    string line;
    string read = "";
    int remain = cellWidth;

    for (int i = 0; i < (int)displayInfo.size(); i++) {
        vector<string> cell;
        line = "|";
        int numImprove = displayInfo[i].numImprove;
        
        if (numImprove == -1) {
            separateCellName(displayInfo[i].cellName, cell);
            for (int j = 0; j < 3 - (int)cell.size(); j++) {
                line.assign("|").append(cellWidth, ' ');
                cell.emplace_back(line);
            }
            separatePlayers(displayInfo[i].players, cell);

        } else {
            line.append(numImprove, 'I');
            line.append(cellWidth - numImprove, ' ');
            cell.emplace_back(line);
            line.assign("|");
            line.append(cellWidth, '-');
            cell.emplace_back(line);
            separateCellName(displayInfo[i].cellName, cell);
            separatePlayers(displayInfo[i].players, cell);
        }
        toPrint.emplace_back(cell);
    }
}

void TextDisplay::printMid(ostream &out, const int left, const int right) const {
    const string spaces(cellWidth, ' ');

    for (int i = 0; i < cellHeight; i++) {
        out << toPrint[left][i];
        for (int j = 0; j < 9; j++) out << spaces;
        out << toPrint[right][i] << "|" << endl;
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
        td.printMid(out, i, td.toPrint.size() - i);
    }

    for (int i = 0; i < td.cellHeight; i++) {
        out << td.toPrint[11][i];
        for (int j = 0; j < 9; j++) {
            if (i != td.cellHeight - 1) {
                out << spaces;
            } else {
                out << cellBound;
            }
        }
        out << td.toPrint[39][i] << "|" << endl;
    }

    for (int i = 0; i < td.cellHeight; i++) {
        for (int j = 10; j >= 0; j--) {
            out << td.toPrint[j][i];
        }
        out << "|" << endl;
    }

    return out;
}