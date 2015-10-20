#include <fstream>

#include "../src/ncurses/NCursesEngine.hpp"

int main()
{
    std::ofstream logFile;
    logFile.open("NCursesTestApp.log");
    
    {
        try
        {
            NCursesEngine engine(logFile);

            engine.addCharacter('@', 1000, 0, 0, 0, 0, 0);
            engine.redraw();

            getch();
        } 
        catch(NCursesException &e)
        {
            logFile << "Caught NCursesException: " << e.what() << std::endl; 
        }
    }

    logFile.close();

}
