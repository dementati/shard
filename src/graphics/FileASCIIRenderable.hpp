#pragma once 

#include <fstream>
#include <ostream>
#include <sstream>
#include <string>

#include "../core/InvalidFormatException.hpp"
#include "ASCIIRenderingSystem.hpp"
#include "ASCIIRenderable.hpp"
#include "CharBitmap.hpp"

class FileASCIIRenderable : public ASCIIRenderable
{
    CharBitmap bitmap;

public:
    FileASCIIRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem, std::string filePath);

    void draw();

    static CharBitmap loadBitmap(std::string filePath);
};
