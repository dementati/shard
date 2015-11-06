#include "SDLTexture.hpp"

SDLTexture::SDLTexture(SDL_Texture *texture)
:
    mTexture(texture)
{
}

SDLTexture::~SDLTexture()
{
    SDL_DestroyTexture(mTexture);
}

SDL_Texture* SDLTexture::get()
{
    return mTexture;
}
