#include "game.h"

void gameHandleEvent(King* theKing, SDL_Event& e )
{
	//Handle input for the king
	theKing->handleEvent(e);
}

void gameCaculate(King* theKing, SDL_Rect& camera, Tile* tileset[])
{
	//Move the king
	theKing->move(tileset);
	theKing->setStatus();
	theKing->setCamera(camera);
}

void gameRender( King* theKing, Tile* tileset[], SDL_Rect &camera)
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	//Back ground render
	gBGTexture.render(0, 0);

	//Tiles render
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		tileset[i]->render(camera);
	}

	//The king render
	theKing->render(camera);

	theKing->drawJumpForce();

	//Screen update
	SDL_RenderPresent(gRenderer);
}
