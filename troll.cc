#include "troll.h"

// ctor
Troll::Troll():Player{} {
  this->getRace() = "Troll";
  this->getHp() = 120;
  this->getAtk() = 25;
  this->getDef() = 15;
  maxHP = this->getHp();
}

// dtor
Troll::~Troll() {}
