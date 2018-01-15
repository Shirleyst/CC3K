#include "character.h"
#include <iostream>
#include <curses.h> 

using namespace std;

// ctor
Character::Character(): race{""}, hp{0}, atk{0}, def{0}, gold{0},
permission{true}, state{false} {}

// Character::getRace() returns the race of this
string &Character::getRace() {return race;}

// Character::getHp() returns the hp this has
int &Character::getHp() {return hp;}

// Character::getAtk() returns the atk this has
int &Character::getAtk() {return atk;}

// Character::getDef() returns the def this has
int &Character::getDef() {return def;}

// Character::getGold() returns the gold this has
int &Character::getGold() {return gold;}

// Character::getMax() returns the maxhp this can have
int &Character::getMax() {return hp;}

// Character::getPermiss() returns the permission of this
bool &Character::getPermiss() {return permission;}

// Character::getState() returns whether or not this attacked merchant
bool &Character::getState() {return state;}

// Character::getScore() returns current score the character has
int Character::getScore() {
  if(race == "Shade") {
    return getGold() * 1.5;
  }
  return getGold();
}

// Character::isE() returns true if this is enemy for player
bool Character::isE() {return false;}

// Character::isDead() returns true if the character is died
bool Character::isDead() { return (hp < 1);}

// Character::potionType() returns the type of this potion
string Character::potionType() {return "";}

// Character::printInfo() prints the information of this
void Character::printInfo() {return;}

// Character::regain() modifys the hp of this if this is Troll
void Character::regain() {return;}

// Character::displayInfo() displays the related info of this character
void Character::displayInfo() {return;}

// Character::display(x, y) displays this character with given coord x and
//   y(only under curses)
void Character::display(int x, int y) {
  if((getRace() == "Shade") || (getRace() == "Drow")
    || (getRace() == "Vampire") || (getRace() == "Troll")
    || (getRace() == "Goblin")) {
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(3));
    mvaddch(x, y, '@');
    attroff(COLOR_PAIR(3));
    return;
  }
  init_pair(4, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(4));
  if(getRace() == "Human") mvaddch(x, y, 'H');
  if(getRace() == "Dwarf") mvaddch(x, y, 'W');
  if(getRace() == "Elf") mvaddch(x, y, 'E');
  if(getRace() == "Orcs") mvaddch(x, y, 'O');
  if(getRace() == "Merchant") mvaddch(x, y, 'M');
  if(getRace() == "Dragon") mvaddch(x, y, 'D');
  if(getRace() == "Halfling") mvaddch(x, y, 'L');
  attroff(COLOR_PAIR(4));
  if(getRace() == "Potion") {
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(5));
    mvaddch(x, y, 'P');
    attroff(COLOR_PAIR(5));
  }
  if(getRace() == "Gold") {
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(6));
    mvaddch(x, y, 'G');
    attroff(COLOR_PAIR(6));
  }
}

// Character::setApply() apply this to the player and returns the 
//   corresponding info
string Character::setApply() {return "";}

// Character::attack(whom) makes this to attack the given whom and returns
//   the damage
int Character::attack(shared_ptr<Character> whom) {return 0;}

// Character::beAttacked(who) makes who attack this and returns the damage
int Character::beAttacked(shared_ptr<Character> who) {return 0;}

// dtor
Character::~Character() {}

ostream &operator<<(ostream &out, Character &c) {
  if((c.getRace() == "Shade") || (c.getRace() == "Drow")
    || (c.getRace() == "Vampire") || (c.getRace() == "Troll")
    || (c.getRace() == "Goblin")) {
    cout << "@";
  }
  if(c.getRace() == "Human") cout << "H";
  if(c.getRace() == "Dwarf") cout << "W";
  if(c.getRace() == "Elf") cout << "E";
  if(c.getRace() == "Orcs") cout << "O";
  if(c.getRace() == "Merchant") cout << "M";
  if(c.getRace() == "Dragon") cout << "D";
  if(c.getRace() == "Halfling") cout << "L";
  if(c.getRace() == "Potion") cout << "P";
  if(c.getRace() == "Gold") cout << "G";
  return out;
}
