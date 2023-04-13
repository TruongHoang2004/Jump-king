#include "LTexture.h"
#include "Constants.h"
#include "UTIL.h"
#include "King.h"
#include "Global.h"
#include "Tiles.h"
#include "timer.h"
#include "game.h"

//Main loop flag   
bool quit = false;

//Event handler
SDL_Event e;

//The king
King Author;

//Camera rect
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

//The level tiles
Tile* tileSet[ TOTAL_TILES ];

//Cap timer
LTimer capTimer;

int main( int argc, char* args[] )
{
    if ( !init() )
    {
        std::cout << "Failed to initialize\n" ;
    }
    else
    {
        //Load media
        if ( !loadMedia( tileSet ) )
        {
            std::cout << "Failed to load media" << std::endl;
        }
        else
        {
            //Set all of clip
            setSpriteClip();

            while ( !quit )
            {
                capTimer.start();

                while( SDL_PollEvent( &e ) != 0 )
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    gameHandleEvent(&Author, e);
                }
                gameCaculate(&Author, camera, tileSet);
                gameRender(&Author,tileSet, camera);

                int frameTicks = capTimer.getTicks();
                if (frameTicks < SCREEN_TICKS_PER_FRAME)
                {
                    //Wait remaining time
                    SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
                }
            }
        }
        close( tileSet );
    }
        return 0;
}
