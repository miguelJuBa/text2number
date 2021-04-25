#include <boost/log/trivial.hpp>

#include "MainApp.h"

int main(int argc, char ** argv)
{
    mainApp::MainApp app;

    try
    {
        app.run(argc, argv);
    }
    catch(const std::exception& e)
    {
        BOOST_LOG_TRIVIAL(error) << "Halting process due to: " << e.what();
    }
    
    return 0;
}