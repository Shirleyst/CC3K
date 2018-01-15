#include "halfling.h"
#include <string>
using namespace std;

// ctor
Halfling::Halfling():Enemy{} {
	getHp() = 100;
	getAtk() = 15;
	getDef() = 20;
	getRace() = "Halfling";
}

// dtor
Halfling::~Halfling(){}
