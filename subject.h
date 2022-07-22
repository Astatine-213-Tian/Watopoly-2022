#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include <memory>
#include "info.h"
class Observer;

class Subject {
    std::vector<Observer *> observers;

 public:
    void attach (Observer *ob);
    void notifyObservers();
    virtual Info &getInfo() = 0;
    virtual ~Subject() = 0;
};

#endif