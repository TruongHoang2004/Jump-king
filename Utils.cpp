#include "Utils.h"
#include "Constants.h"
#include "Global.h"

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
        gWindow = SDL_CreateWindow( "Jump king", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );
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

bool loadMedia( Tile* tiles[] )
{
    bool success = true;
    if ( !gWalkingSpriteSheetTexture.loadFromFile( "Jump king character/PC_Computer_-_Jump_King_-_The_Knight___New_Babe-removebg-preview.png" ) )
    {
        std::cout << "Unable to load Walking sprite sheet\n";
        success = false;
    }

    if ( !gBGTexture.loadFromFile( "Jump king character/Background_2.png" ) )
    {
        std::cout << "Unable to load background texture\n" ;
        success = false;
    }

    if ( !gTilesTexture.loadFromFile( "Jump king character/tiles.png") )
    {
        std::cout << "Failed to load tiles texture \n";
        success = false;
    }

    if ( !setTiles( tiles ) )
    {
        std::cout << "Failed to load tile set!" << std::endl;
        success = false;
    }
    return success;
}

bool setTiles( Tile * tiles[] )
{
    //Success flag
    bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the file map
    std::ifstream map( "Jump king character/Tileset/game_map.map");

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
                gTileClips[ i ] = {((i - 1) % 7) * 64, ((i - 1) / 7 ) * 64, TILE_WIDTH, TILE_HEIGHT};
            }
        }
    }

    map.close();

    return tilesLoaded;
}

void setSpriteClip()
{
    gWalkingSpriteClip[0] = { 0, 0, 24, 26};
    gWalkingSpriteClip[1] = {24, 0, 31, 26};
    gWalkingSpriteClip[2] = {55, 0, 25, 26};
    gWalkingSpriteClip[3] = {80, 0, 30, 26};

    for ( int i = 0; i < LEVEL_HEIGHT / SCREEN_HEIGHT; ++i )
    {
        gCameraSprite[ i ] = { 0, i * SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT };
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
    Game->clean();
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;

    gWalkingSpriteSheetTexture.free();
    gBGTexture.free();

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
        if( ( tiles[ i ]->getType() >= 1 ) && ( tiles[ i ]->getType() < TOTAL_TILE_SPRITES ) )
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
