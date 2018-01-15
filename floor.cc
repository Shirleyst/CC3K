#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "cell.h"
#include "floor.h"
#include "shade.h"
#include "character.h"
#include "dragon.h"
#include "drow.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "halfling.h"
#include "orcs.h"
#include "merchant.h"
#include "game.h"
#include <curses.h> 

using namespace std;

// eraseElement(v, r, c) erase the pair(r, c) in v
static void eraseElement(vector <pair<int, int>> &v, int r, int c) {
  int s = v.size();
  for(int i = 0; i < s; i++) {
    if((v[i].first == r) && (v[i].second == c)) {
      v.erase(v.begin() + i);
    }
  }
}

// addSurround(v, r, c, pos) adds all coordinates in v that is near (r, c)
//   to pos
static void addSurround(vector<pair<int, int>> &v, int r, int c, 
  vector<pair<int, int>> &pos) {
  int u = v.size();
  for(int j = 0; j < u; j++) {
    int x = v[j].first;
    int y = v[j].second;
    if((r - 1 <= x && x <= r + 1) && (c - 1 <= y && y <= c + 1)
      && (x != r && y != c)) {
      pos.emplace_back(make_pair(x, y));
    }
  }
}

// ctor
Floor::Floor(Game &g, int f): theGame{g}, map{g.getBase()},
curremp{vector<vector <pair<int, int>>>{g.getBase().size()}},
enemys{vector<pair<int, int>>{g.getBase().size()}},
players{std::make_pair(0, 0)}, 
dragon{vector<pair<int, int>>{g.getBase().size()}}, 
hoard{vector<pair<pair<int, int>, bool>>{g.getBase().size()}}, 
bag{vector<int>{50}}, numPotion{10}, numGold{10}, numEnemy{20}, floor{f},
command{}, m{true}, potionType{vector<string>{6}} {
  vector<pair<int, int>> sub{g.getBase().size()};
  for(int i = 0; i < 5; i++) {
    curremp.push_back(sub);
  }
  int u = g.getEmp().size();
  for(int j = 0; j < u; j++) {
    int index = g.getEmp()[j].getChamber();
    int r = g.getEmp()[j].getRow();
    int c = g.getEmp()[j].getCol();
    curremp[index - 1].emplace_back(make_pair(r, c));
  }
  cout << "New floor has been generated." << endl;
}

// Floor::getMap() returns the map of this floor
vector <vector <Cell>> &Floor::getMap() { return map; }

// Floor::getcurrEmp() returns the list of current empty cells' coordinates
vector <vector <pair<int, int>>> &Floor::getcurrEmp() {
  return curremp;
}

// Floor::getEnemys() returns the list of enemys coordinates
vector <pair<int, int>>& Floor::getEnemys(){
  return enemys;
}

// Floor::getPlayers() returns the coordination of player
pair<int, int> &Floor::getPlayers() {
  return players;
}

// Floor::getPotion() returns the list of potion type
vector<string> &Floor::getPotion() {
  return potionType;
}

// Floor::score() returns the current score the player has
int Floor::score() {
  return map[players.first][players.second].getChar()->getScore();
}

// Floor::floor_clear() clears the content of this floor
void Floor::floor_clear(){
  m = true;
  int u = map.size();
  for(int i = 0; i < u; i++){
    int v = map.at(i).size();
    for(int j = 0; j < v; j++){map[i][j].getChar().reset();}
    map.at(i).clear();
  }
  int p = theGame.getBase()[0].size();
  for(int i = 0; i < u; i++){
    for(int j = 0; j < p; j++){
      map[i].push_back(theGame.getBase()[i][j]);
    }
  }
  enemys.clear();
  dragon.clear();
  hoard.clear();
  u = curremp.size();
  for(int i = 0; i < u; i++){curremp.at(i).clear();}
  u = theGame.getEmp().size();
  for(int j = 0; j < u; j++) {
    int index = theGame.getEmp()[j].getChamber();
    int r = theGame.getEmp()[j].getRow();
    int c = theGame.getEmp()[j].getCol();
    curremp[index - 1].emplace_back(make_pair(r, c));
  }
}

