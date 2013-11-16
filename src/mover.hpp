#ifndef __MOVER_H__
#define __MOVER_H__

#include "algebra.hpp"

class Mover {
protected:
  Point3D position;
  Vector3D velocity;
  virtual void _update(double delta) = 0;

public:
  void update(double delta);
};

#endif
