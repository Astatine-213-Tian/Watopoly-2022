#include <string>
#include <utility>
#include "error.h"
using namespace std;

Error::Error(const string &msg) : msg{"Error" + msg} {}
const char *Error::what() const noexcept { return msg.c_str(); }

NotOwner::NotOwner(const string &playerName, const string &propertyName) :
    Error{"Player " + playerName + " does not own " + propertyName}, playerName{playerName}, propertyName{propertyName} {}


NotMonopolized::NotMonopolized(const string &blockName) :
    Error{blockName + " is not monopolized "}, blockName{blockName} {}

MaxImprove::MaxImprove(const string &blockName) :
    Error{blockName + " has reached maximal improvement number"}, blockName{blockName} {}

ZeroImprove::ZeroImprove(const string &blockName) :
    Error{blockName + " has no improvement to be removed"}, blockName{blockName} {}

NotAcademicBuilding::NotAcademicBuilding(const string &name) : Error{name + " is not an Academic Building"} {}

NotProperty::NotProperty(const string &name) : Error{name + " is not a Property"} {}

NotPlayer::NotPlayer(const string &name) : Error{name + " is not a Player"} {}

PropertyStillMortgage::PropertyStillMortgage(const string &name) : Error{name + " is mortgaged."}, propertyName{name} {}

PropertyStillUnMortage::PropertyStillUnMortage(const string &name) : Error{name + " is not mortgaged."}, propertyName{name} {}

TradeMoneyWithMoney::TradeMoneyWithMoney() : Error{"You're trying to trade money with money."} {}

NotEnoughCup::NotEnoughCup() : Error{"You don't have enough cup to use!"} {}

BuildingStillWithImprove::BuildingStillWithImprove(const string &name) :
    Error{name + " still have improvements. All improvements need to be sold before further action"}, propertyName{name} {}

NotEnoughCash::NotEnoughCash(const std::string &playerName) : Error{playerName + " don't have enough cash to complete the trade."} {}

InvalidCmd::InvalidCmd(const std::string &cmdName) : Error{"You cannot use command " + cmdName + "at this stage."} {}
