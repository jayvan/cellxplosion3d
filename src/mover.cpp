#include "mover.hpp"
#include "constants.hpp"
#include <iostream>

using namespace std;

Mover::Mover(Point3D position, Vector3D size) :
  position(position), size(size) { };

void Mover::update(double delta) {
  _update(delta);
  velocity = velocity + delta * acceleration;
  position = position + delta * velocity;

  // Bounds check
  if (left() < 0)
    position[0] = 0;
  if (right() > CONSTANTS::AREA_SIZE)
    position[0] = CONSTANTS::AREA_SIZE - size[0];
  if (bottom() < 0)
    position[1] = 0;
  if (top() > CONSTANTS::AREA_SIZE)
    position[1] = CONSTANTS::AREA_SIZE - size[1];
  if (front() < 0)
    position[2] = 0;
}

Point3D Mover::getPosition() {
  return position;
}

// Only need to worry about 2d collisions for now
bool Mover::collidingWith(Mover &other) {
  return !(left() > other.right() ||
           right() < other.left() ||
           top() < other.bottom() ||
           bottom() > other.top());
}
