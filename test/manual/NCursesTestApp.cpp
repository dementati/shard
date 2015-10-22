#include <fstream>

#include <glm/glm.hpp>

#include "../../src/graphics/ASCIIRenderingSystem.hpp"
#include "../../src/graphics/CharBitmap.hpp"
#include "../../src/graphics/NCursesRenderingSystem.hpp"
#include "../../src/graphics/TestRenderable.hpp"
#include "../../src/ncurses/NCursesInterface.hpp"

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

            renderable.draw();

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
