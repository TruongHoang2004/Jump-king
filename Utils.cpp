#include "Utils.h"
#include "Constants.h"

bool init()
{
    bool success = true;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "Failed to initializes sdl \n";
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow( "Jump king" , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );
        if ( gWindow == NULL )
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if ( gRenderer == NULL )
            {
                std::cout << "Renderer could not be create! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if ( !IMG_Init( imgFlags ) & imgFlags ) )
                {
                    std::cout << "SDL image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                    success = false;
                }

                //Initialize SDL_ttf
                if ( TTF_Init() == -1 )
                {
                    std::cout << "SDL_ttf could not initialize! SDL_ttf Error" << TTF_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
}

void close()
{

}
