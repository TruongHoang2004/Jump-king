#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Tiles.h"

bool init(SDL_Window* window = NULL);

bool loadMedia();

void setSpriteClip();

void close(Tile* tiles[] );

bool checkCollision( SDL_Rect a, SDL_Rect b );

bool touchesWall( SDL_Rect box, Tile * tiles[] );

bool setTiles( Tile * tiles[], std::string path );

void drawRect(int xPos, int yPos, int width, int height);

#endif // UTILS_H_
