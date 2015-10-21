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

            engine.draw('@', 10, 10);
            engine.refreshScreen();

            getch();
        } 
        catch(NCursesException &e)
        {
            logFile << "Caught NCursesException: " << e.what() << std::endl; 
        }
    }

    logFile.close();

}
