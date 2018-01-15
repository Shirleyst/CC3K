#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include <memory>

class Floor;
class Cell;
class Character;

class Game {
protected:
  std::string command; // stores current commend
  std::unique_ptr<Floor> floors; // current floor
  std::vector <std::vector <Cell>> base; // base map
  std::vector <Cell> emptys;
  std::string race = "";
  bool readIn; // true if read in a given layout
  int numFloors;
  int currentFloor;
  bool UI;
  bool inv;

  void checkChamber();
  void checkSurround(Cell &middle, int chamber, int r_l, int c_l);
public:
  Game();
  std::vector <Cell> getEmp();
  std::vector <std::vector <Cell>> getBase();
  std::string getRace();
  void chooseRace();

  void generate(int hp = 0, int gold = 0, bool state = false);
  void nextlevel(int hp = 0, int gold = 0, bool state = false);
  
  bool isWin();
  bool isLost();
  void stop();
  void restart();
  void setRead();
  void setUI(bool u);
  void setInv(bool i);

  void move(std::string &comm);
  void use(std::string &comm);
  void put(std::string &comm);
  void attack(std::string &comm);
  void wasd(char c);
  
  ~Game();

  void display();
  friend std::istream &operator>>(std::istream &in, Game &g);
  friend std::ostream &operator<<(std::ostream &out, Game &g);
};


#endif
