#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "algebra.hpp"
#include "mover.hpp"

class Player : public Mover {
  static constexpr double PLAYER_SPEED = 10.0;
  bool moveDirection[4];

protected:
  void _update(double delta);

public:
  enum Direction {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3};
  bool debug;

  Player();
  void render();
  void setDirection(Direction direction, bool down);
};

#endif
