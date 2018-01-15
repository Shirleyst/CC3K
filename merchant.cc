#include "enemy.h"
#include "merchant.h"
#include <string>
using namespace std;

// ctor
Merchant::Merchant(): Enemy{} {
	isEnemy = false;
	getHp() = 30;
	getAtk() = 70;
	getDef() = 5;
	getRace() = "Merchant";
};

// dtor
Merchant::~Merchant(){}
