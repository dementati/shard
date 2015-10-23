#include <fstream>

#include <glm/glm.hpp>

#include "../../src/graphics/ASCIIRenderingSystem.hpp"
#include "../../src/graphics/CharBitmap.hpp"
#include "../../src/graphics/FileASCIIRenderable.hpp"
#include "../../src/graphics/NCursesRenderingSystem.hpp"
#include "../../src/graphics/TestRenderable.hpp"
#include "../../src/ncurses/NCursesInterface.hpp"

#define SIZE_2x2_FILE_PATH "../test/resources/charBitmaps/2x2.txt"

int main()
{
    std::ofstream logFile;
    logFile.open("NCursesTestApp.log");
    
    {
        try
        {
            NCursesInterface ncurses(logFile);
            NCursesRenderingSystem system(logFile, ncurses);
            system.setScreenPosition(glm::ivec2(-20, -20));
            
            TestRenderable renderable(logFile, system);
            renderable.setPosition(glm::ivec2(0, 0));

            FileASCIIRenderable fileRenderable(logFile, system, SIZE_2x2_FILE_PATH);
            fileRenderable.setPosition(glm::ivec2(10, 5));

            renderable.draw();
            fileRenderable.draw();

            ncurses.refreshScreen();
            getch();
        } 
        catch(NCursesException &e)
        {
            logFile << "Caught NCursesException: " << e.what() << std::endl; 
        }
    }

    logFile.close();

}
