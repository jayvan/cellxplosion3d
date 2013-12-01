#include <list>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL.h>
#include <math.h>

#include <iostream>
#include "game.hpp"
#include "SoundManager.hpp"
#include "shader.hpp"

using namespace std;

extern shaderProgram g_shader;

Game::Game() {
  enemySpeedBoost = 0;
  enemyNumberBoost = 0;
  enemiesDefeated = 0;
  score = 0;

  floorTexture = SOIL_load_OGL_texture(CONSTANTS::FLOOR_TEXTURE_PATH.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS);
  wallTexture = SOIL_load_OGL_texture(CONSTANTS::WALL_TEXTURE_PATH.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS);

  // Spawn enemies
  for (unsigned int i = 0; i < CONSTANTS::INITIAL_ENEMIES; i++) {
    spawnEnemy();
  }

  // Spawn Walls
  // Bottom
  walls.push_back(Wall(Point3D(0.0, -(CONSTANTS::WALL_THICKNESS), 0.0),
        Vector3D(CONSTANTS::AREA_SIZE, CONSTANTS::WALL_THICKNESS, CONSTANTS::WALL_HEIGHT), 0.0));
  // Left
  walls.push_back(Wall(Point3D(0.0, 0.0 , 0.0),
        Vector3D(CONSTANTS::AREA_SIZE, CONSTANTS::WALL_THICKNESS, CONSTANTS::WALL_HEIGHT), 90.0));
  // Top
  walls.push_back(Wall(Point3D(0, CONSTANTS::AREA_SIZE, 0),
        Vector3D(CONSTANTS::AREA_SIZE, CONSTANTS::WALL_THICKNESS, CONSTANTS::WALL_HEIGHT), 0.0));
  // Right
  walls.push_back(Wall(Point3D(0.0, -CONSTANTS::AREA_SIZE - CONSTANTS::WALL_THICKNESS, 0.0),
        Vector3D(CONSTANTS::AREA_SIZE, CONSTANTS::WALL_THICKNESS, CONSTANTS::WALL_HEIGHT), 90.0));

  loadSounds();
}

Game::~Game() {
  for (Enemy* enemy : enemies) {
    delete enemy;
  }
}

void Game::loadSounds() {
  goodBeepsBase = badBeepsBase = boomsBase = -1;

  // Load background music
  musicId = SM.LoadMusic(CONSTANTS::BACKGROUND_MUSIC);
  SM.PlayMusic(musicId);

  // Load beeps
  for (unsigned int i = 1; i <= CONSTANTS::NUM_DIAL_GOOD; i++) {
    string path = CONSTANTS::DIAL_GOOD;
    path.append(string(to_string(i)));
    path.append(CONSTANTS::EFFECT_SUFFIX);
    if (goodBeepsBase == -1) {
      goodBeepsBase = SM.LoadSound(path);
    } else {
      SM.LoadSound(path);
    }
  }

  // load bad beeps
  for (unsigned int i = 1; i <= CONSTANTS::NUM_DIAL_BAD; i++) {
    string path = CONSTANTS::DIAL_BAD;
    path.append(string(to_string(i)));
    path.append(CONSTANTS::EFFECT_SUFFIX);
    if (badBeepsBase == -1) {
      badBeepsBase = SM.LoadSound(path);
    } else {
      SM.LoadSound(path);
    }
  }

  // load booms
  for (unsigned int i = 1; i <= CONSTANTS::NUM_ENEMY_DIE; i++) {
    string path = CONSTANTS::ENEMY_DIE;
    path.append(string(to_string(i)));
    path.append(CONSTANTS::EFFECT_SUFFIX);
    if (boomsBase == -1) {
      boomsBase = SM.LoadSound(path);
    } else {
      SM.LoadSound(path);
    }
  }

}

void Game::playBeep() {
  int beepNum = rand() % CONSTANTS::NUM_DIAL_GOOD + goodBeepsBase;
  SM.PlaySound(beepNum);
}

void Game::playError() {
  int beepNum = rand() % CONSTANTS::NUM_DIAL_BAD + badBeepsBase;
  SM.PlaySound(beepNum);
}

void Game::playBoom() {
  int boomNum = rand() % CONSTANTS::NUM_ENEMY_DIE + boomsBase;
  SM.PlaySound(boomNum);
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
  Point3D enemyPosition = player.getPosition();

  while((enemyPosition - player.getPosition()).length() < CONSTANTS::PLAYER_SPEED * 2) {
    double degree = (2.0 * M_PI) * (double)(rand() % 1000) / 1000;
    double xPosition = cos(degree) * CONSTANTS::AREA_SIZE / 2 + CONSTANTS::AREA_SIZE / 2;
    double yPosition = sin(degree) * CONSTANTS::AREA_SIZE / 2 + CONSTANTS::AREA_SIZE / 2;
    enemyPosition = Point3D(xPosition, yPosition, 0);
  }

  Enemy* enemy = new Enemy(enemyPosition, player, enemySpeedBoost, enemyNumberBoost);
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

    playBeep();
  } else {
    playError();
  }
}

// If any of the enemies numbers match our number, destroy them
// Always clear the players number
void Game::submitNumber() {
  list<Enemy*>::iterator it = enemies.begin();
  while (it != enemies.end()) {
    bool destroyed = (*it)->tryDestroy();

    if (destroyed) {
      score += 100;
      enemiesDefeated++;
      if (enemiesDefeated % 10 == 0) {
        enemySpeedBoost += 0.25;
      }
      if (enemiesDefeated % 25 == 0) {
        enemyNumberBoost++;
      }

      spawnEnemy();

      if ((unsigned int)rand() % 100 < CONSTANTS::FORK_CHANCE) {
        spawnEnemy();
      }

      playBoom();
    } else {
      (*it)->resetDigit();
      it++;
    }
  }

  targetEnemies = enemies;
  number = "";
}

void Game::renderFloor() {
  GLfloat floor_colour[] = {1.0, 1.0, 1.0, 1.0};
  glBindTexture(GL_TEXTURE_2D, floorTexture);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floor_colour);
  glBegin(GL_TRIANGLE_STRIP);
  glTexCoord2s(2,2);
  glVertex3f(CONSTANTS::AREA_SIZE, CONSTANTS::AREA_SIZE, 0);
  glTexCoord2s(0,2);
  glVertex3f(0, CONSTANTS::AREA_SIZE, 0);
  glTexCoord2s(2,0);
  glVertex3f(CONSTANTS::AREA_SIZE, 0, 0);
  glTexCoord2s(0,0);
  glVertex3f(0, 0, 0);
  glEnd();
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

  glBindTexture(GL_TEXTURE_2D, wallTexture);
  g_shader.setActive(shaderProgram::TEXTURE);
  // Draw walls
  for (Wall wall : walls) {
    wall.render();
  }

  // Draw floor
  renderFloor();

  player.render();
}
