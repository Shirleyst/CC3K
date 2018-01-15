#include "elf.h"
#include <string>
using namespace std;

// ctor
Elf::Elf(): Enemy{} {
	getHp() = 140;
	getAtk() = 30;
	getDef() = 10;
	getRace() = "Elf";
}

// dtor
Elf::~Elf(){}
