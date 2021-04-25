#include <stdexcept>
#include <boost/log/trivial.hpp>

#include "MainApp.h"


mainApp::MainApp::MainApp(translators::ITranslator &translator) : m_translator(translator)
{
    
}

mainApp::MainApp::~MainApp()
{

}

void mainApp::MainApp::run(int argc, char ** argv)
{
    BOOST_LOG_TRIVIAL(debug) << "Running application...";
    m_textToTranslate = parseCommandlineParameters(argc, argv);
    std::string textTranslated = m_translator.translate(m_textToTranslate);
    BOOST_LOG_TRIVIAL(info) << "Text2Number: " << textTranslated;
}

std::string mainApp::MainApp::parseCommandlineParameters(int numberOfParameters, char ** parameters)
{
    BOOST_LOG_TRIVIAL(debug) << "Parsing a total of: " << numberOfParameters << " parameters";
    if( (numberOfParameters <= 1) || (numberOfParameters > 2) )
    {
        throw std::runtime_error("Application accepts only 1 parameter, the text to be processed");
    }

    std::string textToProcess(parameters[1]);
    BOOST_LOG_TRIVIAL(info) << "Text to process -" << textToProcess << "-";
    if(textToProcess.empty())
    {
        throw std::runtime_error("Application does not accepts empty text");
    }

    return textToProcess;
}