#include "human.h"
#include <string>

using namespace std;

// ctor
Human::Human(): Enemy{} {
	getHp() = 140;
	getAtk() = 20;
	getDef() = 20;
	getRace() = "Human";
}

// dtor
Human::~Human(){}
