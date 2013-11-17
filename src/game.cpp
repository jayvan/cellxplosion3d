#include "game.hpp"
#include <list>
#include <GL/gl.h>
#include <iostream>

using namespace std;

Game::Game() {
  // Spawn enemies
  for (unsigned int i = 0; i < INITIAL_ENEMIES; i++) {
    enemies.push_back(Enemy());
  }
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

  player.render();
}
