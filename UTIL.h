#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Tiles.h"

bool init();

bool loadMedia(Tile* tiles[]);

void setSpriteClip();

void close(Tile* tiles[] );

bool checkCollision( SDL_Rect a, SDL_Rect b );

bool touchesWall( SDL_Rect box, Tile * tiles[] );

bool setTiles( Tile * tiles[], std::string path );

#endif // UTILS_H_
