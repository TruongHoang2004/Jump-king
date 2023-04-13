#ifndef GAME_H_
#define GAME_H_

#include "LTexture.h"
#include "Constants.h"
#include "Global.h"
#include "Tiles.h"
#include "King.h"

void gameHandleEvent( King * theKing, SDL_Event &e );
void gameCaculate( King * theKing, SDL_Rect &camera, Tile * tileset[] );
void gameRender(King* theKing, Tile * tileset[], SDL_Rect &camera);

#endif // !GAME_H_
