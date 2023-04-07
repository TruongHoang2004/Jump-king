#include "King.h"
#include "Global.h"
#include "Utils.h"


King::King()
{
    //Initialize of the offsets
    currentFrame = gWalkingSpriteClip[ 0 ];
    mBox.x = 0;
    mBox.y = LEVEL_HEIGHT - 26;
    mBox.w = currentFrame.w;
    mBox.h = currentFrame.h;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    //Set frame to started
    frame = 0;

    //Set facing direction
    facing = false;

    jump_time = 0;
}

void King::handleEvent( SDL_Event &e )
{
    if ( e.type == SDL_KEYDOWN )
    {
        if ( e.key.repeat == 0 )
        {
            switch ( e.key.keysym.sym )
            {
            case SDLK_LEFT:
                facing =  true;
                mVelX -= KING_VEL;
                break;

            case SDLK_RIGHT:
                facing = false;
                mVelX += KING_VEL;
                break;
            }
        }

        if ( e.key.repeat != 0 )
        {
            if ( e.key.keysym.sym == SDLK_SPACE )
            {
                if ( jump_time < MAX_JUMP_TIME )
                {
                    ++jump_time;
                }
                else
                {
                    jump_time = MAX_JUMP_TIME;
                }
            }
        }
    }

    if ( e.type == SDL_KEYUP )
    {
        if ( e.key.repeat == 0 )
        {
            switch ( e.key.keysym.sym )
            {
            case SDLK_LEFT:
                mVelX += KING_VEL;
                break;

            case SDLK_RIGHT:
                mVelX -= KING_VEL;
                break;

            case SDLK_SPACE:
                mVelY -= MIN_JUMP_VEL + ( MAX_JUMP_VEL - MIN_JUMP_VEL ) * jump_time / MAX_JUMP_TIME;
                jump_time = 0;
                break;
            }
        }
    }
}

void King::move( Tile * tiles[] )
{
    //Move X
    mBox.x += mVelX;
    if ( mBox.x < 0 || mBox.x + mBox.w > LEVEL_WIDTH || touchesWall( mBox, tiles ) )
    {
        //Move back
        mBox.x -= mVelX;
    }

    //Move Y
    mBox.y += mVelY;
    if ( mBox.y < 0 || mBox.y + mBox.h > LEVEL_HEIGHT || touchesWall( mBox, tiles ) )
    {
        //Move back
        mBox.y -= mVelY;
        mVelY = 0;
    }

    //Gravity
    mVelY = std::min( mVelY + GRAVITY, MAX_FALLING_VEL );
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

void King::drawJumpForce()
{
    if ( jump_time != 0 )
    {
        SDL_Rect jumpForce = { SCREEN_WIDTH - 100, 0, jump_time * 100 / MAX_JUMP_TIME, 20 };
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderFillRect( gRenderer, &jumpForce );
    }
}
