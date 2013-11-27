#include "constants.hpp"
#include "math.h"

// Game World
const double CONSTANTS::AREA_SIZE        =   25.0;
const double CONSTANTS::CAMERA_ANGLE     =   20.0;
const double CONSTANTS::CAMERA_ANGLE_RAD =   CONSTANTS::CAMERA_ANGLE * M_PI / 180.0;
const double CONSTANTS::CAMERA_DISTANCE  =   20.0;
const double CONSTANTS::WALL_HEIGHT      =   3.0;
const double CONSTANTS::WALL_THICKNESS   =   2.0;

// Player
const double CONSTANTS::PLAYER_SPEED = 5.0;
const double CONSTANTS::ROTATION_SPEED = 720.0;

// Enemy
const unsigned int  CONSTANTS::INITIAL_ENEMIES  =   5;
const unsigned int  CONSTANTS::FORK_CHANCE      =   20;
const unsigned int  CONSTANTS::NUMBER_LENGTH    =   5;
const double        CONSTANTS::LIMB_TTL         =   1.5;
const double        CONSTANTS::LIMB_VELOCITY    =   6.0;
const unsigned int  CONSTANTS::ENEMY_SPEED_PROBABILITY[] = {1, 1, 5, 14, 79};
const double        CONSTANTS::ENEMY_SPEEDS[] = {4.5, 4.0, 3.0, 2.0, 1.0};
const unsigned int  CONSTANTS::ENEMY_DIFFICULTY_PROBABILITY[] = {1, 5, 10, 14, 70};
const double        CONSTANTS::ENEMY_DIFFICULTIES[] = {7, 6, 5, 4, 3};

// Data
const std::string CONSTANTS::DATA_PATH = "../data/";

// Models
const std::string CONSTANTS::MODEL_PATH = DATA_PATH + "models/";
const std::string CONSTANTS::PLAYER_MODEL_PATH = MODEL_PATH + "player.lua";
const std::string CONSTANTS::ENEMY_MODEL_PATH = MODEL_PATH + "enemy.lua";

// Sound
const std::string CONSTANTS::MUSIC_PATH = DATA_PATH + "background_music/";
const std::string CONSTANTS::BACKGROUND_MUSIC = MUSIC_PATH + "gameMusic.ogg";
const std::string CONSTANTS::DEATH_MUSIC = MUSIC_PATH + "gameOver.ogg";

double sample(const unsigned int probability[], const double values[]) {
  unsigned int roll = rand() % 100;
  int index = 0;
  while (roll > probability[index]) {
    roll -= probability[index++];
  }

  return values[index];
}
