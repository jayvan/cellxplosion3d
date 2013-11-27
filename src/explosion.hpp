#include "particle.hpp"
#include "algebra.hpp"
#include <list>

// A starburst explosion particle emitter
class Explosion {
  Point3D position;
  std::list<Particle> particles;
  double time;

  void addParticles(unsigned int num);
  void addSmokeParticles(unsigned int num);

  public:
    void start(Point3D position);
    void update(double delta);
    void render();
};
