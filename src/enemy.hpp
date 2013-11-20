#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "algebra.hpp"
#include "mover.hpp"
#include "scene.hpp"
#include <string>

class Enemy : public Mover {
  std::string number;
  double speed;
  unsigned int digitIndex;
  double rotation;
  SceneNode* node;
  Mover& target;

protected:
  void _update(double delta);

public:
  Enemy();
  Enemy(Point3D position, Mover& target);
  void render();
  bool tryDigit(char num);
  void advanceDigit();
  void resetDigit();
  bool tryDestroy();
};

#endif