//  Floor::generate(hp, state, race) generates elements on map based on given
//    hp and race
void Floor::generate(int hp, int gold, bool state, string race) {
  int chamber = -1;
  this->generatePlayer(hp, gold, state, race, chamber);
  this->generateSW(chamber);
  this->generatePotion(numPotion);
  this->generateGold(numGold);
  this->generateEnemy(numEnemy);
}

// Floor::generatePlayer(hp, state, race, chamber) generates player with given
//   race and hp and changes chamber to the chamber of player
void Floor::generatePlayer(int hp, int gold, 
  bool state, string race, int &chamber) {
  int cham = chamber - 1;
  while(chamber - 1 == cham) {
    srand((unsigned)time(NULL));
    cham = rand() % 5; // determines chamber(0-4)
  }
  chamber = cham + 1;
  int total = curremp[cham].size();
  srand(clock());
  int ran = rand() % total; // determines the cell in chamber
  int r = curremp[cham][ran].first;
  int c = curremp[cham][ran].second;
  createPlayer(hp, gold, state, race, r, c);
  // erase that cell from current empty list
  curremp[cham].erase(curremp[cham].begin() + ran);
}

// Floor::createPlayer(race, r, c) creates palyer at (r,c)
void Floor::createPlayer(int hp, int gold, bool state, 
  string race, int r, int c) {
  if(race == "Shade") {
    shared_ptr<Character> p{new Shade};
    std::swap(p, map[r][c].getChar());
  }
  if(race == "Drow") {
    shared_ptr<Character> p{new Drow};
    std::swap(p, map[r][c].getChar()); 
  }
  if(race == "Vampire") {
    shared_ptr<Character> p{new Vampire};
    std::swap(p, map[r][c].getChar());
  }
  if(race == "Goblin") {
    shared_ptr<Character> p{new Goblin};
    std::swap(p, map[r][c].getChar());
  }
  if(race == "Troll") {
    shared_ptr<Character> p{new Troll};
    std::swap(p, map[r][c].getChar());
  }
  // put the coordinate of players
  players = make_pair(r, c); 
  if(hp != 0) map[r][c].getChar()->getHp() = hp;
  map[r][c].getChar()->getGold() = gold;
  map[r][c].getChar()->getState() = state;
}

// Floor::generateSW(chamber) generates stair which will not be in the given
//   chamber
void Floor::generateSW(int chamber) {
  int newcham = chamber - 1;
  int total = 0;
  // determine which chamber to put stair
  while(((chamber - 1) == newcham) || (total == 0)) {
    srand(clock());
    newcham = rand() % 5; // 0-4
    total = curremp[newcham].size();
  }
  srand(clock());
  int index = rand() % total;
  int r = curremp[newcham][index].first;
  int c = curremp[newcham][index].second;
  map[r][c].getContent() = '\\';
  curremp[newcham].erase(curremp[newcham].begin() + index);
}

// Floor::generatePotion(n) generates n potions
void Floor::generatePotion(int n) {
  int x = players.first;
  int y = players.second;
  for(int i = 0; i < n; i++) {
    srand(clock());
    int chamber = rand() % 5; // determine chamber
    srand(clock());
    int type = rand() % 6; // each type of potion has a corresponding number
    srand(clock());
    int index = rand() % curremp[chamber].size();
    int r = curremp[chamber][index].first;
    int c = curremp[chamber][index].second;
    map[r][c].createPotion(map[x][y].getChar(), type);
    curremp[chamber].erase(curremp[chamber].begin() + index);
  }
}

// Floor::generateGold(n) generates n gold
void Floor::generateGold(int n) {
  int type; // type of gold
  int x = players.first;
  int y = players.second;
  for(int i = 0; i < n; i++) {
    srand(clock());
    int chamber = rand() % 5; // 0-4
    srand(clock());
    type = rand() % 8; // 0-7
    srand(clock());
    int size = curremp[chamber].size();
    int index = rand() % size;
    int r = curremp[chamber][index].first;
    int c = curremp[chamber][index].second;
    map[r][c].getContent() = 'G';
    if(type != 7) {
      map[r][c].createGold(map[x][y].getChar(), type);
    }
    if(type == 7) {
      if(!generateHoard(r, c, chamber)) {
        c += 1;
        continue;
      }
    }
    curremp[chamber].erase(curremp[chamber].begin() + index);
  }
}

