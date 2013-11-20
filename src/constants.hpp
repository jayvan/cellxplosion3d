#include <string>

struct CONSTANTS {
  // Game world
  static const double AREA_SIZE;
  static const double CAMERA_ANGLE;
  static const double CAMERA_ANGLE_RAD;
  static const double CAMERA_DISTANCE;
  static const double WALL_HEIGHT;
  static const double WALL_THICKNESS;

  // Player
  static const double ROTATION_SPEED;

  // Enemy
  static const unsigned int INITIAL_ENEMIES;
  static const unsigned int NUMBER_LENGTH;

  // Data
  static const std::string DATA_PATH;

  // Models
  static const std::string MODEL_PATH;
  static const std::string PLAYER_MODEL_PATH;
  static const std::string ENEMY_MODEL_PATH;

  // Sound
  static const std::string MUSIC_PATH;
  static const std::string BACKGROUND_MUSIC;
  static const std::string DEATH_MUSIC;
};
