#include "cell.h"
#include "character.h"
#include "item.h"
#include "floor.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "halfling.h"
#include "orcs.h"
#include "merchant.h"
#include <curses.h> 

using namespace std;

// ctor
Cell::Cell(char c, int row, int col): content{c}, chamber{0},
coord{std::make_pair(row, col)}, cha{nullptr} {}

// Cell::getContent() returns the content of this cell
char &Cell::getContent() {
  return content;
}

// Cell::getRow() returns the row this cell is in
int &Cell::getRow() {
  return coord.first;
}

// Cell::getCol() returns the col this cell is in
int &Cell::getCol(){
  return coord.second;
}

// Cell::getChamber() returns the chamber this cell is in
int &Cell::getChamber() {
  return chamber;
}

// Cell::getChar() returns the character inside this cell
shared_ptr<Character> &Cell::getChar() {
  return cha;
}

// Cell::sameCell(c) returns true if this cell has the coordinate c and
//   false otherwise
bool Cell::sameCell(pair <int, int> c) {
  return ((getRow() == c.first) && (getCol() == c.second));
}

// Cell::isPlayerOrEnemy() returns true if the character inside this cell
//   is not player or enemy, and false otherwise
bool Cell::isPlayerOrEnemy() {
  if(getChar() != nullptr){
    if((getChar()->getRace() != "Potion") && (getContent() != 'G')) {
      return true;
    }
  }
  return false;
}

// Cell::createPotion(c, type) create a potion with given type and will be
//   used to c in future
void Cell::createPotion(shared_ptr<Character> c, int type) {
  content = 'P';
  shared_ptr<Character> p{new Item{c, "Potion", type}};
  std::swap(p, cha);
}

// Cell::createGold(c, type) create a gold with given type and will be
//   pick to c in future
void Cell::createGold(std::shared_ptr<Character> c, int type) {
  content = 'G';
  shared_ptr<Character> p{new Item{c, "Gold", type}};
  std::swap(p, cha);
}

// Cel::createE(race) create an enemy with the given race
void Cell::createE(char race) {
  if(race == 'H') {
    getContent() = 'H';
    shared_ptr<Character> p{new Human};
    std::swap(p, getChar());
  } else if(race == 'W'){
    getContent() = 'W';
    shared_ptr<Character> p{new Dwarf};
    std::swap(p, getChar());
  } else if(race == 'L'){
    getContent() = 'L';
    shared_ptr<Character> p{new Halfling};
    std::swap(p, getChar());
  } else if(race == 'E'){
    getContent() = 'E';
    shared_ptr<Character> p{new Elf};
    std::swap(p, getChar());
  } else if(race == 'O'){
    getContent() = 'O';
    shared_ptr<Character> p{new Orcs};
    std::swap(p, getChar());
  } else if(race == 'M'){
    getContent() = 'M';
    shared_ptr<Character> p{new Merchant};
    std::swap(p, getChar());
  }
}

// Cell::printChar() prints the character inside this cell
void Cell::printChar() {
  return;
}

// Cell::display() displays this cell(only under curses)
void Cell::display() {
  int x = coord.first + (LINES - 30) / 2;
  int y = coord.second + (COLS - 80) / 2;
  if((getContent() == 'G') && (cha == nullptr)) {
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(7));
    mvaddch(x, y, getContent());
    attroff(COLOR_PAIR(7));
  } else if(cha == nullptr) {
    mvaddch(x, y, getContent());
  } else {
    getChar()->display(x, y);
  }
}

// Cell::notify(f, coo, s) notifys all oberserver of s with given f and coo
string Cell::notify(Floor &f, pair<int,int> coo, Subject &s) {
  Cell &theCell = f.getMap()[coo.first][coo.second];
  string info = "";
  if((theCell.getContent() == 'D') && theCell.getChar() != nullptr) {
    auto theDragon = theCell.getChar();
    if(isPlayerOrEnemy()){
      this->getChar()->beAttacked(theDragon);
    }
  }
  if(this->getContent() == 'D') {
    pair<int, int> dragonCoord = make_pair(getRow(), getCol());
    this->notifyObservers(f, dragonCoord, *this);
    return "";
  }
  int n = f.enemys_random_move(coord.first, coord.second);
  if((n > 0) && (this->getChar() != nullptr)) {
    info += this->getChar()->getRace() + " deals " + to_string(n) +
    " damage to PC.";
  }
  return info;
}

// dtor
Cell::~Cell() {};

ostream &operator<<(ostream &out, Cell &c) {
  if(c.cha == nullptr) {
    cout << c.content;
  } else {
    cout << (*c.cha);
  }
  return out;
}
