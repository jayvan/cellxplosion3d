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
  size = node->get_size();
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
  velocity = PLAYER_SPEED * velocity;
}

void Player::_update(double delta) {
  (void)delta;
}

void Player::render() {
  glColor3f(0.0, 0.392157, 0.0);
  if (debug) {
    glColor3f(1.0, 0.5, 0.0);
  }

  glPushMatrix();
  glTranslated(position[0], position[1], position[2]);

  node->walk_gl();
  glPopMatrix();
}
