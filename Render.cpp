#include "Render.h"

void render( King &theKing, Tile* tileSet[] , SDL_Rect &camera )
{
    theKing.move( tileSet );
    theKing.setCamera( camera );

    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    //Back ground render
    gBGTexture.render( 0, 0, &camera );

    //Tiles render
    for ( int i = 0; i < TOTAL_TILES; ++i )
    {
        tileSet[ i ]->render( camera );
    }

    //Render the king
    theKing.render( camera );

    theKing.drawJumpForce();

    //Update screen
    SDL_RenderPresent( gRenderer );
}