// Floor::generateHoard(r, c, chamber) generates dargon hoard, returns true
//   if can put dragon near the hoard and false otherwise
bool Floor::generateHoard(int r, int c, int chamber) {
  vector<pair<int, int>> dargonPos;
  // determines the avaliable position to put dargon
  addSurround(curremp[chamber], r, c, dargonPos);
  srand(clock());
  int v = dargonPos.size();
  if(v != 0) {
    hoard.emplace_back(make_pair(make_pair(r, c), true)); 
    // true if the dragon is alive
    int pos = rand() % v;
    int x = dargonPos[pos].first;
    int y = dargonPos[pos].second;
    generateDragon(x, y, r, c);
    return true;
  }
  return false;
}

// Floor::generateDragon(x, y) generate dragon with the given x y coordinates
//   and with the hoard pos r, c
void Floor::generateDragon(int x, int y, int r, int c) {
  int newcham = map[x][y].getChamber() - 1;
  map[x][y].getContent() = 'D';
  shared_ptr<Character> p{new Dragon};
  std::swap(p, map[x][y].getChar());
  eraseElement(curremp[newcham], x, y);
  enemys.emplace_back(make_pair(x, y));
  dragon.emplace_back(make_pair(x, y));
  // attach the pos near hoard as obervers
  for(int i = r - 1; i <= r + 1; i++) {
    for(int j = c - 1; j <= c + 1; j++) {
      if(!((i == x) && (j == y))) {
        shared_ptr<Observer> p{new Cell{map[i][j]}};
        map[x][y].attach(p);
      }
    }
  }
  // attach the pos near dragon as obervers
  for(int a = x - 1; a <= x + 1; a++) {
    for(int b = y - 1; b <= y + 1; b++) {
      if((a != x) || (b != y)) {
        shared_ptr<Observer> p{new Cell{map[a][b]}};
        map[x][y].attach(p);
      }
    }
  }
}

// Floor::generateEnemy(n) generates n enemys
void Floor::generateEnemy(int n) {
  for(int i = 0; i < n; i++) {
    srand(clock());
    int chamber = rand() % 5; // 0-4
    srand(clock());
    int type = rand() % 18; // 0-17
    srand(clock());
    if(curremp[chamber].size() != 0) {
      int u = curremp[chamber].size();
      int index = rand() % u;
      int r = curremp[chamber][index].first;
      int c = curremp[chamber][index].second;
      if(0 <= type && type <= 3){
        map[r][c].getContent() = 'H';
        shared_ptr<Character> p{new Human};
        std::swap(p, map[r][c].getChar());
      } else if(4 <= type && type <= 6){
        map[r][c].getContent() = 'W';
        shared_ptr<Character> p{new Dwarf};
        std::swap(p, map[r][c].getChar());
      } else if(7 <= type && type <= 11){
        map[r][c].getContent() = 'L';
        shared_ptr<Character> p{new Halfling};
        std::swap(p, map[r][c].getChar());
      } else if(12 <= type && type <= 13){
        map[r][c].getContent() = 'E';
        shared_ptr<Character> p{new Elf};
        std::swap(p, map[r][c].getChar());
      } else if(14 <= type && type <= 15){
        map[r][c].getContent() = 'O';
        shared_ptr<Character> p{new Orcs};
        std::swap(p, map[r][c].getChar());
      } else {
        map[r][c].getContent() = 'M';
        shared_ptr<Character> p{new Merchant};
        std::swap(p, map[r][c].getChar());
      }
      enemys.emplace_back(make_pair(r, c));
      curremp[chamber].erase(curremp[chamber].begin() + index);
      shared_ptr<Observer> p{new Cell{map[r][c]}};
      map[players.first][players.second].attach(p);
    }
  }
}

