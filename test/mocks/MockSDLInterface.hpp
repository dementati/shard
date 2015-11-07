#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <gmock/gmock.h>

#include "../../src/sdl/SDLInterface.hpp"
#include "../../src/sdl/SDLTexture.hpp"

class MockSDLInterface : public SDLInterface
{
public:
    MockSDLInterface()
    :
        SDLInterface(std::string("mock"), glm::uvec2(1, 1))
    {
    }

    MOCK_METHOD0(pollEvents, void());

    MOCK_METHOD1(isPressed, bool(SDLKey));

    MOCK_METHOD2(createTextureFromString, 
        std::shared_ptr<SDLTexture>(std::string, glm::u8vec4));

    MOCK_METHOD0(clear, void());

    MOCK_METHOD3(render, void(SDLTexture&, glm::ivec2, glm::ivec2));

    MOCK_METHOD0(refresh, void());
};
