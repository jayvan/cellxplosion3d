#include "enemy.hpp"
#include <iostream>
#include <GL/gl.h>

using namespace std;

char randomDigit() {
  return (rand() % 10) + 48;
}

Enemy::Enemy() : Mover(Point3D(), Vector3D(1, 1, 1)) {
  digitIndex = 0;

  position = Point3D(rand() % 20 - 10, rand() % 20 - 10, 0);

  // Generate the enemies number
  for (unsigned int i = 0; i < NUMBER_LENGTH; i++) {
    number.push_back(randomDigit());
  }

  speed = 1.0;
}

// Move closer to player
// Animate limbs and particle system
void Enemy::_update(double delta) {

}

void Enemy::render() {
  glColor3f(0.333333, 0.066667, 0.066667);
  glPushMatrix();
  glTranslated(position[0], position[1], position[2]);
  glBegin(GL_QUADS);

  // Front face
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 0.0);
  glVertex3d(1.0, 1.0, 0.0);
  glVertex3d(0.0, 1.0, 0.0);

  // Back Face
  glVertex3d(0.0, 0.0, 1.0);
  glVertex3d(1.0, 0.0, 1.0);
  glVertex3d(1.0, 1.0, 1.0);
  glVertex3d(0.0, 1.0, 1.0);

  // Top Face
  glVertex3d(0.0, 1.0, 0.0);
  glVertex3d(0.0, 1.0, 1.0);
  glVertex3d(1.0, 1.0, 1.0);
  glVertex3d(1.0, 1.0, 0.0);

  // Bottom Face
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 1.0);
  glVertex3d(1.0, 0.0, 1.0);
  glVertex3d(1.0, 0.0, 0.0);

  // Left Face
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 1.0, 0.0);
  glVertex3d(0.0, 1.0, 1.0);
  glVertex3d(0.0, 0.0, 1.0);

  // Right Face
  glVertex3d(1.0, 0.0, 0.0);
  glVertex3d(1.0, 1.0, 0.0);
  glVertex3d(1.0, 1.0, 1.0);
  glVertex3d(1.0, 0.0, 1.0);

  glEnd();
  glPopMatrix();
}