// Floor::enemys_random_move(x, y) makes the enemy at x y to do action and
//   returns damage if it attacks or 0 otherwise
int Floor::enemys_random_move(int x, int y) {
  int d = 0; // damage
  if(map[x][y].getChar() == nullptr) return 0;
  if(enemy_should_attack(x, y, d)) return d;
  // do random move
  if((m) && (map[x][y].getChar() != nullptr)) {
    if(map[x][y].getChar()->getRace() != "Dragon") {
      int chamber = map[x][y].getChamber();
      if(chamber == 0) return 0;
      vector<pair<int, int>> pos;
      addSurround(curremp[chamber - 1], x, y, pos);
      int s = pos.size();
      if(s != 0) {
        srand(clock());
        int index = rand() % pos.size();
        int newx = pos[index].first;
        int newy = pos[index].second;
        curremp[chamber - 1].emplace_back(make_pair(x, y));
        eraseElement(curremp[chamber - 1], newx, newy);
        eraseElement(enemys, x, y);
        enemys.emplace_back(make_pair(newx, newy));
        map[newx][newy].getChar() = map[x][y].getChar();
        map[x][y].getChar() = nullptr;
        std::swap(map[newx][newy].getContent(), map[x][y].getContent());
      }
    }
  }
  return 0;
}

// Floor::enemy_should_attack(r, c, d) returns true if enemy in (r,c) can
//   attack and changes d to its damage and false otherwise
bool Floor::enemy_should_attack(int r, int c, int &d){
  int playerR = players.first;
  int playerC = players.second;
  if((map[r][c].getChar()->getRace() == "Merchant") &&
     (map[playerR][playerC].getChar()->getState() == false)) {
    return false;
  }
  if(((playerR > r - 2) && (playerR < r + 2)) &&
     ((playerC > c - 2) && (playerC < c + 2))) {
    // if within the radius
    if(map[r][c].getChar() != nullptr) {
      d = map[r][c].getChar()->attack(map[playerR][playerC].getChar());
    }
    return true;
  }
  return false;
}
 
// Floor::newEnemy() updates enemy informaiton
void Floor::newEnemy(int x, int y, int ax, int ay) {
  map[x][y].clearOb();
  int u = enemys.size();
  for(int i = 0; i < u; i++) {
    shared_ptr<Observer> p{new Cell{map[enemys[i].first][enemys[i].second]}};
    map[ax][ay].attach(p);
  }
}

// Floor::walk(ax, ay, x, y) makes player moves from ax ay to x y and
//   changes ax ay to x y
void Floor::walk(int &ax, int &ay, int x, int y) {
  if((map[ax][ay].getChar() == nullptr) || (map[x][y].getContent() == '|')
     || (map[x][y].getContent() == '-')) {
    return;
  }
  // determine if x,y is a hoard
  int index = -1;
  int len = hoard.size();
  for(int i = 0; i < len; i++) {
    if(x == hoard[i].first.first && y == hoard[i].first.second) {
      index = i;
    }
  }
  if((this->map[x][y].getContent() == '.') ||
     (this->map[x][y].getContent() == '+') ||
     (this->map[x][y].getContent() == '#') ||
     (index != -1 && (hoard[index].second == true))) {
    std::swap(this->map[x][y].getChar(), this->map[ax][ay].getChar());
    int chamber = map[x][y].getChamber();
    if((chamber != 0) && (this->map[x][y].getContent() != 'G')) {
      eraseElement(curremp[chamber - 1], x, y);
    }
    int c = map[ax][ay].getChamber();
    if(c != 0) curremp[c - 1].emplace_back(make_pair(ax, ay));
    ax = x;
    ay = y;
    players = make_pair(x, y);
  } else if(this->map[x][y].getContent() == 'G') {
    if(index != -1 && (hoard[index].second == false)) {
      this->map[x][y].getContent() = '.';
      std::swap(this->map[x][y].getChar(), this->map[ax][ay].getChar());
      this->map[x][y].getChar()->getGold() += 6;
    } else if(index == -1) {
      this->map[x][y].getContent() = '.';
      this->map[x][y].getChar()->setApply();
      this->map[x][y].getChar() = this->map[ax][ay].getChar();
      this->map[ax][ay].getChar() = nullptr;
    }
    int chamber = map[x][y].getChamber() - 1;
    eraseElement(curremp[chamber], x, y);
    int c = map[ax][ay].getChamber();
    if(c != 0) curremp[c - 1].emplace_back(make_pair(ax, ay));
    ax = x;
    ay = y;
    players = make_pair(ax, ay);
  }
  if(this->map[x][y].getContent() == '\\') {
    int hp = map[ax][ay].getChar()->getHp();
    int gold = map[ax][ay].getChar()->getGold();
    bool state = map[ax][ay].getChar()->getState();
    floor++;
    this->theGame.nextlevel(hp, gold, state);
  }
}

