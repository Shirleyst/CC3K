#include "goblin.h"
#include <cmath>

// ctor
Goblin::Goblin(): Player{} {
  this->getRace() = "Goblin";
  this->getHp() = 110;
  this->getAtk() = 15;
  this->getDef() = 20;
  maxHP = this->getHp();
}

// dtor
Goblin::~Goblin() {}
