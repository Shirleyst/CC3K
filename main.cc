#include "game.h"
#include <fstream>
#include <iostream>
#include <curses.h> 
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  Game g;
  string file;
  if(argc == 2) {
    cout << "You choose to read in a layout instead of a map" << endl;
    g.setRead();
    file = argv[1];
  } else {
    cout << "Please choose a map(enter name below):" << endl;
    if(!(cin >> file)) {
      cout << "You entered an invalid name, exit the game:(" << endl;
      return 0;
    }
  }
  ifstream iff{file};
  if(iff) {
    iff >> g;
  } else {
    cout << "You entered an invalid map, exit the game:(" << endl;
    return 0;
  }
  g.chooseRace();
  if(g.getRace() == "") {
    return 0;
  }
  cout << "Do you want to use inventory system?(y/n)" << endl;
  char i;
  if(cin >> i) {
    if(i == 'y') {
      g.setInv(true);
    }
  } else {
    cout << "Invalid answer, exit :(" << endl;
    return 0;
  }
  cout << "Do you want to use UI?(y/n)" << endl;
  char a;
  if(cin >> a) {
    if(a == 'y') {
      g.setUI(true);
    }
  } else {
    cout << "Invalid answer, exit :(" << endl;
    return 0;
  }
  g.generate();
  string s;
  if(a != 'y') {
    while(cin >> s) {
      //if(g.isLost()) break;
      //if(g.isWin()) break;
      if(s == "u") {
        if(cin >> s) {
          g.use(s);
        }
      } else if(s == "a") {
        if(cin >> s) {
          g.attack(s);
        }
      } else if(s == "q") {
        cout << "Exit" << endl;
        break;
      } else if(s == "f") {
        g.stop();
      } else if(s == "r") {
        g.restart();
      } else {
        g.move(s);
      }
      if(g.isLost()) break;
      if(g.isWin()) break;
    }
  } else {
    cbreak();
    noecho();
    char c = getch();
    while(c) {
      if(g.isLost()) break;
      if(g.isWin()) break;
      if(c == 'q') {
        break;
      } else if(c == 'r') {
        endwin();
        g.restart();
      } else if(c == 'f') {
        clear();
        g.stop();
      } else {
        clear();
        g.wasd(c);
      }
      if(g.isLost()) break;
      if(g.isWin()) break;
      c = getch();
    }
    endwin();
    g.setUI(false);
    if(!g.isLost()) g.isWin();
  }
  return 0;
}
