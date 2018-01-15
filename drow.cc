#include "drow.h"

// ctor
Drow::Drow():Player{} {
  this->getRace() = "Drow";
  this->getHp() = 155;
  this->getAtk() = 25;
  this->getDef() = 15;
  maxHP = this->getHp();
}

// dtor
Drow::~Drow(){}

