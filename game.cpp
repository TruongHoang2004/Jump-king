#include "game.h"
#include "Global.h"

game::game()
{
    gWindow = NULL;
}

bool game::init( std::string title, int width, int height )
{
    bool success = true;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "Failed to initializes sdl \n";
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow( title.c_str() , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI );
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
                if ( !(IMG_Init( imgFlags ) & imgFlags ) )
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

void game::clean()
{
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
}

bool game::isRunning()
{
    return running;
}


