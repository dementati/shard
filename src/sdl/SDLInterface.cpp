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
    LOG_INFO(mLogger, "Initializing SDL...");
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG_ERROR(mLogger, "Failed to initialize SDL: " << SDL_GetError());
    } 
    else 
    {
        LOG_INFO(mLogger, "Initialization successful");
    }

    if(TTF_Init() == -1)
    {
        LOG_ERROR(mLogger, "TTF could not initialize: " << TTF_GetError());
    }
    else
    {
        LOG_INFO(mLogger, "TTF initialization successful");
    }

    mWindow = SDL_CreateWindow(windowTitle.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        windowSize.x, windowSize.y, 
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_GRABBED);
    if(mWindow == NULL)
    {
        LOG_ERROR(mLogger, "Couldn't create window: " << SDL_GetError());
    }
    else
    {
        LOG_INFO(mLogger, "Window created successfully");
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_TARGETTEXTURE);
    if(mRenderer == NULL)
    {
        LOG_ERROR(mLogger, "Renderer could not be created: " << SDL_GetError());
    }
    else
    {
        LOG_INFO(mLogger, "Renderer created successfully");
    }

    mFont = TTF_OpenFont( "fonts/Anonymous_Pro.ttf", 13); 
    if(mFont == NULL)
    {
        LOG_ERROR(mLogger, "Couldn't open font: " << TTF_GetError());
    } 
    else
    {
        LOG_INFO(mLogger, "Font opened successfully");
    }
}

SDLInterface::~SDLInterface()
{
    LOG_INFO(mLogger, "Closing font...");
    TTF_CloseFont(mFont);

    LOG_INFO(mLogger, "Destroying renderer...");
    SDL_DestroyRenderer(mRenderer);
    
    LOG_INFO(mLogger, "Destroying window...");
    SDL_DestroyWindow(mWindow);

    LOG_INFO(mLogger, "Quitting TTF...");
    TTF_Quit();

    LOG_INFO(mLogger, "Quitting SDL...");
    SDL_Quit();

    LOG_INFO(mLogger, "Done.");
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
    LOG_INFO(mLogger, "Creating texture from string '" << str << "' with color " 
        << color.r << ", " 
        << color.g << ", " 
        << color.b << ", " 
        << color.a);

    SDL_Color sdlColor = { color.r, color.g, color.b, color.a };
    auto textSurface = TTF_RenderText_Solid(mFont, str.c_str(), sdlColor);
    if(textSurface == NULL)
    {
        LOG_ERROR(mLogger, "Failed to create text surface: " << TTF_GetError());
    }
    else
    {
        LOG_INFO(mLogger, "Surface rendered successfully");
    }

    auto texture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if(texture == NULL)
    {
        LOG_ERROR(mLogger, "Texture could not be rendered: " << SDL_GetError());
    }
    else
    {
        LOG_INFO(mLogger, "Texture rendered successfully");
    }

    SDL_FreeSurface(textSurface);

    return std::make_shared<SDLTexture>(texture);
}

void SDLInterface::clear()
{
    LOG_DEBUG(mLogger, "Clearing");
    SDL_RenderClear(mRenderer);
}

void SDLInterface::render(SDLTexture &texture, glm::ivec2 position, glm::ivec2 dimensions)
{
    ASSERT(dimensions.x > 0, "Render dimensions must be positive");
    ASSERT(dimensions.y > 0, "Render dimensions must be positive");
    ASSERT(texture.get() != nullptr, "Cannot render null texture");

    LOG_DEBUG(mLogger, "Drawing texture at " << glm::to_string(position) << " with dimensions " << glm::to_string(dimensions));

    SDL_Rect destRect = {position.x, position.y, dimensions.x, dimensions.y};
    SDL_RenderCopy(mRenderer, texture.get(), NULL, &destRect);
}

void SDLInterface::refresh()
{
    LOG_DEBUG(mLogger, "Refreshing");
    SDL_RenderPresent(mRenderer);
}
// LCOV_EXCL_STOP
