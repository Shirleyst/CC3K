#ifndef CELL_H
#define CELL_H
#include <utility>
#include <iostream>
#include "subject.h"
#include "observer.h"
#include <memory>

class Character;
class Floor;

class Cell : public Subject, public Observer{
  char content;
  int chamber; // the chamber this cell is in
  std::pair <int, int> coord;
  std::shared_ptr<Character> cha; // the character inside this cell
public:
  Cell(char c, int row, int col);
  char &getContent();
  int &getRow() override;
  int &getCol() override;
  int &getChamber();
  std::shared_ptr<Character> &getChar();

  bool sameCell(std::pair <int, int> c) override;
  bool isPlayerOrEnemy();

  void createPotion(std::shared_ptr<Character> c, int type);
  void createGold(std::shared_ptr<Character> c, int type);
  void createE(char race);
  virtual void printChar();
  void display();

  std::string notify(Floor &f, std::pair<int,int> coo, 
    Subject &whoNotified) override;
  
  ~Cell();

  friend std::ostream &operator<<(std::ostream &out, Cell &c);
};

#endif
