#ifndef __GAME_H__
#define __GAME_H__

#include "enemy.hpp"
#include "player.hpp"
#include "wall.hpp"
#include "constants.hpp"
#include <list>
#include <string>

class Game {
  std::list<Enemy*> enemies;
  std::list<Enemy*> targetEnemies;
  std::list<Wall> walls;
  std::string number;
  Player player;

  GLuint frameBuffer;
  GLuint renderedTexture;
  GLuint depthBuffer;
  GLuint floorTexture;
  GLuint wallTexture;
  GLuint bufferVertices;
  double enemySpeedBoost;
  unsigned int enemyNumberBoost;
  unsigned int enemiesDefeated;
  unsigned int score;
  double gameOverTimeout;
  bool godMode;
  bool gameOver;
  bool neverPlayed;

  void loadSounds();
  void playBeep();
  void playError();
  void playBoom();
  void dial(char num);
  void submitNumber();
  void spawnEnemy();
  void renderFloor();
  void setFramebuffer();
  void drawFramebuffer();
  void drawGreeting();
  void drawGameover();
  void endGame();
  void reset();

  // Sound
  int musicId;
  int goodBeepsBase;
  int badBeepsBase;
  int boomsBase;
  int scream;

public:
  Game();
  ~Game();
  void update(double delta);
  void render();
  void handleKey(unsigned char key, bool down);
};

#endif
