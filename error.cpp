#include <string>
#include <utility>
#include "error.h"
using namespace std;

Error::Error(std::string msg) : msg{move(msg)} {}
const char *Error::what() const noexcept { return msg.c_str(); }

NotOwner::NotOwner(string playerName, string propertyName) :
    Error{"Player " + playerName + " does not own " + propertyName}, playerName{move(playerName)}, propertyName{move(propertyName)} {}


NotMonopolized::NotMonopolized(string blockName) :
    Error{blockName + " is not monopolized "}, blockName{move(blockName)} {}

MaxImprove::MaxImprove(std::string blockName) :
    Error{blockName + " has reached maximal improvement number"}, blockName{std::move(blockName)} {}

ZeroImprove::ZeroImprove(std::string blockName) :
    Error{blockName + " has no improvement to be removed"}, blockName{std::move(blockName)} {}

NotAcademicBuilding::NotAcademicBuilding(const string& name) : Error{name + " is not an Academic Building"} {}

NotProperty::NotProperty(const std::string &name) : Error{name + " is not a Property"} {}

NotPlayer::NotPlayer(const std::string &name) : Error{name + " is not a Player"} {}
