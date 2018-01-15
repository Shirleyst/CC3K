#include "vampire.h"
#include <cmath>
#include <climits>

// ctor
Vampire::Vampire(): Player{} {
  this->getRace() = "Vampire";
  this->getHp() = 50;
  this->getAtk() = 25;
  this->getDef() = 25;
  maxHP = INT_MAX;
}

// dtors
Vampire::~Vampire() {}
