#ifndef WATOPOLY__ERROR_H_
#define WATOPOLY__ERROR_H_

#include <stdexcept>
#include <utility>

class Player;
class Property;

class Error : public std::exception {};

// throw when player is not the owner of a property
class NotOwner : public Error {
  std::string playerName;
  std::string propertyName;
 public:
  NotOwner(std::string playerName, std::string propertyName);
};

NotOwner::NotOwner(std::string playerName, std::string propertyName) : playerName{std::move(playerName)}, propertyName{std::move(propertyName)} {}

// throw when player try to improve an un-monopolized block
class NotMonopolized: public Error {};
// throw when a block reaches maximum improvement number
class MaxImprove: public Error {};
// throw when a block cannot be removed more improvement
class ZeroImprove: public Error {};

#endif //WATOPOLY__ERROR_H_
