#include "enemy.hpp"
#include "constants.hpp"
#include "scene_lua.hpp"

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

char randomDigit() {
  return (rand() % 10) + 48;
}

Enemy::Enemy(Point3D position, Mover& target) : Mover(position, Vector3D(1, 1, 1)), target(target) {
  node = import_lua(CONSTANTS::ENEMY_MODEL_PATH);
  rotation = 0;

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
  (void)delta;
  // Look at player
  Vector3D toPlayer = target.getPosition() - position;
  double newRotation = atan2(toPlayer[1], toPlayer[0]);
  node->rotate('y', (newRotation - rotation) * 180.0 / M_PI);
  rotation = newRotation;

  velocity = toPlayer;
  velocity.normalize();
  velocity = speed * velocity;
}

bool Enemy::tryDigit(char num) {
  return number[digitIndex] == num;
}

void Enemy::advanceDigit() {
  digitIndex++;
}

void Enemy::resetDigit() {
  digitIndex = 0;
}

bool Enemy::tryDestroy() {
  return digitIndex == number.length();
}

void Enemy::render() {
  // Model
  glPushMatrix();
  glTranslated(position[0], position[1], position[2]);
  node->walk_gl();

  glDisable(GL_LIGHTING);
  // Number
  float green[] = {0.0, 0.392157, 0.0};
  float red[] = {0.333333, 0.066667, 0.066667};
  glColor3fv(green);
  glRasterPos2d(0 , -0.4);
  for (unsigned int i = 0; i < number.length(); i++) {
    // Change to red for untyped portion
    if (i == digitIndex) {
      glColor3fv(red);
      glRasterPos2d(0.2425 * digitIndex, -0.4);
    }
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, number[i]);
  }
  glEnable(GL_LIGHTING);

  glPopMatrix();
}
