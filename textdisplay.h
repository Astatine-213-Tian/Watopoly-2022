#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <vector>
#include <string>
#include "observer.h"
#include "info.h"
class Subject;

class TextDisplay: public Observer {
    std::vector<Info> theDisplay;
 public:
    void notify(Subject &whoFrom) override;

    friend std::ostream &operator<< (std::ostream out, const TextDisplay &td);
};

#endif