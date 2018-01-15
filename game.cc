#include "game.h"
#include "floor.h"
#include "cell.h"
#include "character.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <curses.h> 

using namespace std;

// cotr
Game::Game(): command{}, floors{}, base{}, emptys{},
race{""}, readIn{false}, numFloors{5}, currentFloor{0}, UI{false}, inv{false} {
  cout << "You have opened the game for CC3k :)" << endl;
}

// Game::getEmp() returns a list of empty cells in map
vector<Cell> Game::getEmp() { return emptys;}

// Game::getBase() returns the map of the game
vector <vector <Cell>> Game::getBase() {return base;}

// Game::getRace() returns the race of the player
string Game::getRace() {return race;}

void Game::chooseRace() {
  // need to choose a race
  cout << "Please pick a race for PC(enter any of the below):" << endl;
  cout << "d(Drow), g(Goblin), s(Shade), t(Troll), v(Vampire)." << endl;
  string racePC;
  if(cin >> racePC) {
    if(racePC == "d") race = "Drow";
    if(racePC == "g") race = "Goblin";
    if(racePC == "s") race = "Shade";
    if(racePC == "t") race = "Troll";
    if(racePC == "v") race = "Vampire";
    this->race = race;
    if(race == "") {
      cout << "No matching race, exit:(" << endl;
      return;
    }
  } else {
    cout << "Exit without begin :(" << endl;
    return;
  }
}

// Game::generate(hp, gold, state) generates a floor with given hp
void Game::generate(int hp, int gold, bool state) {
  if(race == "") {
    chooseRace();
  }
  // generate floors
  if(readIn) {
    floors->modify(hp, gold, state, this->race);
  } else {
    floors->generate(hp, gold, state, this->race);
  }
  if(UI) {
    display();
    string out = "Player character has spawned.";
    addstr(out.c_str());
    refresh();
  } else {
    cout << *floors;
    cout << "Player character has spawned." << endl;
  }
}

// Game::nextlevel(hp, gold, state) generates a new floor for the game
void Game::nextlevel(int hp, int gold, bool state) {
  currentFloor++;
  if(currentFloor != 5) {
    floors->floor_clear();
    if(readIn) {
      floors->modify(hp, gold, state, this->race);
    } else {
      floors->generate(hp, gold, state, race);
    }
    if(UI) {
      string out = "New floor has been generated.";
      mvaddstr(0, (COLS - out.length())/ 2, out.c_str());
      refresh();
    } else {
      cout << "New floor has been generated." << endl;
    }
  } else {
    isWin();
  }
}

// Game::isWin() returns true if the player enters 5 floor and false otherwise
bool Game::isWin() {
  if(currentFloor != 4) return false;
  if(UI) {
    string out = "Win!!!!!! You total score is" + to_string(floors->score());
    addstr(out.c_str());
    refresh();
  } else {
    cout << "Win!!!!!!" << endl;
    cout << "You total score is " << floors->score() << endl;
  }
  return true;
}

// Game::isLost() returns true if the player dies and false otherwise
bool Game::isLost() {
  if(floors->isLost()) {
    if(!UI) {
      cout << "You Lost" << endl;
    } else {
      string out = "You Lost";
      addstr(out.c_str());
      refresh();
    }
  }
  return floors->isLost();
}

// Game::stop() stops/moves enemys
void Game::stop() {
  floors->stop();
  if(UI) {
    display();
    string out = "Switch between Stop/Move mode.";
    addstr(out.c_str());
    refresh();
  } else {
    cout << (*this);
    cout << "Switch between Stop/Move mode." << endl;
  }
}

// Game::restart() restart the game
void Game::restart() {
  race = "";
  currentFloor = 0;
  floors->getPotion().clear();
  floors->floor_clear();
  this->generate();
}

// Game::setRead() sets readIn mode to true(no random generation)
void Game::setRead() {
  readIn = true;
}

// Game::setUI(u) sets UI to u(open curses or not)
void Game::setUI(bool u) {
  UI = u;
}

