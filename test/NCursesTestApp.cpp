#include <fstream>

#include "../src/graphics/ASCIIRenderingSystem.hpp"
#include "../src/graphics/CharBitmap.hpp"
#include "../src/graphics/NCursesRenderingSystem.hpp"
#include "../src/ncurses/NCursesInterface.hpp"

int main()
{
    std::ofstream logFile;
    logFile.open("NCursesTestApp.log");
    
    {
        try
        {
            NCursesInterface ncurses(logFile);
            NCursesRenderingSystem system(logFile, ncurses);

            char buffer[] = {
                '#', '#', '#',
                '#', '#', '#',
                '#', '#', '#'
            };
            CharBitmap bitmap(buffer, 3, 3);

            system.drawBitmap(bitmap, 3, 3);
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
