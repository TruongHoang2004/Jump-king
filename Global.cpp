#include "Global.h"

game * Game;

SDL_Window * gWindow = NULL;

SDL_Renderer * gRenderer = NULL;

TTF_Font *gFont = NULL;

SDL_Rect gCameraSprite[ LEVEL_HEIGHT / SCREEN_HEIGHT ];

LTexture gTilesTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

LTexture gWalkingSpriteSheetTexture;
SDL_Rect gWalkingSpriteClip[ WALKING_ANIMATION_FRAMES ];

LTexture gBGTexture;