// Game::setInv(i) sets inventory system to i(active bag or not)
void Game::setInv(bool i) {
  inv = i;
}

// Game::move(comm) makes player to move with the given comm
void Game::move(string &comm) {
  command = comm;
  string pInfo = "";
  floors->move(comm, pInfo);
  if(UI) {
    display();
    return;
  }
  cout << (*this);
  cout << pInfo;
  cout << endl;
}

// Game::use(comm) makes player use potion with the given comm
void Game::use(string &comm) {
  string info = "";
  command = comm;
  floors->use(comm, info);
  if(UI) {
    display();
    return;
  }
  cout << (*this);
  cout << info;
  cout << endl;
}

void Game::put(string &comm) {
  string info = "";
  command = comm;
  floors->use_bag(comm, info);
  if(UI) {
    display();
    return;
  }
  cout << (*this);
  cout << info;
  cout << endl;
}

// Game::attack(comm) makes player to attack with the given comm
void Game::attack(string &comm) {
  string pInfo = "";
  command = comm;
  floors->attack(comm, pInfo);
  if(UI) {
    display();
    return;
  }
  cout << (*this);
  cout << pInfo;
  cout << endl;
}

// Game::wasd(char c) manipulate current floor based on given c
//   (only under curses)
void Game::wasd(char c) {
  string info = "";
  floors->WASD(c, info);
  floors->display();
  addstr(info.c_str());
  refresh();
}

// Game::checkChamber() determines the chamber of every cell in map
void Game::checkChamber() {
  int currChamber = 1;
  int r_l = base.size();
  int c_l = base[0].size();
  int u = emptys.size();
  for(int i = 0; i < u; i++) {
    if(emptys[i].getChamber() == 0) {
      emptys[i].getChamber() = currChamber;
      checkSurround(emptys[i], currChamber, r_l, c_l);
      currChamber++;
    }
  }
  for(int j = 0; j < u; j++) {
    int r = emptys[j].getRow();
    int c = emptys[j].getCol();
    base[r][c].getChamber() = emptys[j].getChamber();
  }
}

//  Game::checkSurround(middle, chamber, r_l, c_l) determines the chamber
//    of cells near middle with given r_l and c_l
void Game::checkSurround(Cell &middle, int chamber, int r_l, int c_l) {
  int r = middle.getRow();
  int c = middle.getCol();
  for(int x = max(0, r - 1); x <= min(r + 1, r_l); x++) {
    for(int y = max(0, c - 1); y <= min(c + 1, c_l); y++) {
      if(x != r || y != c) {
        int u = emptys.size();
        for(int i = 0; i < u; i++) {
          if((emptys[i].sameCell(make_pair(x, y)))
            && ((emptys[i]).getChamber() == 0)) {
            (emptys[i]).getChamber() = chamber;
            checkSurround(emptys[i], chamber, r_l, c_l);
          }
        }
      }
    }
  }
}

// dtor
Game::~Game() {}

// Game::display() displays the game (only under curses)
void Game::display() {
  initscr();
  box(stdscr, ACS_VLINE, ACS_HLINE);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  attron(COLOR_PAIR(2));
  floors->display();
  refresh();
}

istream &operator>>(istream &in, Game &g) {
  string l;
  char c;
  int row = 0;
  while(getline(in, l)) {
    vector<Cell> sub;
    (g.base).push_back(sub);
    int coloum = 0;
    stringstream ss{l};
    while(ss >> noskipws >> c) {
      Cell cell{c, row, coloum};
      if((c != '|') && (c != '+') && (c != '-') && (c != '#') && (c != ' ')) {
        g.emptys.push_back(cell);
      }
      g.base[row].push_back(cell);
      coloum++;
    }
    ss.str(string());
    row++;
  }
  g.checkChamber();
  unique_ptr<Floor> p{new Floor{g, 0}};
  std::swap(p, g.floors);
  return in;
}

ostream &operator<<(ostream &out, Game &g) {
  cout << (*g.floors);
  return out;
}
