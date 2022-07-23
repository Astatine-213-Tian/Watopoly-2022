#ifndef _INFO_H_
#define _INFO_H_

#include <vector>
#include <string>

struct Info {
  int numImprove;
  int cellIndex;
  std::string cellName;
  std::vector<char> players;
};

#endif