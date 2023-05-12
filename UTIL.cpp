#include "UTIL.h"
#include "Constants.h"
#include "Global.h"

bool init( SDL_Window* window)
{
    bool success = true;
    window = SDL_CreateWindow("Jump king", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL)
    {
        std::cout << "Failed to create new window\n";
    }
    else
    {
        //Initialize renderer
        gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (gRenderer == NULL)
        {
            std::cout << "Renderer could not be create! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        }
    }

    //Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        std::cout << "Failed to initializes sdl \n";
        success = false;
    }

    //Initialize SDL_image
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

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    if (!gWalkingSpriteSheetTexture.loadFromFile("Game data/Character/Walking.png"))
    {
        std::cout << "Unable to load Walking sprite sheet\n";
        success = false;
    }

    if (!gBGTexture.loadFromFile("Game data/Jungle_background.png "))
    {
        std::cout << "Unable to load background texture\n";
        success = false;
    }

    if (!gCastleBackGround.loadFromFile("Game data/castle_wall_background.png"))
    {
        std::cout << "Unable to load castle background texture\n";
        success = false;
    }

    if (!gTilesTexture.loadFromFile("Game data/Tileset/Tileset.png"))
    {
        std::cout << "Failed to load tiles texture\n";
        success = false;
    }

    if (!gJumpingTexture.loadFromFile("Game data/Character/Jumping.png"))
    {
        std::cout << "Failed to load jumping texture\n";
        success = false;
    }

    if (!gForcingTexture.loadFromFile("Game data/Character/Forcing.png"))
    {
        std::cout << "Failed to load forcing texture\n";
        success = false;
    }

    if (!gFallingTexture.loadFromFile("Game data/Character/Falling.png"))
    {
        std::cout << "Failed to load falling texture\n";
        success = false;
    }
    
    if (!gCollisionTexture.loadFromFile("Game data/Character/Colision.png"))
    {
        std::cout << "Failed to load colision texture\n";
        success = false;
    }

    if (!gMenuBGTexture.loadFromFile("Game data/background_of_menu.png"))
    {
        std::cout << "Failed to load menu back ground\n";
        success = false;
    }

    if (!gWinGameBG.loadFromFile("Game data/winning_texture.png"))
    {
        std::cout << "Failed to load win game texture\n";
        success = false;
    }

    if (!gNewGameButton.loadButtonTextureFromText("Game data/Menu_font.ttf", "NEW GAME", 40))
    {
        std::cout << "Failed to load 'NEW GAME' button\n";
        success = false;
    }
    else gNewGameButton.setPosition(120, 350);

    if (!gContinueButton.loadButtonTextureFromText("Game data/Menu_font.ttf", "CONTINUE", 40))
    {
        std::cout << "Failed to load 'CONTINUE' button\n";
        success = false;
    }
    else gContinueButton.setPosition(120, 400);

    if (!gOptionsButton.loadButtonTextureFromText("Game data/Menu_font.ttf", "OPTION", 40))
    {
        std::cout << "Failed to load 'OPTION' button\n";
        success = false;
    }
    else gOptionsButton.setPosition(120, 450);

    if (!gCreditButton.loadButtonTextureFromText("Game data/Menu_font.ttf", "CREDIT", 40))
    {
        std::cout << "Failed to load 'CREDIT' button\n";
        success = false;
    }
    else gCreditButton.setPosition(120, 500);

    if (!gQuitButton.loadButtonTextureFromText("Game data/Menu_font.ttf", "QUIT", 40))
    {
        std::cout << "Failed to load 'QUIT' button\n";
        success = false;
    }
    else gQuitButton.setPosition(120, 550);

    if (!gResumeButton.loadButtonTextureFromText("Game data/Menu_font.ttf", "RESUME", 40))
    {
        std::cout << "Failed to load 'RESUME' button\n";
        success = false;
    }
    else gResumeButton.setPosition((SCREEN_WIDTH - gResumeButton.getWidth()) / 2, 200);

    if (!gRestartButton.loadButtonTextureFromText("Game data/Menu_font.ttf", "RESTART", 40))
    {
        std::cout << "Failed to load 'RESTART' button\n";
        success = false;
    }
    else gRestartButton.setPosition((SCREEN_WIDTH - gRestartButton.getWidth()) / 2, 250);

    if (!gPauseOptionButton.loadButtonTextureFromText("Game data/Menu_font.ttf", "OPTIONS", 40))
    {
        std::cout << "Failed to load 'OPTION' in pause menu button\n";
        success = false;
    }
    else gPauseOptionButton.setPosition((SCREEN_WIDTH - gPauseOptionButton.getWidth()) / 2, 300);

    if (!gSaveExitButton.loadButtonTextureFromText("Game data/Menu_font.ttf", "SAVE AND EXIT", 40))
    {
        std::cout << "Failed to load 'SAVE & EXIT' button";
            success = false;
    }
    else gSaveExitButton.setPosition((SCREEN_WIDTH - gSaveExitButton.getWidth()) / 2, 350);

    if (!gEndGame.loadButtonTextureFromText("Game data/Menu_font.ttf", "YOU WINNING THE GAME, CLICK THE TO BACK TO MENU", 50))
    {
        std::cout << "Failed to load 'END GAME' button\n";
        success = false;
    }
    else gEndGame.setPosition((SCREEN_WIDTH - gEndGame.getWidth()) / 2, 600);


    gJumpSound = Mix_LoadWAV("Game data/jump.wav");
    if (gJumpSound == NULL)
    {
        std::cout << "Failed to load jump sound\n";
        success = false;
    }

    return success;
}

