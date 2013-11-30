#include "particle.hpp"
#include "algebra.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

Particle::Particle(Point3D position, Vector3D vel, Colour colour, Colour endColour, double width, double lifetime) :
    Mover(position, Vector3D()), startColour(colour), endColour(endColour), lifetime(lifetime)
{
  velocity = vel;
  size[0] = width / 2;
}

void Particle::_update(double delta) {
  age += delta;
}

void Particle::render() {
  if (age > lifetime) return;

  Colour colour = startColour.lerp(endColour, age / lifetime);
  glColor3f(colour.R(), colour.G(), colour.B());
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(position[0]+size[0], position[1]+size[0], position[2] + size[0]);
  glVertex3f(position[0]-size[0], position[1]+size[0], position[2] + size[0]);
  glVertex3f(position[0]+size[0], position[1]-size[0], position[2] + size[0]);
  glVertex3f(position[0]-size[0], position[1]-size[0], position[2] + size[0]);
  glEnd();
}
