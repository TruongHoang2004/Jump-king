#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "LTexture.h"
#include "Constants.h"

extern SDL_Window * gWindow;

extern SDL_Renderer * gRenderer;

extern TTF_Font *gFont;

extern SDL_Rect gCameraSprite[ LEVEL_HEIGHT / SCREEN_HEIGHT ];

extern LTexture gTilesTexture;
extern SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

extern LTexture gWalkingSpriteSheetTexture;
extern SDL_Rect gWalkingSpriteClip[ WALKING_ANIMATION_FRAMES ];

extern LTexture gBGTexture;
#endif // GLOBAL_H_