// Floor::move(comm, info) makes player move with the given comm and changes 
//   info to corresponding message
void Floor::move(string &comm, string &info) {
  command = comm;
  int &ax = players.first;
  int &ay = players.second;
  int x = ax;
  int y = ay;
  if(command == "so") {
    this->walk(ax, ay, ax + 1, ay);
  }
  if(command == "no") {
    this->walk(ax, ay, ax - 1, ay);
  }
  if(command == "ea") {
    this->walk(ax, ay, ax, ay + 1);
  }
  if(command == "we") {
    this->walk(ax, ay, ax, ay - 1);
  }
  if(command == "se") {
    this->walk(ax, ay, ax + 1, ay + 1);
  }
  if(command == "sw") {
    this->walk(ax, ay, ax + 1, ay - 1);
  }
  if(command == "ne") {
    this->walk(ax, ay, ax - 1, ay + 1);
  }
  if(command == "nw") {
    this->walk(ax, ay, ax - 1, ay - 1);
  }
  string dir = "";
  if(comm == "no") dir = "North";
  if(comm == "ea") dir = "East";
  if(comm == "so") dir = "South";
  if(comm == "we") dir = "West";
  if(comm == "ne") dir = "North-East";
  if(comm == "nw") dir = "North-West";
  if(comm == "se") dir = "South-East";
  if(comm == "sw") dir = "South-West";
  if((x != ax) || (y != ay)) {
    info = info + "PC moves to " + dir;
  } else if(dir != ""){
    info = info + "PC cannot move to " + dir;
  } else {
    info = info + "PC do not know that direction(invalid direction)";
  }
  info += printSurround();
  info += map[x][y].notifyObservers(*this,make_pair(x,y), map[x][y]);
  newEnemy(x, y, ax, ay);
  map[ax][ay].getChar()->regain();
}

// Floor::drink(x, y) makes player to use the potion at x,y and returns
//   corresponding message
string Floor::drink(int x, int y) {
  string name = "";
  if(this->map[x][y].getChar() == nullptr) return "nothing";
  if(this->map[x][y].getContent() == 'P') {
    this->map[x][y].getContent() = '.';
    name += this->map[x][y].getChar()->setApply();
    this->map[x][y].getChar() = nullptr;
    int chamber = map[x][y].getChamber() - 1;
    curremp[chamber].emplace_back(make_pair(x, y));
    if(std::find(potionType.begin(), potionType.end(), name)
        == potionType.end()) {
      potionType.push_back(name);
    }
    return name;
  }
  return "nothing";
}

// Floor::use(comm, info) makes player to use the potion with given comm
//   and changes info to corresponding message
void Floor::use(string &comm, string &info) {
  command = comm;
  string name = "";
  int ax = players.first;
  int ay = players.second;
  if(command == "so") {
    name += this->drink(ax + 1, ay);
  }
  if(command == "no") {
    name += this->drink(ax - 1, ay);
  }
  if(command == "ea") {
    name += this->drink(ax, ay + 1);
  }
  if(command == "we") {
    name += this->drink(ax, ay - 1);
  }
  if(command == "se") {
    name += this->drink(ax + 1, ay + 1);
  }
  if(command == "sw") {
    name += this->drink(ax + 1, ay - 1);
  }
  if(command == "ne") {
    name += this->drink(ax - 1, ay + 1);
  }
  if(command == "nw") {
    name += this->drink(ax - 1, ay - 1);
  }
  if(map[ax][ay].getChar()->getHp() > map[ax][ay].getChar()->getMax()) {
    map[ax][ay].getChar()->getHp() = map[ax][ay].getChar()->getMax();
  }
  if(name != "") {
    info += "PC uses " + name;
  } else {
    info += "PC do not know that direction(invalid direction)";
  }
  info += printSurround();
  info += map[ax][ay].notifyObservers(*this,make_pair(ax,ay), map[ax][ay]);
  newEnemy(ax, ay, ax, ay);
  map[ax][ay].getChar()->regain();
}

