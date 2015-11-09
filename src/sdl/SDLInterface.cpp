#include "SDLInterface.hpp"

// LCOV_EXCL_START
std::unordered_map<SDLKey, SDL_Scancode, EnumClassHash> SDLInterface::cScanCodeMap =
{
    {SDLKey::W, SDL_SCANCODE_W},
    {SDLKey::A, SDL_SCANCODE_A},
    {SDLKey::S, SDL_SCANCODE_S},
    {SDLKey::D, SDL_SCANCODE_D},
    {SDLKey::E, SDL_SCANCODE_E},
    {SDLKey::Escape, SDL_SCANCODE_ESCAPE}
};

SDLInterface::SDLInterface(std::string windowTitle, glm::uvec2 windowSize)
:
    mLogger(LoggerFactory::createLogger("SDLInterface", Severity::DEBUG)),
    mEvent()
{
    mLogger->info("Initializing SDL...");
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        mLogger->error(std::string("Failed to initialize SDL: ") + SDL_GetError());
    } 
    else 
    {
        mLogger->info("Initialization successful");
    }

    if(TTF_Init() == -1)
    {
        mLogger->error(std::string("TTF could not initialize: ") + TTF_GetError());
    }
    else
    {
        mLogger->info("TTF initialization successful");
    }

    mWindow = SDL_CreateWindow(windowTitle.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        windowSize.x, windowSize.y, 
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_GRABBED);
    if(mWindow == NULL)
    {
        mLogger->error(std::string("Couldn't create window: ") + SDL_GetError());
    }
    else
    {
        mLogger->info("Window created successfully");
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_TARGETTEXTURE);
    if(mRenderer == NULL)
    {
        mLogger->error(std::string("Renderer could not be created: ") + SDL_GetError());
    }
    else
    {
        mLogger->info("Renderer created successfully");
    }

    mFont = TTF_OpenFont( "fonts/Anonymous_Pro.ttf", 13); 
    if(mFont == NULL)
    {
        mLogger->error(std::string("Couldn't open font: ") + TTF_GetError());
    } 
    else
    {
        mLogger->info("Font opened successfully");
    }
}

SDLInterface::~SDLInterface()
{
    mLogger->info("Closing font...");
    TTF_CloseFont(mFont);

    mLogger->info("Destroying renderer...");
    SDL_DestroyRenderer(mRenderer);
    
    mLogger->info("Destroying window...");
    SDL_DestroyWindow(mWindow);

    mLogger->info("Quitting TTF...");
    TTF_Quit();

    mLogger->info("Quitting SDL...");
    SDL_Quit();

    mLogger->info("Done.");
}

void SDLInterface::pollEvents()
{
    while(SDL_PollEvent(&mEvent) != 0) {}

    mKeyStates = SDL_GetKeyboardState(NULL);
}

bool SDLInterface::isPressed(SDLKey key)
{
    ASSERT(cScanCodeMap.count(key) == 1, "Key is not supported");

    return mKeyStates[cScanCodeMap[key]] == 1;
}

std::shared_ptr<SDLTexture> SDLInterface::createTextureFromString(std::string str, glm::u8vec4 color)
{
    mLogger->info(std::string("Creating texture from string '") + str + "' with color " 
        + glm::to_string((int)color.r) + ", " 
        + glm::to_string((int)color.g) + ", " 
        + glm::to_string((int)color.b) + ", " 
        + glm::to_string((int)color.a));

    SDL_Color sdlColor = { color.r, color.g, color.b, color.a };
    auto textSurface = TTF_RenderText_Solid(mFont, str.c_str(), sdlColor);
    if(textSurface == NULL)
    {
        mLogger->error(std::string("Failed to create text surface: ") + TTF_GetError());
    }
    else
    {
        mLogger->info("Surface rendered successfully");
    }

    auto texture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if(texture == NULL)
    {
        mLogger->error(std::string("Texture could not be rendered: ") + SDL_GetError());
    }
    else
    {
        mLogger->info("Texture rendered successfully");
    }

    SDL_FreeSurface(textSurface);

    return std::make_shared<SDLTexture>(texture);
}

void SDLInterface::clear()
{
    mLogger->debug("Clearing");
    SDL_RenderClear(mRenderer);
}

void SDLInterface::render(SDLTexture &texture, glm::ivec2 position, glm::ivec2 dimensions)
{
    ASSERT(dimensions.x > 0, "Render dimensions must be positive");
    ASSERT(dimensions.y > 0, "Render dimensions must be positive");
    ASSERT(texture.get() != nullptr, "Cannot render null texture");

    mLogger->debug(std::string("Drawing texture at " + glm::to_string(position) + " with dimensions " + glm::to_string(dimensions)));

    SDL_Rect destRect = {position.x, position.y, dimensions.x, dimensions.y};
    SDL_RenderCopy(mRenderer, texture.get(), NULL, &destRect);
}

void SDLInterface::refresh()
{
    mLogger->debug("Refreshing");
    SDL_RenderPresent(mRenderer);
}
// LCOV_EXCL_STOP