bool setTiles( Tile * tiles[] , std::string path)
{
    //Success flag
    bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the file map
    std::ifstream map(path.c_str());

    //If the map couldn't be loaded
    if ( map.fail() )
    {
        std::cout << "Unable to load map file!" << std::endl;
        tilesLoaded = false;
    }
    else
    {
        //Initializes the tiles
        for (int i = 0; i < TOTAL_TILES; ++i )
        {
            //Determines what kid of tile will be made
            int tileType = -1;

            //Read the map from file
            map >> tileType;

            //If the was a problem in reading the map
            if ( map.fail() )
            {
                //Stop loading map
                std::cout << "Error loading map: Unexpected end of file!" << std::endl;
                tilesLoaded = false;
                break;
            }

            //If the number is a valid tile number
            if ( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
            {
                tiles[ i ] = new Tile( x, y, tileType );
            }// If we don't recongnize the tile type
            else
            {
                //Stop loading map
                std::cout << "Error loading map: Invalid tile type at " << i << std::endl;
                tilesLoaded = false;
                break;
            }

            //Move to next tile spot
            x += TILE_WIDTH;

            //If we've gone too far
            if ( x >= LEVEL_WIDTH )
            {
                //Move back
                x = 0;

                //Move to the next row
                y += TILE_HEIGHT;
            }
        }

        //Clip the sprite sheet
        if ( tilesLoaded )
        {
            for (int i = 1; i < TOTAL_TILE_SPRITES; ++i )
            {
                gTileClips[i].x = (((i - 1) % TILE_OF_ROW) * (TILE_WIDTH + 1));
                gTileClips[i].y = (((i - 1) / TILE_OF_ROW) * (TILE_HEIGHT + 1));
                gTileClips[i].w = TILE_WIDTH;
                gTileClips[i].h = TILE_HEIGHT;
            }
        }
    }

    map.close();

    return tilesLoaded;
}

void setSpriteClip()
{
    gWalkingSpriteClip[0] = {  0, 0, 50, 64};
    gWalkingSpriteClip[1] = { 50, 0, 62, 64};
    gWalkingSpriteClip[2] = {112, 0, 50, 64};
    gWalkingSpriteClip[3] = {163, 0, 58, 64};

    for ( int i = 0; i < LEVEL_HEIGHT / SCREEN_HEIGHT; ++i )
    {
        gCameraSprite[ i ] = { 0, i * SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
    }
}

void close( Tile* tiles[])
{
    for (int i = 0; i < TOTAL_TILES; ++i )
    {
        if ( tiles[ i ] != NULL )
        {
            delete tiles[ i ];
            tiles[ i ] = NULL;
        }
    }
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    TTF_CloseFont(gMenuFont);

    Mix_FreeChunk(gJumpSound);
    Mix_FreeMusic(gMusic);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if ( bottomA <= topB )
    {
        return false;
    }
    if ( topA >= bottomB)
    {
        return false;
    }
    if ( leftA >= rightB )
    {
        return false;
    }
    if ( rightA <= leftB )
    {
        return false;
    }

    //if none of the sides form A are outside B
    return true;
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >= 1 ) && 
            ( tiles[ i ]->getType() <= TOTAL_TILE_SPRITES ) && 
            tiles[i]->getType() != 18 &&
            tiles[i]->getType() != 41 &&
            tiles[i]->getType() != 64 &&
            tiles[i]->getType() != 200 && 
            tiles[i]->getType() != 199 &&
            tiles[i]->getType() != 203 &&
            tiles[i]->getType() != 226 &&
            tiles[i]->getType() != 271 &&
            tiles[i]->getType() != 272 )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

void drawRect( int xPos, int yPos, int width, int height )
{
    SDL_Rect rect = { xPos, yPos, width, height };
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &rect);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_Rect dRect = { rect.x + 4, rect.y + 4, rect.w - 8, rect.h - 8 };
    SDL_RenderDrawRect(gRenderer, &dRect);
}
