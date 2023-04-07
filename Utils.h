#ifndef UTILS_H_
#define UTILS_H_

#include "LTexture.h"
#include "Tiles.h"

bool init();

bool loadMedia( Tile* tiles[]);

void setSpriteClip();

void close( Tile* tiles[] );

bool checkCollision( SDL_Rect a, SDL_Rect b );

bool touchesWall( SDL_Rect box, Tile * tiles[] );

bool setTiles( Tile * tiles[], std::string path );

#endif // UTILS_H_
