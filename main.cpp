#include "LTexture.h"
#include "Constants.h"
#include "UTIL.h"
#include "King.h"
#include "Global.h"
#include "Tiles.h"
#include "timer.h"

//Main loop flag
bool quit = false;

//Event handler
SDL_Event e;

//The king
King theKing;

//Camera rect
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

//The level tiles
Tile* tileSet[ TOTAL_TILES ];

//Cap timer
LTimer capTimer;


void handleEvent();
void caculate();
void render();

void handleEvent()
{
    if (e.type == SDL_QUIT)
    {
        quit = true;
    }

    //Handle input for the dot
    theKing.handleEvent(e);
}

void caculate()
{
    //Move the king
    theKing.move(tileSet);
    theKing.setStatus();
    theKing.setCamera(camera);
}

void render()
{
    //Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    //Back ground render
    gBGTexture.render(0, 0, &camera);

    //Tiles render
    for (int i = 0; i < TOTAL_TILES; ++i)
    {
        tileSet[i]->render(camera);
    }

    //Render the king
    theKing.render(camera);

    //Draw jump force
    theKing.drawJumpForce();

    //Update screen
    SDL_RenderPresent(gRenderer);
}

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
                    handleEvent();
                }
                caculate();
                render();

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
