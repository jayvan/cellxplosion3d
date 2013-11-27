#include "game.hpp"
#include "constants.hpp"

#include <list>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

Game::Game() {
  // Spawn enemies
  for (unsigned int i = 0; i < CONSTANTS::INITIAL_ENEMIES; i++) {
    spawnEnemy();
  }

  // Spawn Walls
  // Bottom
  walls.push_back(Wall(Point3D(0.0, -(CONSTANTS::WALL_THICKNESS), 0.0),
        Vector3D(CONSTANTS::AREA_SIZE, CONSTANTS::WALL_THICKNESS, CONSTANTS::WALL_HEIGHT)));
  // Left
  walls.push_back(Wall(Point3D(-(CONSTANTS::WALL_THICKNESS), 0, 0),
        Vector3D(CONSTANTS::WALL_THICKNESS, CONSTANTS::AREA_SIZE, CONSTANTS::WALL_HEIGHT)));
  // Top
  walls.push_back(Wall(Point3D(0, CONSTANTS::AREA_SIZE, 0),
        Vector3D(CONSTANTS::AREA_SIZE, CONSTANTS::WALL_THICKNESS, CONSTANTS::WALL_HEIGHT)));
  // Right
  walls.push_back(Wall(Point3D(CONSTANTS::AREA_SIZE, 0, 0),
        Vector3D(CONSTANTS::WALL_THICKNESS, CONSTANTS::AREA_SIZE, CONSTANTS::WALL_HEIGHT)));
}

Game::~Game() {
  for (Enemy* enemy : enemies) {
    delete enemy;
  }
}

void Game::handleKey(unsigned char key, bool down) {
  // Movement keys
  switch (key) {
    case 'w':
    case 'W':
      player.setDirection(Player::UP, down);
      break;
    case 's':
    case 'S':
      player.setDirection(Player::DOWN, down);
      break;
    case 'a':
    case 'A':
      player.setDirection(Player::LEFT, down);
      break;
    case 'd':
    case 'D':
      player.setDirection(Player::RIGHT, down);
      break;
    case 13: // Enter
      submitNumber();
      break;
  }

  // Dialing keys
  if (down && key >= '0' && key <= '9') {
    dial(key);
  }
}

// Calls the update methods of each game component
void Game::update(double delta) {
  player.update(delta);

  // Update enemies
  list<Enemy*>::iterator it = enemies.begin();
  while (it != enemies.end()) {
    Enemy* enemy = *it;
    if (enemy->isGone()) {
      it = enemies.erase(it);
    } else {
      enemy->update(delta);
      list<Enemy*>::iterator other = enemies.begin();
      while (other != it) {
        enemy->rebound(**other);
        other++;
      }
      it++;
    }
  }
}

void Game::spawnEnemy() {
  double degree = (2.0 * M_PI) * (double)(rand() % 1000) / 1000;
  double xPosition = cos(degree) * CONSTANTS::AREA_SIZE / 3 + CONSTANTS::AREA_SIZE / 2;
  double yPosition = sin(degree) * CONSTANTS::AREA_SIZE / 3 + CONSTANTS::AREA_SIZE / 2;
  Point3D enemyPosition(xPosition, yPosition, 0);
  Enemy* enemy = new Enemy(enemyPosition, player);
  enemies.push_back(enemy);
  if (number.length() == 0) {
    targetEnemies.push_back(enemy);
  }
}

// Try dialing the given digit by checking if it is the next digit for any enemy
void Game::dial(char digit) {
  list<Enemy*> validEnemies;
  list<Enemy*> invalidEnemies;

  // Go through each enemy and find which ones have the given number as their next digit
  for (Enemy* enemy : targetEnemies) {
    if (enemy->tryDigit(digit)) {
      validEnemies.push_back(enemy);
    } else {
      invalidEnemies.push_back(enemy);
    }
  }

  // If there were any valid enemies then
  // - Set the new target list to the valid enemies
  // - Increment the digit index for valid enemies
  // - Reset the digit index for invalid enemies
  if (validEnemies.size() > 0) {
    number.push_back(digit);
    targetEnemies = validEnemies;

    for (Enemy* enemy : validEnemies) {
      enemy->advanceDigit();
    }

    for (Enemy* enemy : invalidEnemies) {
      enemy->resetDigit();
    }
  }
}

// If any of the enemies numbers match our number, destroy them
// Always clear the players number
void Game::submitNumber() {
  list<Enemy*>::iterator it = enemies.begin();
  while (it != enemies.end()) {
    bool destroyed = (*it)->tryDestroy();

    if (destroyed) {
      spawnEnemy();
      spawnEnemy();
    } else {
      (*it)->resetDigit();
      it++;
    }
  }

  targetEnemies = enemies;
  number = "";
}

// Draw all of the game components
void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glLoadIdentity(); // Reset the view

  Point3D playerPosition = player.getPosition();
  glRotated(-CONSTANTS::CAMERA_ANGLE, 1.0, 0, 0);
  glTranslated(-playerPosition[0] - 0.5,
               -playerPosition[1] + (CONSTANTS::CAMERA_DISTANCE * tan(CONSTANTS::CAMERA_ANGLE_RAD)) - 0.5,
               -CONSTANTS::CAMERA_DISTANCE);

  // Draw enemies
  for (Enemy* enemy : enemies) {
    enemy->render();
  }

  // Draw walls
  for (Wall wall : walls) {
    wall.render();
  }

  player.render();
}