// Floor::put_bag(x, y) makes player to put the potion at x,y to bag and
//   returns corresponding message
string Floor::put_bag(int x, int y) {
  string name = "";
  if(this->map[x][y].getChar() == nullptr) return "nothing";
  if(this->map[x][y].getContent() == 'P') {
    this->map[x][y].getContent() = '.';
    name += this->map[x][y].getChar()->potionType();
    this->map[x][y].getChar() = nullptr;
    int chamber = map[x][y].getChamber() - 1;
    curremp[chamber].emplace_back(make_pair(x, y));
    if(name == "RH") bag.emplace_back(0);
    if(name == "BA") bag.emplace_back(1);
    if(name == "BD") bag.emplace_back(2);
    if(name == "PH") bag.emplace_back(3);
    if(name == "WA") bag.emplace_back(4);
    if(name == "WD") bag.emplace_back(5);
    return name;
  }
  return "nothing";
}

// Floor::use_bag(comm, info) makes player to use the potion with given comm
//   and changes info to corresponding message
void Floor::use_bag(string &comm, string &info) {
  command = comm;
  string name = "";
  int ax = players.first;
  int ay = players.second;
  if(command == "so") {
    name += this->drink(ax + 1, ay);
  }
  if(command == "no") {
    name += this->drink(ax - 1, ay);
  }
  if(command == "ea") {
    name += this->drink(ax, ay + 1);
  }
  if(command == "we") {
    name += this->drink(ax, ay - 1);
  }
  if(command == "se") {
    name += this->drink(ax + 1, ay + 1);
  }
  if(command == "sw") {
    name += this->drink(ax + 1, ay - 1);
  }
  if(command == "ne") {
    name += this->drink(ax - 1, ay + 1);
  }
  if(command == "nw") {
    name += this->drink(ax - 1, ay - 1);
  }
  if(map[ax][ay].getChar()->getHp() > map[ax][ay].getChar()->getMax()) {
    map[ax][ay].getChar()->getHp() = map[ax][ay].getChar()->getMax();
  }
  if(name != "") {
    info += "PC puts " + name + "in bag";
  } else {
    info += "PC do not know that direction(invalid direction)";
  }
  info += printSurround();
  info += map[ax][ay].notifyObservers(*this,make_pair(ax,ay), map[ax][ay]);
  newEnemy(ax, ay, ax, ay);
  map[ax][ay].getChar()->regain();
}

// Floor::hurt(ax, ay, x, y) makes player at (x, y) to attack (ax, ay) and
//   returns the damage
int Floor::hurt(int ax, int ay, int x, int y) {
  int damage = 0;
  // if there is an enemy in that direction
  if(map[x][y].getChar() != nullptr) {
    damage = map[ax][ay].getChar()->attack(map[x][y].getChar());
  }
  return damage;
}

// Floor::use(comm, info) makes player to attack based on the given comm
//   and changes info to corresponding message
void Floor::attack(string &comm, string &info) {
  command = comm;
  int ax = players.first;
  int ay = players.second;
  int x, y;
  string enemy = "";
  if(command == "so") {
    x = ax + 1;
    y = ay;
  }
  if(command == "no") {
    x = ax - 1;
    y = ay;
  }
  if(command == "ea") {
    x = ax;
    y = ay + 1;
  }
  if(command == "we") {
    x = ax;
    y = ay - 1;
  }
  if(command == "se") {
    x = ax + 1;
    y = ay + 1;
  }
  if(command == "sw") {
    x = ax + 1;
    y = ay - 1;
  }
  if(command == "ne") {
    x = ax - 1;
    y = ay + 1;
  }
  if(command == "nw") {
    x = ax - 1;
    y = ay - 1;
  }
  int damage = this->hurt(ax, ay, x, y);
  if(damage > 0) {
    string enemy = map[x][y].getChar()->getRace();
    int h = map[x][y].getChar()->getHp();
    info = " PC deals " + to_string(damage) + " damge to " + enemy;
    info += "(" + to_string(h) + " HP)";
    if(map[x][y].getChar()->getHp() == 0) {
      if(map[x][y].getChar()->getRace() == "Dragon") {
        int len = dragon.size();
        for(int i = 0; i < len; i++) {
          if(dragon[i].first == x && dragon[i].second == y) {
            hoard[i].second = false;
          }
        }
      }
      shared_ptr<Observer> p{new Cell{map[x][y]}};
      map[ax][ay].dettach(p);
      this->map[x][y].getContent() = '.';
      this->map[x][y].getChar() = nullptr;
      int chamber = map[x][y].getChamber() - 1;
      curremp[chamber].emplace_back(make_pair(x, y));
      eraseElement(enemys, x, y);
    }
  } else {
    info += "PC does nothing";
  }
  info += printSurround();
  info += map[ax][ay].notifyObservers(*this,make_pair(x,y), map[x][y]);
  newEnemy(x, y, ax, ay);
  map[ax][ay].getChar()->regain();
}

