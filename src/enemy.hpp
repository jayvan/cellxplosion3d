#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "algebra.hpp"
#include "mover.hpp"
#include <string>

class Enemy : public Mover {
  static const unsigned int NUMBER_LENGTH = 5;

  std::string number;
  double speed;
  unsigned int digitIndex;

protected:
  void _update(double delta);

public:
  Enemy();
  void render();
};

#endif
