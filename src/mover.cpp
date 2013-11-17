#include "mover.hpp"

void Mover::update(double delta) {
  _update(delta);
  position = position + delta * velocity;
}

Point3D Mover::getPosition() {
  return position;
}
