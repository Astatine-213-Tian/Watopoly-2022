#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <vector>
#include <string>
#include "observer.h"
#include "info.h"
class Subject;

class TextDisplay: public Observer {
    std::vector<Info> displayInfo;
    std::vector<std::vector<std::string> > toPrint;
    const int cellWidth = 7;
    const int cellHeight = 6;

    void separateCellName(const std::string &cellName, std::vector<std::string> &cell);
    void separatePlayers(const std::vector<char>& p, std::vector<std::string> &cell);
 public:
    void notify(Subject &whoFrom) override;
    void setDisplayContents();

    void printMid(std::ostream &out, const int left, const int right) const;
    friend std::ostream &operator<< (std::ostream &out, const TextDisplay &td);
};

#endif