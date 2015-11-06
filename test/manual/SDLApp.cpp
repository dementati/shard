#include <iostream>
#include <unordered_map>

#include <SDL.h>
#include <SDL_ttf.h>

int main()
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize: " << SDL_GetError() << std::endl;
        return 1;
    } 
    else
    {
        std::cout << "SDL initialization successful" << std::endl;
    }

    // Initialize TTF
    if(TTF_Init() == -1)
    {
        std::cerr << "TTF could not initialize: " << TTF_GetError() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "TTF initialization successful" << std::endl;
    }

    // Initialize window
    auto window = SDL_CreateWindow( "SDL Tutorial", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        640, 480, 
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_GRABBED);
    if(window == NULL)
    {
        std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Window created successfully" << std::endl;
    }
    
    // Create renderer
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
    if( renderer == NULL )
    {
        std::cerr << "Renderer could not be created: " << SDL_GetError() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Renderer created successfully" << std::endl;
    }

    // Open font 
    auto font = TTF_OpenFont( "../fonts/Anonymous_Pro.ttf", 13); 
    if(font == NULL)
    {
        std::cerr << "Couldn't open font: " << TTF_GetError() << std::endl;
        return 1;
    } 
    else
    {
        std::cout << "Font opened successfully" << std::endl;
    }

    // Render text to surface
    SDL_Color color = { 255, 255, 255, 255 };
    auto textSurface = TTF_RenderText_Solid(font, "@", color);
    if(textSurface == NULL)
    {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Surface rendered successfully" << std::endl;
    }

    // Render surface to texture
    auto texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if(texture == NULL)
    {
        std::cerr << "Texture could not be rendered: " << SDL_GetError() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Texture rendered successfully" << std::endl;
    }

    int x = 10;
    int y = 10;
    int w = 10;
    int h = 13;

    std::unordered_map<int, bool> pressed;

    // Main loop
    SDL_Event event;
    bool quit = false;
    const Uint8 *keys = nullptr;
    while(!quit) {
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }

            keys = SDL_GetKeyboardState(NULL);
        }

        if(keys[SDL_SCANCODE_ESCAPE]) 
        {
            quit = true;
        }

        if(keys[SDL_SCANCODE_UP]) 
        {
            y -= 1;
        }

        if(keys[SDL_SCANCODE_DOWN]) 
        {
            y += 1;
        }

        if(keys[SDL_SCANCODE_LEFT]) 
        {
            x -= 1;
        }

        if(keys[SDL_SCANCODE_RIGHT]) 
        {
            x += 1;
        }

        // Clear screen
        SDL_RenderClear(renderer);

        // Render text
        SDL_Rect destRect = {x, y, w, h};
        SDL_RenderCopy(renderer, texture, NULL, &destRect);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    std::cout << "Shutting down SDL..." << std::endl;

    SDL_DestroyWindow( window );

    SDL_Quit();

    std::cout << "SDL quit neatly" << std::endl;

    return 0;
}
