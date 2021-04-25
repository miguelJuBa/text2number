#include <boost/log/expressions.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>

#include "MainApp.h"
#include "TextToNumberTranslator.h"


auto initLogger() -> void
{
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );
}

int main(int argc, char ** argv)
{

    initLogger();

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