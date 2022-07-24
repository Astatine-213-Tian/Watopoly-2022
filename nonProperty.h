#ifndef _NONPROPERTY_H_
#define _NONPROPERTY_H_

#include "cell.h"
#include "info.h"

class NonProperty: public Cell {
 public:
  explicit NonProperty(const std::string&);
  int getImproveNum() const override;
};

#endif