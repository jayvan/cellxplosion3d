#include "explosion.hpp"
#include "constants.hpp"
#include <GL/gl.h>
#include <iostream>

using namespace std;

void Explosion::start(Point3D position) {
  position[2] = 1;
  Explosion::position = position;
  addParticles(CONSTANTS::EXPLOSION_PARTICLES);
}

void Explosion::update(double delta) {
  if (time < 0.2) {
    addParticles((unsigned int)rand() % 10);
    addSmokeParticles(rand() % 7);
  }


  time += delta;

  list<Particle>::iterator it = particles.begin();
  while (it != particles.end()) {
    it->update(delta);
    it++;
  }
}

void Explosion::render() {

  glDisable(GL_LIGHTING);
  for (Particle p : particles) {
    p.render();
  }
  glEnable(GL_LIGHTING);
}

void Explosion::addSmokeParticles(unsigned int num) {
  for (unsigned int i = 0; i < num; i++) {
    Vector3D trajectory = Vector3D(rand() % 2000 / 1000.0 - 1,
                                   rand() % 2000 / 1000.0 - 1,
                                   rand() % 1000 / 1000.0);

    Colour colour(0.5, 0.5, 0.5);
    Colour endColour(0.75, 0.75, 0.75);
    trajectory.normalize();
    trajectory = 0.5 * trajectory;
    double lifetime = 0.5 + rand() % 1000 / 1000.0;

    particles.push_back(Particle(position, trajectory, colour, endColour, 0.06, lifetime));
  }
}

void Explosion::addParticles(unsigned int num) {
  for (unsigned int i = 0; i < num; i++) {
    Vector3D trajectory = Vector3D(rand() % 2000 / 1000.0 - 1,
                                   rand() % 2000 / 1000.0 - 1,
                                   rand() % 1000 / 1000.0);
    Colour colour(1.0, 0.0, 0.0);
    Colour endColour(1.0, 0.75, 0.0);
    trajectory.normalize();
    trajectory = 3 * trajectory;
    double lifetime = 0.0 + rand() % 1000 / 2000.0;

    particles.push_back(Particle(position, trajectory, colour, endColour, 0.04, lifetime));
  }
}
