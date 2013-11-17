#ifndef __GAME_H__
#define __GAME_H__

#include "enemy.hpp"
#include "player.hpp"
#include "wall.hpp"
#include <list>

class Game {
  std::list<Enemy> enemies;
  std::list<Wall> walls;
  Player player;

public:
  Game();
  void update(double delta);
  void render();
  void handleKey(unsigned char key, bool down);
};

#endif
