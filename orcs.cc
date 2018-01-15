#include "orcs.h"
#include <string>
using namespace std;

// ctor
Orcs::Orcs(){
  getHp() = 180;
  getAtk() = 30;
  getDef() = 25;
  getRace() = "Orcs";
}

// dtor
Orcs::~Orcs(){}
