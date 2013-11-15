#include "game.hpp"
#include <list>
#include <GL/gl.h>

Game::Game() {
  // Spawn enemies
  for (unsigned int i = 0; i < INITIAL_ENEMIES; i++) {
    enemies.push_back(Enemy());
  }
}

// Calls the update methods of each game component
void Game::update(double delta) {
  // Update enemies
  for (Enemy enemy : enemies) {
    enemy.update(delta);
  }
}

// Draw all of the game components
void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glLoadIdentity(); // Reset the view

  glTranslated(0.0, 0.0, -10.0);


  // Draw enemies
  for (Enemy enemy : enemies) {
    enemy.render();
  }
}
