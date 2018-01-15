#include "dragon.h"
#include "character.h"
#include <string>
using namespace std;

// ctor
Dragon::Dragon(): Enemy{} {
	getHp() = 150;
	getAtk() = 20;
	getDef() = 20;
	getRace() = "Dragon";
}

// dtor
Dragon::~Dragon(){}
