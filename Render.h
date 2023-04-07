#ifndef RENDER_H_
#define RENDER_H_

#include "game.h"
#include "Constants.h"
#include "Utils.h"
#include "King.h"
#include "Global.h"
#include "Tiles.h"

void render( King &theKing, Tile* tileSet[], SDL_Rect &camera );

#endif // RENDER_H_
