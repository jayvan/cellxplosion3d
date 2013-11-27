#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "algebra.hpp"
#include "mover.hpp"

class Particle : public Mover {
  Colour startColour;
  Colour endColour;

  double lifetime;
  double age;

  protected:
  void _update(double delta);

  public:
    Particle(Point3D position, Vector3D velocity, Colour startColour, Colour endColour, double width, double lifetime);
    void render();
};

#endif
