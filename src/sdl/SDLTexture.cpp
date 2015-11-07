#include "SDLTexture.hpp"

// LCOV_EXCL_START
SDLTexture::SDLTexture(SDL_Texture *texture)
:
    mTexture(texture)
{
}

SDLTexture::~SDLTexture()
{
    if(mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
    }
}

SDL_Texture* SDLTexture::get()
{
    return mTexture;
}
// LCOV_EXCL_STOP
