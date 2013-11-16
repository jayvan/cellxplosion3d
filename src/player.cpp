#include "player.hpp"
#include <GL/gl.h>
#include <iostream>

using namespace std;

Player::Player() {
  for (unsigned int i = 0; i < 4; i++) {
    moveDirection[i] = false;
  }
}

void Player::setDirection(Direction direction, bool down) {
  moveDirection[direction] = down;

  // Recalculate velocity
  // We don't do this relative to just the current key event because we may miss an event
  // e.g. we don't 'hear' the keyUp, so the next keyDown doubles the player speed

  double yVelocity, xVelocity = 0;

  if (moveDirection[UP])
    yVelocity++;
  if (moveDirection[DOWN])
    yVelocity--;
  if (moveDirection[LEFT])
    xVelocity--;
  if (moveDirection[RIGHT])
    xVelocity++;

  velocity = Vector3D(xVelocity, yVelocity, 0);
  velocity.normalize();
  velocity = PLAYER_SPEED * velocity;
}

void Player::_update(double delta) {
}

void Player::render() {
  glColor3f(0.0, 0.392157, 0.0);
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
