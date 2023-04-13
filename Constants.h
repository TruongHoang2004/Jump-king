#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 480;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

const int TOTAL_TILE_SPRITES = 48;
const int TOTAL_TILES = 32 * 120;

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

const int TILE_OF_ROW = 8;

const int LEVEL_WIDTH = TILE_WIDTH * 32;
const int LEVEL_HEIGHT = TILE_HEIGHT * 120;

const int WALKING_ANIMATION_FRAMES = 4;

//Set the velocity
const int MIN_JUMP_VEL = 5;
const int MAX_JUMP_TIME = 30;

const int MAX_FALLING_VEL = 10;
const int MAX_JUMP_VEL = 20;
const int JUMP_VELX = 5;

const int GRAVITY = 1;

enum status
{
    IDLE,
    WALKING,
    JUMPING,
    FALLING,
    FORCING,
};


enum tileType
{
    AIR_BLOCK
};

#endif // CONSTANTS_H_
