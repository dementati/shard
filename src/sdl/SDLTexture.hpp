#pragma once

#pragma GCC diagnostic ignored "-Weffc++"

#include <SDL.h>

class SDLTexture
{
    SDL_Texture *mTexture;

public:
    SDLTexture(SDL_Texture *texture);

    ~SDLTexture();

    SDL_Texture* get();
};
