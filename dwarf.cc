#include "dwarf.h"
#include <string>

using namespace std;

// ctor
Dwarf::Dwarf(): Enemy{} {
	getHp() = 100;
	getAtk() = 20;
	getDef() = 30;
	getRace() = "Dwarf";
}

// dtor
Dwarf::~Dwarf(){}
