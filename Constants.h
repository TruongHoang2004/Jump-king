#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 800;

const int LEVEL_WIDTH = 768;
const int LEVEL_HEIGHT = 6400;

const int TOTAL_TILE_SPRITES = 32;
const int TOTAL_TILES = 1200;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;

const int WALKING_ANIMATION_FRAMES = 4;

//Set the velocity
const int MAX_FALLING_VEL = 10;
const int MIN_JUMP_VEL = 5;
const int MAX_JUMP_VEL = 25;
const int MAX_JUMP_TIME = 30;
const int GRAVITY = 1;

enum status
{
    IDLE,
    WALKING,
    JUMPING,
    FALLING,
    FORCING
};


enum tileType
{
    AIR_BLOCK
};

#endif // CONSTANTS_H_
