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
    double degree = (2.0 * M_PI) * ((double)i / (double)CONSTANTS::INITIAL_ENEMIES);
    cout << degree << endl;
    double xPosition = cos(degree) * CONSTANTS::AREA_SIZE / 3 + CONSTANTS::AREA_SIZE / 2;
    double yPosition = sin(degree) * CONSTANTS::AREA_SIZE / 3 + CONSTANTS::AREA_SIZE / 2;
    Point3D enemyPosition(xPosition, yPosition, 0);
    cout << enemyPosition << endl;
    enemies.push_back(Enemy(enemyPosition));
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

void Game::handleKey(unsigned char key, bool down) {
  switch (key) {
    case 'w':
      player.setDirection(Player::UP, down);
      break;
    case 's':
      player.setDirection(Player::DOWN, down);
      break;
    case 'a':
      player.setDirection(Player::LEFT, down);
      break;
    case 'd':
      player.setDirection(Player::RIGHT, down);
      break;
  }
}

// Calls the update methods of each game component
void Game::update(double delta) {
  player.update(delta);
  player.debug = false;

  // Update enemies
  for (Enemy enemy : enemies) {
    enemy.update(delta);
    if (enemy.collidingWith(player)) {
      player.debug = true;
    }
  }
}

// Draw all of the game components
void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glLoadIdentity(); // Reset the view

  Point3D playerPosition = player.getPosition();
  glTranslated(-playerPosition[0], -playerPosition[1], -25.0);

  // Draw enemies
  for (Enemy enemy : enemies) {
    enemy.render();
  }

  // Draw walls
  for (Wall wall : walls) {
    wall.render();
  }

  player.render();

}
