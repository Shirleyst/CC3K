#include "decorator.h"
#include <string>

using namespace std;

// ctor
Decorator::Decorator(shared_ptr<Character>component): 
Character{}, component{component} {}

// Decorator::setApply() apply this to the player and returns the corresponding
//   info
string Decorator::setApply() {
  if(this->getPermiss()) {
  	if(component->getRace() != "Drow") {
  	  component->getAtk() += this->getAtk();
  	  component->getHp() += this->getHp();
  	  component->getDef() += this->getDef();
  	  component->getGold() += this->getGold();
  	} else { // drow's special ability
  	  component->getAtk() += this->getAtk() * 1.5;
  	  component->getHp() += this->getHp() * 1.5;
  	  component->getDef() += this->getDef() * 1.5;
  	  component->getGold() += this->getGold() * 1.5;
  	}
  	if(component->getHp() > component->getMax()) {
  	  component->getHp() = component->getMax();
  	}
  	if(component->getAtk() < 0)  component->getAtk() = 0;
  	if(component->getDef() < 0)  component->getDef() = 0;
  	// determines the type of potion
  	return this->potionType();
  }
  return "";
}

// Decorator::potionType() returns the type of potion
std::string Decorator::potionType() {
  if(this->getHp() > 0) return "RH";
  if(this->getAtk() > 0) return "BA";
  if(this->getDef() > 0) return "BA";
  if(this->getHp() < 0) return "PH";
  if(this->getAtk() < 0) return "WA";
  if(this->getDef() < 0) return "WD";
  return "";
}

// dtor
Decorator::~Decorator() { }

