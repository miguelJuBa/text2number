#include <boost/log/trivial.hpp>

#include "MainApp.h"

int main(int argc, char ** argv)
{
    int retVal = 0;
    mainApp::MainApp app;

    try
    {
        // We create a class with the general application logic, so it can be reuse in elsewhere. 
        app.run(argc, argv);
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << "Halting process due to: " << e.what();
        retVal = 1;
    }
    
    return retVal;
}