// Floor::WASD(c, info) uses c to control the floor and sent infomation to
//   info(only under curses)
void Floor::WASD(char c, string &info) {
  string comm;
  int x = players.first;
  int y = players.second;
  if((c == 'W') || (c == 'w')) {
    comm = "no";
    if(map[x - 1][y].getContent() == 'P') {
      use(comm, info);
    } else if(map[x - 1][y].getContent() == 'G') {
      move(comm, info);
    } else if(map[x - 1][y].getChar() != nullptr) {
      attack(comm, info);
    } else {
      move(comm, info);
    }
  } else if((c == 'A') || (c == 'a')) {
    comm = "we";
    if(map[x][y - 1].getContent() == 'P') {
      use(comm, info);
    } else if(map[x][y - 1].getContent() == 'G') {
      move(comm, info);
    } else if(map[x][y - 1].getChar() != nullptr) {
      attack(comm, info);
    } else {
      move(comm, info);
    }
  } else if((c == 'S') || (c == 's')) {
    comm = "so";
    if(map[x + 1][y].getContent() == 'P') {
      use(comm, info);
    } else if(map[x + 1][y].getContent() == 'G') {
      move(comm, info);
    } else if(map[x + 1][y].getChar() != nullptr) {
      attack(comm, info);
    } else {
      move(comm, info);
    }
  } else if((c == 'D') || (c == 'd')) {
    comm = "ea";
    if(map[x][y + 1].getContent() == 'P') {
      use(comm, info);
    } else if(map[x][y + 1].getContent() == 'G') {
      move(comm, info);
    } else if(map[x][y + 1].getChar() != nullptr) {
      attack(comm, info);
    } else {
      move(comm, info);
    }
  }
}

// Floor::stop() make enemy to move or stop
void Floor::stop() {
  if(m) {
    m = false;
  } else {
    m = true;
  }
}

// Floor::isLost() returns true if player's hp is <= 0 and false otehrwise
bool Floor::isLost() {
  return map[players.first][players.second].getChar()->isDead();
}

// Floor::printFirst() returns the information of palyer and floor
string Floor::printFirst() {
  string f = "";
  int r = players.first;
  int c = players.second;
  f = "Race: " + map[r][c].getChar()->getRace();
  f += " Gold: " + to_string(map[r][c].getChar()->getGold());
  int curr = floor + 1;
  string floor = "Floor " + to_string(curr) + " ";
  int u = map[0].size();
  int v = f.length();
  int w = floor.length();
  for(int i = 0;
      i < u - v - w - 1; i++) {
    f += " ";
  }
  f += floor;
  return f;
}

// Floor::printSurround() returns a string contains all info around player
string Floor::printSurround() {
  string info = "";
  for(int r = players.first - 1; r <= players.first + 1; r++) {
    for(int c = players.second - 1; c <= players.second + 1; c++) {
      if(!((r == players.first) && (c == players.second))) {
        if(map[r][c].getContent() == 'G') {
          info += " and sees some Gold";
        } else if (map[r][c].getChar() != nullptr) {
          if(map[r][c].getChar()->getRace() == "Potion") {
            string name = map[r][c].getChar()->potionType();
            if(std::find(potionType.begin(), potionType.end(), name) 
               != potionType.end()) {
              info += " and sees a " + name;
            } else {
              info += " and sees an unknown Potion";
            }
          } else {
            info += " and sees a " + map[r][c].getChar()->getRace();
          }
        }
      }
    }
  }
  info += ".";
  return info;
}

