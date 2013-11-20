#include "constants.hpp"
#include "math.h"

// Game World
const double CONSTANTS::AREA_SIZE        =   15.0;
const double CONSTANTS::CAMERA_ANGLE     =   20.0;
const double CONSTANTS::CAMERA_ANGLE_RAD =   CONSTANTS::CAMERA_ANGLE * M_PI / 180.0;
const double CONSTANTS::CAMERA_DISTANCE  =   20.0;
const double CONSTANTS::WALL_HEIGHT      =   3.0;
const double CONSTANTS::WALL_THICKNESS   =   2.0;

// Player
const double CONSTANTS::PLAYER_SPEED = 6.0;
const double CONSTANTS::ROTATION_SPEED = 720.0;

// Enemy
const unsigned int  CONSTANTS::INITIAL_ENEMIES  =   5;
const unsigned int  CONSTANTS::NUMBER_LENGTH    =   5;

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
