#include "item.h"
#include "character.h"

using namespace std;

// ctor
Item::Item(shared_ptr<Character> c, std::string race, int type): Decorator{c} {
  this->getRace() = race;
  if(race == "Potion") {
  	if(type == 0) this->getHp() = 10;
  	if(type == 1) this->getAtk() = 5;
  	if(type == 2) this->getDef() = 5;
  	if(type == 3) this->getHp() = -10;
  	if(type == 4) this->getAtk() = -5;
  	if(type == 5) this->getDef() = -5;
  } else {
  	if(0 <= type && type <= 4) this->getGold() = 2;
  	if(5 <= type && type <= 6) this->getGold() = 1;
  	if(type == 7) {
      this->getGold() = 6;
      this->getPermiss() = false;
    }
    if(type == 8) this->getGold() = 4;
  }
}

// dtor
Item::~Item(){}

