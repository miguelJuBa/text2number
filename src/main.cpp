#include <boost/log/trivial.hpp>

#include "MainApp.h"
#include "TextToNumberTranslator.h"

int main(int argc, char ** argv)
{
    translators::TextToNumberTranslator translator;
    mainApp::MainApp app(translator);

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