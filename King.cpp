#include "King.h"
#include "Global.h"
#include "Utils.h"


King::King()
{
    //Initialize of the offsets
    currentFrame = gWalkingSpriteClip[ 0 ];
    mBox.x = 0;
    mBox.y = 6400 - 26;
    mBox.w = currentFrame.w;
    mBox.h = currentFrame.h;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    //Set frame to started
    frame = 0;

    //Set facing direction
    facing = false;
}

void King::handleEvent( SDL_Event &e )
{
    //If a key press down
    if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_SPACE:
            if ( kingStatus != FALLING && kingStatus != JUMPING )
            {
                mVelY -= JUMPING_VEL;
                kingStatus = JUMPING;
            }
            break;

        case SDLK_LEFT:
            mVelX -= KING_VEL;
            facing = true;
            if ( kingStatus == IDLE )
            {
                kingStatus = WALKING;
                frame = 0;
            }
            break;

        case SDLK_RIGHT:
            mVelX += KING_VEL;
            facing = false;
            if ( kingStatus == IDLE )
            {
                kingStatus = WALKING;
                frame = 0;
            }
            break;
        }

        if ( kingStatus == JUMPING )
        {
            if ( facing )
                mVelX = -1 * KING_VEL;
            else
                mVelX = KING_VEL;
        }
    }
    else if ( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch ( e.key.keysym.sym )
        {
        case SDLK_LEFT:
            mVelX += KING_VEL;
            if ( kingStatus == WALKING )
            {
                kingStatus = IDLE;
            }
            break;

        case SDLK_RIGHT:
            mVelX -= KING_VEL;
            if ( kingStatus == WALKING )
            {
                kingStatus = IDLE;
            }
            break;
        }
    }
}

void King::move( Tile * tiles[] )
{
    //Move the dot left or right
    mBox.x += mVelX;

    //If the dot went too far to the left or right
    if ( ( mBox.x < 0 ) || mBox.x + mBox.w > LEVEL_WIDTH || touchesWall( mBox, tiles ) )
    {
        //Move back
        mBox.x -= mVelX;
    }

    //Jumping and falling
    mVelY = std::min( mVelY + 1, MAX_FALLING_VEL );

    mBox.y += mVelY;
    if ( ( mBox.y < 0 ) || mBox.y + mBox.h > LEVEL_HEIGHT || touchesWall( mBox, tiles ) )
    {
        //Move back
        mBox.y -= mVelY;
        mVelY = 0;
        if ( kingStatus == FALLING || kingStatus == JUMPING )
        {
            kingStatus = IDLE;
        }
    }
}

void King::setCamera( SDL_Rect& camera )
{
    for ( int i = 0; i < LEVEL_HEIGHT / SCREEN_HEIGHT; ++i )
    {
        if ( checkCollision( mBox, gCameraSprite[ i ] ) )
        {
            camera = gCameraSprite[ i ];
            return ;
        }
    }
    return ;
}

void King::render( SDL_Rect& camera )
{
    mBox.w = currentFrame.w;
    mBox.h = currentFrame.h;
    SDL_RendererFlip flip;
    if ( facing )
        flip = SDL_FLIP_HORIZONTAL;
    else
        flip = SDL_FLIP_NONE;

    if ( kingStatus == WALKING )
    {
        if ( frame >= 8 * WALKING_ANIMATION_FRAMES )
            frame = 0;
        gWalkingSpriteSheetTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gWalkingSpriteClip[ frame / 8 ], 0, NULL, flip );
        currentFrame = gWalkingSpriteClip[ frame / 8 ];
        ++frame;
    }
    else
    {
        gWalkingSpriteSheetTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gWalkingSpriteClip[ 0 ], 0, NULL, flip);
        currentFrame = gWalkingSpriteClip[ 0 ];
    }
}

SDL_Rect King::getBox()
{
    return mBox;
}
