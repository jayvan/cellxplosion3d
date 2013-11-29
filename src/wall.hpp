#ifndef __WALL_H__
#define __WALL_H__

#include "mover.hpp"
#include "algebra.hpp"

class Wall : public Mover {
protected:
  void _update(double delta);

  double rotation;

public:
  Wall(Point3D position, Vector3D size, double rotation);
  void render();
};

#endif
