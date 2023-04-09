#include "Tiles.h"
#include "Global.h"
#include "UTIL.h"

Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

void Tile::render( SDL_Rect& camera )
{
    if ( mType == 0 )
    {
        return;
    }
    //If the tile is on screen
    if ( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTilesTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

