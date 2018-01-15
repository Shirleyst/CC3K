#include "shade.h"

Shade::Shade(): Player{} {
  this->getRace() = "Shade";
  this->getHp() = 125;
  this->getAtk() = 25;
  this->getDef() = 25;
  maxHP = this->getHp();
}

Shade::~Shade() {}
