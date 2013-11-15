#ifndef __GAME_H__
#define __GAME_H__

#include "enemy.hpp"
#include <list>

class Game {
  static const unsigned int INITIAL_ENEMIES = 5;
  std::list<Enemy> enemies;

public:
  Game();
  void update(double delta);
  void render();
};

#endif