// Floor::modify(hp, gold, state, race) modifies the given map and creates 
// floor with given hp, gold, state and race
void Floor::modify(int hp, int gold, bool state, string race) {
  int r_l = map.size();
  int c_l = map[0].size();
  int chamber = 0;
  bool player = false;
  for(int a = 0; a < r_l; a++) {
    for(int b = 0; b < c_l; b++) {
      if(map[a][b].getContent() == '@') {
        map[a][b].getContent() = '.';
        createPlayer(hp, gold, state, race, a, b);
        int c = map[a][b].getChamber() - 1;
        eraseElement(curremp[c], a, b);
        player = true;
      } else if(map[a][b].getContent() == '\\') {
        chamber = map[a][b].getChamber();
        eraseElement(curremp[chamber - 1], a, b);
      }
    }
  }
  if(!player) {
    generatePlayer(hp, gold, state, race, chamber);
  }
  int x = players.first;
  int y = players.second;
  for(int i = 0; i < r_l; i++) {
    for(int j = 0; j < c_l; j++) {
      char c = map[i][j].getContent();
      int n = c - '0';
      if(0 <= n && n <= 5) {
        map[i][j].getContent() = 'P';
        map[i][j].createPotion(map[x][y].getChar(), n);
        int c = map[i][j].getChamber() - 1;
        eraseElement(curremp[c], i, j);
      } else if(6 <= n && n <= 8) {
        map[i][j].getContent() = 'G';
        int g = n;
        if(n == 6) g = 0;
        if(n == 7) g = 5;
        map[i][j].createGold(map[x][y].getChar(), g);
        int c = map[i][j].getChamber() - 1;
        eraseElement(curremp[c], i, j);
      } else if(n == 9) {
        map[i][j].getContent() = 'G';
        hoard.emplace_back(make_pair(i, j), true);
        int cham = map[i][j].getChamber() - 1;
        for(int r = i - 1; r <= i + 1; r++) {
          for(int c = j - 1; c <= j + 1; c++) {
            if(map[r][c].getContent() == 'D') {
              generateDragon(r, c, i, j);
              eraseElement(curremp[cham], r, c);
            }
          }
        }
        eraseElement(curremp[cham], i, j);
      } else if((c == 'H') || (c == 'W') || (c == 'L') || (c == 'E') 
        || (c == 'O') || (c == 'M')){
        map[i][j].createE(c);
        int c = map[i][j].getChamber() - 1;
        eraseElement(curremp[c], i, j);
        enemys.emplace_back(make_pair(i, j));
        shared_ptr<Observer> p{new Cell{map[i][j]}};
        map[x][y].attach(p);
      }
    }
  }
}

// Floor::display() displays the current floor(only under curses)
void Floor::display() {
  int u = map.size();
  for(int i = 0; i < u; i++) {
    int v = (map[i]).size();
    for(int j = 0; j < v; j++) {
      map[i][j].display();
    }
  }
  int y = 0;
  int x = 0;
  getyx(stdscr, y, x);
  mvaddstr(y + 1, x - 78, printFirst().c_str());
  map[players.first][players.second].getChar()->displayInfo();
  refresh(); 
}

Floor::~Floor() {}

ostream &operator<<(ostream &out, Floor &f) {
  int u = f.map.size();
  for(int i = 0; i < u; i++) {
    int v = (f.map[i]).size();
    for(int j = 0; j < v; j++) {
      cout << f.map[i][j];
    }
    cout << endl;
  }
  cout << f.printFirst() << endl;
  int r = f.players.first;
  int c = f.players.second;
  f.map[r][c].getChar()->printInfo();
  if(!f.bag.empty()) { // printf bag information
    cout << "Bag: ";
    int size = f.bag.size();
    for(int p = 0; p < size; p++) {
      cout << p << ":" << f.bag[p] << " " << endl;
    }
  }
  return out;
}

