#include "enemy.hpp"
#include "constants.hpp"
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

char randomDigit() {
  return (rand() % 10) + 48;
}

Enemy::Enemy(Point3D position) : Mover(position, Vector3D(1, 1, 1)) {
  init();
}

Enemy::Enemy() : Mover(Point3D(), Vector3D(1, 1, 1)) {
  init();
}

void Enemy::init() {
  digitIndex = 0;

  // Generate the enemies number
  for (unsigned int i = 0; i < CONSTANTS::NUMBER_LENGTH; i++) {
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

  glColor3f(1.0, 0, 0);
  glRasterPos2d(0 , -0.4);
  for (char c : number) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }

  glPopMatrix();
}
