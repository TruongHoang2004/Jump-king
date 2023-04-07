#ifndef TILES_H_
#define TILES_H_

#include "LTexture.h"
#include "constant.h"

class Tile
{
public:
    //Initializes position and type
    Tile( int x, int y, int tileType );

    //Show the tile
    void render( SDL_Rect& camera );

    //Get the collision box
    SDL_Rect getBox();

    //Get tile type
    int getType();

private:
    //The attributes of the tile
    SDL_Rect mBox;

    //The tile type
    int mType;
};

#endif // TILES_H_
