#include <fstream>

#include <glm/glm.hpp>

#include "../../src/graphics/ascii/ncurses/NCursesRenderingSystem.hpp"
#include "../../src/graphics/ascii/ASCIIFileRenderable.hpp"
#include "../../src/graphics/ascii/ASCIIRenderable.hpp"
#include "../../src/graphics/ascii/ASCIIRenderingSystem.hpp"
#include "../../src/graphics/ascii/ASCIIWorldRenderer.hpp"
#include "../../src/graphics/CharBitmap.hpp"
#include "../../src/graphics/RenderableStore.hpp"
#include "../../src/logic/Entity.hpp"
#include "../../src/logic/World.hpp"
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
            
            RenderableStore<ASCIIRenderable> renderableStore;
            renderableStore.add("test", std::make_unique<ASCIIFileRenderable>(logFile, system, SIZE_2x2_FILE_PATH));

            Entity testEntity("test");
            testEntity.position = glm::ivec2(10, 30);

            World world;
            world.add(testEntity);

            ASCIIWorldRenderer worldRenderer(renderableStore, world);

            worldRenderer.render();

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