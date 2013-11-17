#ifndef __WALL_H__
#define __WALL_H__

#include "mover.hpp"
#include "algebra.hpp"

class Wall : public Mover {
protected:
  void _update(double delta);

public:
  Wall(Point3D position, Vector3D size);
  void render();
};

#endif
