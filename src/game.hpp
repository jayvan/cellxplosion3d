#ifndef __GAME_H__
#define __GAME_H__

#include "enemy.hpp"
#include "player.hpp"
#include "wall.hpp"
#include <list>
#include <string>

class Game {
  std::list<Enemy*> enemies;
  std::list<Enemy*> targetEnemies;
  std::list<Wall> walls;
  std::string number;
  Player player;

  GLuint floorTexture;
  GLuint wallTexture;
  double enemySpeedBoost;
  unsigned int enemyNumberBoost;
  unsigned int enemiesDefeated;
  unsigned int score;

  void dial(char num);
  void submitNumber();
  void spawnEnemy();
  void renderFloor();

public:
  Game();
  ~Game();
  void update(double delta);
  void render();
  void handleKey(unsigned char key, bool down);
};

#endif
