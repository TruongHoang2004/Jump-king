#include "LTexture.h"
#include "Constants.h"
#include "Utils.h"

int main( int argc, char* args[] )
{
    if ( !init() )
    {
        std::cout << "Failed to initialize\n" << std::endl;
    }
    else
    {
        if ( !loadMedia() )
        {
            std::cout << "Failed to load media" << std::endl;
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            while ( !quit )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if ( e.type == SDL_QUIT ) )
                    {
                        quit = true;
                    }
                }

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                SDL_RenderPresent( gRenderer );
            }
        }
        close();
    }
    return 0;
}
