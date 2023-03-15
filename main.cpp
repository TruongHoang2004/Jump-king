#include "LTexture.h"
#include "Constants.h"
#include "Utils.h"
#include "King.h"
#include "Global.h"
#include "Tiles.h"

int main( int argc, char* args[] )
{
    if ( !init() )
    {
        std::cout << "Failed to initialize\n" << std::endl;
    }
    else
    {
        //The level tiles
        Tile* tileSet[ TOTAL_TILES ];

        //Load media
        if ( !loadMedia( tileSet ) )
        {
            std::cout << "Failed to load media" << std::endl;
        }
        else
        {
            setSpriteClip();

            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            King theKing;

            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

            while ( !quit )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if ( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    //Handle input for the dot
                    theKing.handleEvent( e );
                }
                //Move the king
                for (int i = 0; i < 7 * 64; ++i )
                {
                    gTilesTexture.render( i * 64, 0, &gTileClips[ i ] );
                }

                theKing.move( tileSet );
                theKing.setCamera( camera );

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Back ground render
                gBGTexture.render( 0, 0, &camera );

                //Tiles render
                for (int i = 0; i < TOTAL_TILES; ++i )
                {
                    tileSet[i]->render( camera );
                }

                //Render the king
                theKing.render( camera );

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
        close( tileSet );
    }
    return 0;
}
