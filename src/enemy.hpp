#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "algebra.hpp"
#include "mover.hpp"
#include <string>

class Enemy : public Mover {
  void init();

  std::string number;
  double speed;
  unsigned int digitIndex;

protected:
  void _update(double delta);

public:
  Enemy();
  Enemy(Point3D position);
  void render();
  bool tryDigit(char num);
  void advanceDigit();
  void resetDigit();
  bool tryDestroy();
};

#endif
