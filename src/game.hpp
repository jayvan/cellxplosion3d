#ifndef __GAME_H__
#define __GAME_H__

#include "enemy.h"

class Game {
  List<Enemy> enemies;

public:
  void update(double delta);
};

#endif
