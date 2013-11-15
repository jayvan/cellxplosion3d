#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "algebra.hpp"
#include <string>

class Enemy {
  static const unsigned int NUMBER_LENGTH = 5;

  Point3D position;
  std::string number;
  double speed;
  unsigned int digitIndex;
public:
  void update(double delta);
  void render();
  Enemy();
};

#endif
