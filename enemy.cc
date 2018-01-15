#include "enemy.h"
#include <cmath>
#include <ctime>
#include <utility>

using namespace std;

// ctor
Enemy::Enemy(): Character{}, isEnemy{true} {}

// Enemy::isE() returns true if it will attack the player and false otherwise
bool Enemy::isE() {return isEnemy;}

// Enemy::attack(whom) makes this to attack whom and returns the damage
int Enemy::attack(shared_ptr<Character> whom){
  int damage = 0;
  if((this->getRace() == "Merchant") && (whom->getState() == false)) return 0;
  srand(time(NULL));
  int i = rand() % 2;
	if(i == 1) { // else enemy misses this attack
		damage += whom->beAttacked(shared_from_this());
	}
  if((this->getRace() == "Elf") && (whom->getRace() != "Drow")){
    srand(clock());
    int j = rand() % 2;
  	if(j == 1){
  		damage += whom->beAttacked(shared_from_this());
  	}
  }
  return damage;
}

// Enemy::beAttacked(who) makes who to attack this and returns the damage
int Enemy::beAttacked(shared_ptr<Character> who){
  if(this->getRace() == "Merchant") who->getState() = true;
  isEnemy = true;
	int damage = ceil(who->getAtk() * 100 / (100 + this->getDef()));
	if(this->getHp() > damage){
	  this->getHp() -= damage;
	} else {
	  this->getHp() = 0;
	}
  if(this->getHp() == 0) {
    this->dropGold(who);
  }
  return damage;
}

// Enemy::dropGold(who) adds the gold to who if this enemy is died
void Enemy::dropGold(shared_ptr<Character> who) {
  if(who->getRace() == "Goblin") {
    who->getGold() += 5;
  } else if(this->getRace() == "Human") {
    who->getGold() += 4;
  } else if(this->getRace() == "Merchant") {
    who->getGold() += 6;
  } else if(this->getRace() != "Dragon") {
    srand(time(NULL));
    int i = rand() % 2 + 1;
    who->getGold() += i;
  }
}

// dtor
Enemy::~Enemy(){}

