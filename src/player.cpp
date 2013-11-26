#include "player.hpp"
#include "constants.hpp"
#include "scene_lua.hpp"

#include <GL/gl.h>
#include <iostream>

using namespace std;

Player::Player() : Mover(Point3D(CONSTANTS::AREA_SIZE / 2, CONSTANTS::AREA_SIZE / 2, 0),
                   Vector3D(1,1,1)) {
  for (unsigned int i = 0; i < 4; i++) {
    moveDirection[i] = false;
  }

  node = import_lua(CONSTANTS::PLAYER_MODEL_PATH);
  rotation = 0;
  desiredRotation = 0;
}

Player::~Player() {
  delete node;
}

void Player::setDirection(Direction direction, bool down) {
  moveDirection[direction] = down;

  // Recalculate velocity
  // We don't do this relative to just the current key event because we may miss an event
  // e.g. we don't 'hear' the keyUp, so the next keyDown doubles the player speed

  double yVelocity = 0;
  double xVelocity = 0;

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
  velocity = CONSTANTS::PLAYER_SPEED * velocity;

  if (velocity.length2() == 0) {
    return;
  }

  desiredRotation = atan2(yVelocity, xVelocity) * 180.0 / M_PI;
  if (desiredRotation < 0) desiredRotation += 360;
}

void Player::_update(double delta) {
  double rotDiff = delta * CONSTANTS::ROTATION_SPEED;

  if (abs(rotation - desiredRotation) < rotDiff) {
    node->rotate('y', desiredRotation - rotation);
    rotation = desiredRotation;
    return;
  }


  double clockwiseDist = desiredRotation - rotation;
  if (clockwiseDist < 0) clockwiseDist += 360;

  double counterclockwiseDist = rotation - desiredRotation;
  if (counterclockwiseDist < 0) counterclockwiseDist += 360;

  if (clockwiseDist > counterclockwiseDist) {
    rotation -= rotDiff;
    node->rotate('y', -rotDiff);
  } else {
    rotation += rotDiff;
    node->rotate('y', rotDiff);
  }
  if (rotation < 0) rotation += 360;
  if (rotation > 360) rotation -= 360;
}

void Player::render() {
  glPushMatrix();
  glTranslated(position[0], position[1], position[2]);
  node->walk_gl();
  glPopMatrix();
}
