#include "constants.hpp"

// Game World
const double CONSTANTS::AREA_SIZE        =   5.0;
const double CONSTANTS::WALL_HEIGHT      =   1.0;
const double CONSTANTS::WALL_THICKNESS   =   1.0;

// Enemy
const unsigned int  CONSTANTS::INITIAL_ENEMIES  =   0;
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
