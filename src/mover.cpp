#include "mover.hpp"
#include <iostream>

using namespace std;

unsigned int Mover::idCounter = 0;

Mover::Mover(Point3D position, Vector3D size) :
  position(position), size(size) { };

void Mover::update(double delta) {
  _update(delta);
  position = position + delta * velocity;
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
