#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
#include <utility>
#include <memory>
#include "cell.h"

class Character;
class Game;

class Floor {
  Game& theGame;
  std::vector <std::vector <Cell>> map;
  std::vector <std::vector <std::pair<int, int>>> curremp; // current empty cells
  std::vector <std::pair<int, int>> enemys; // current enemy cells
  std::pair<int, int> players; // current player cell
  std::vector<std::pair<int, int>> dragon;
  std::vector<std::pair<std::pair<int, int>, bool>> hoard;
  std::vector<int> bag;
  int numPotion;
  int numGold;
  int numEnemy;
  int floor; // current floor
  std::string command;
  bool m; // true if the enemy can move
  std::vector<std::string> potionType; 
  // track how many types of potion player used
  
  // generate map
  void generatePlayer(int hp, int gold, 
    bool state, std::string race, int &chamber);
  void createPlayer(int hp, int gold, bool state, 
    std::string race, int r, int c);
  void generateSW(int chamber);
  void generatePotion(int n);
  void generateGold(int n);
  bool generateHoard(int r, int c, int chamber);
  void generateDragon(int x, int y, int r, int c);
  void generateEnemy(int n);
  // player
  void walk(int &ax, int &ay, int x, int y);
  std::string drink(int x, int y);
  std::string put_bag(int x, int y);
  int hurt(int ax, int ay, int x, int y);
  // enemy
  bool enemy_should_attack(int x, int y, int &d);
  void newEnemy(int x, int y, int ax, int ay);
  // print
  std::string printFirst();
  std::string printSurround();
public:
  Floor(Game &g, int f);
  std::vector <std::vector <Cell>> &getMap();
  std::vector <std::vector <std::pair<int, int>>> &getcurrEmp();
  std::vector <std::pair<int, int>>& getEnemys();
  std::pair<int, int> &getPlayers();
  std::vector<std::string> &getPotion();
  int score();
  void floor_clear();

  // generate map
  void generate(int hp, int gold, bool state, std::string race);
  void modify(int hp, int gold, bool state, std::string race);
  
  // player
  void move(std::string &comm, std::string &info);
  void use(std::string &comm, std::string &info);
  void use_bag(std::string &comm, std::string &info);
  void attack(std::string &comm, std::string &info);
  void WASD(char c, std::string &info);
  
   // enemy
  int enemys_random_move(int x, int y);

  void stop();
  bool isLost();
  void display();

  virtual ~Floor();

  friend std::ostream &operator<<(std::ostream &out, Floor &f);
};

#endif
