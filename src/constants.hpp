#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

struct CONSTANTS {
  // Game world
  static const double AREA_SIZE;
  static const double CAMERA_ANGLE;
  static const double CAMERA_ANGLE_RAD;
  static const double CAMERA_DISTANCE;
  static const double WALL_HEIGHT;
  static const double WALL_THICKNESS;
  static const GLfloat LIGHT_POSITION[];

  // Lighting
  static const unsigned int SHADOWMAP_MULT;

  // Player
  static const double PLAYER_SPEED;
  static const double ROTATION_SPEED;

  // Enemy
  static const unsigned int INITIAL_ENEMIES;
  static const unsigned int FORK_CHANCE;
  static const unsigned int NUMBER_LENGTH;
  static const double LIMB_TTL;
  static const double LIMB_VELOCITY;
  static const unsigned int ENEMY_SPEED_PROBABILITY[];
  static const double ENEMY_SPEEDS[];
  static const unsigned int ENEMY_DIFFICULTY_PROBABILITY[];
  static const double ENEMY_DIFFICULTIES[];
  static const unsigned int EXPLOSION_PARTICLES;

  // Data
  static const std::string DATA_PATH;

  // Models
  static const std::string MODEL_PATH;
  static const std::string PLAYER_MODEL_PATH;
  static const std::string ENEMY_MODEL_PATH;

  // Textures
  static const std::string FLOOR_TEXTURE_PATH;
  static const std::string WALL_TEXTURE_PATH;

  // Sound
  static const std::string MUSIC_PATH;
  static const std::string BACKGROUND_MUSIC;
  static const std::string DEATH_MUSIC;
  static const std::string SOUND_EFFECT_PATH;
  static const std::string DIAL_GOOD;
  static const unsigned int NUM_DIAL_GOOD;
  static const std::string DIAL_BAD;
  static const unsigned int NUM_DIAL_BAD;
  static const std::string ENEMY_DIE;
  static const unsigned int NUM_ENEMY_DIE;
  static const std::string EFFECT_SUFFIX;
};

double sample(const unsigned int probability[], const double values[]);

#endif
