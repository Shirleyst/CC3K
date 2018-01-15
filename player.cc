#include "player.h"
#include <utility>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <curses.h> 

using namespace std;

// ctor
Player::Player(): Character{}, maxHP{0} {}

// Player::getMax() returns the maxhp the palyer can have
int &Player::getMax() {return maxHP;}

// Player::regain() updates the hp info of player if the player is troll
void Player::regain() {
  if(getRace() == "Troll") {
    getHp() = min(getMax(), getHp() + 5);
  }
}

// Player::attack(whom) makes player to attack whom and returns the damage
int Player::attack(shared_ptr<Character> whom) {
	int damage = 0;
	if(whom->getRace() != "Halfling") { // 100% hit
		damage += whom->beAttacked(shared_from_this());
		if(this->getRace()=="Vampire"){
			if(whom->getRace() =="Dwarf"){
				this->getHp() -= 5;
			} else {
				this->getHp() += 5;
			}
		}
	} else { // there is 1/2 chance to miss
		srand(clock());
		int r = rand() % 2;
		if(r == 1) { // 0 miss 1 hit
			damage += whom->beAttacked(shared_from_this());
		}
	}
	return damage;
}

// Player::beAttacked(who) makes who to attack player and returns the damage
int Player::beAttacked(shared_ptr<Character> who) {
	int damage = ceil(who->getAtk() * 100 / (100 + this->getDef()));
	if((this->getRace() == "Goblin") && (who->getRace() =="Orcs")){
		damage *= 1.5;
	}
	if(getHp() > damage){
		getHp() -= damage;
	} else {
		getHp() = 0;
	}
	return damage;
}

// Player::printInfo() prints the info of this player
void Player::printInfo() {
  cout << "HP: " << getHp() << endl;
  cout << "Atk: " << getAtk() << endl;
  cout << "Def: " << getDef() << endl;
  cout << "Action: ";
}

// Player::displayInfo() displays the info of this player(only under curses)
void Player::displayInfo() {
  int y, x = 0;
  getyx(stdscr, y, x);
  string hp =  "HP: " + to_string(getHp());
  mvaddstr(y + 1, x - 78, hp.c_str());
  string atk = "Atk: " + to_string(getAtk());
  mvaddstr(y + 2, x - 78, atk.c_str());
  string def = "Def: " + to_string(getDef());
  mvaddstr(y + 3, x - 78, def.c_str());
  string a = "Action: ";
  mvaddstr(y + 4, x - 78, a.c_str());
}

// dtor
Player::~Player() {}

