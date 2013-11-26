#ifndef __MOVER_H__
#define __MOVER_H__

#include "algebra.hpp"
#include <vector>

class Mover {
public:
  typedef std::vector<Mover*> CollisionList;

protected:
  Point3D position;
  Vector3D size;
  Vector3D velocity;
  Vector3D acceleration;
  virtual void _update(double delta) = 0;

public:
  Mover(Point3D position, Vector3D size);
  void update(double delta);
  bool collidingWith(Mover &other);
  void rebound(Mover &other);

  Point3D getPosition();

  // Convenience methods
  inline double left() {
    return position[0];
  }

  inline double right() {
    return position[0] + size[0];
  }

  inline double bottom() {
    return position[1];
  }

  inline double top() {
    return position[1] + size[1];
  }

  inline double front() {
    return position[2];
  }

  inline double back() {
    return position[2] + size[2];
  }

  inline Point3D center() {
    return position + 0.5 * size;
  }
};

#endif
