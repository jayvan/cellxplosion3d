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
  timeLeft = CONSTANTS::LIMB_TTL;
  destroyed = false;

  // Generate the enemies number
  for (unsigned int i = 0; i < CONSTANTS::NUMBER_LENGTH; i++) {
    number.push_back(randomDigit());
  }

  speed = 1.0;
}

Enemy::~Enemy() {
}

// Move closer to player
// Animate limbs and particle system
void Enemy::_update(double delta) {
  if (timeLeft < 0) return;

  if (destroyed) {
    for (Limb* limb : limbs) {
      limb->update(delta);
    }
    timeLeft -= delta;
    if (timeLeft < 0) {
      for (Limb* limb : limbs) {
        delete limb;
      }
    }
  } else {
    // Look at player
    Vector3D toPlayer = target.getPosition() - position;
    double newRotation = atan2(toPlayer[1], toPlayer[0]);
    node->rotate('y', (newRotation - rotation) * 180.0 / M_PI);
    rotation = newRotation;

    velocity = toPlayer;
    velocity.normalize();
    velocity = speed * velocity;
  }
}

bool Enemy::isGone() {
  return timeLeft < 0;
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
  if (destroyed) return false;

  destroyed = digitIndex == number.length();

  if (destroyed) {
    SceneNode::ChildList limbNodes = node->explode();
    for (SceneNode* limb_node : limbNodes) {
      limbs.push_back(new Limb(limb_node, position, velocity));
    }
    velocity = Vector3D();
    position = Point3D() + CONSTANTS::AREA_SIZE * 2 * Vector3D();
  }

  return destroyed;
}

void Enemy::render() {
  if (isGone()) return;
  // Model
  glPushMatrix();
  if (destroyed) {
    for (Enemy::Limb* limb : limbs) {
      limb->render();
    }
  } else {
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
  }

  glPopMatrix();
}

Enemy::Limb::Limb(SceneNode* node, Point3D position, Vector3D vel) : Mover(position, Vector3D()), node(node) {
  velocity = -1 * vel;
  velocity.normalize();
  velocity = velocity + Vector3D(rand() % 10 / 10.0, rand() % 10 / 10.0, 1.0);
  velocity.normalize();
  velocity = CONSTANTS::LIMB_VELOCITY * velocity;
  acceleration = Vector3D(0.0, 0.0, -5.0);
}

void Enemy::Limb::_update(double delta) {
  (void)delta;
  rotation += 1.0;
}

void Enemy::Limb::render() {
  glPushMatrix();
  glTranslated(position[0], position[1], position[2]);
  glRotated(rotation, 0, 0, 1);
  node->walk_gl();
  glPopMatrix();
}
