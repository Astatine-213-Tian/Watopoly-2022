#ifndef WATOPOLY__ERROR_H_
#define WATOPOLY__ERROR_H_

#include <stdexcept>
#include <utility>

class Error : public std::exception {
  std::string msg;
 public:
  explicit Error(std::string msg);
  const char * what() const noexcept override;
};

// throw when player is not the owner of a property
class NotOwner : public Error {
  std::string playerName;
  std::string propertyName;
 public:
  NotOwner(std::string playerName, std::string propertyName);
};

class NotMonopolized: public Error {
  std::string blockName;
 public:
  explicit NotMonopolized(std::string blockName);
};

class MaxImprove: public Error {
  std::string blockName;
 public:
  explicit MaxImprove(std::string blockName);
};


class ZeroImprove: public Error {
  std::string blockName;
 public:
  explicit ZeroImprove(std::string blockName);
};

class NotAcademicBuilding: public Error {
  std::string invalidName;
 public:
  explicit NotAcademicBuilding(const std::string &name);
};

class NotProperty: public Error {
  std::string invalidName;
 public:
  explicit NotProperty(const std::string &name);
};

class NotPlayer: public Error {
  std::string invalidName;
 public:
  explicit NotPlayer(const std::string &name);
};

class InvalidRoll: public Error {
 public:
  InvalidRoll();
};

#endif //WATOPOLY__ERROR_H_
