#include <algorithm>
#include <iterator>
#include <cctype>
#include <sstream>
#include <boost/log/trivial.hpp>

#include "TextToNumberTranslator.h"
#include "TextTools.hpp"



translators::TextToNumberTranslator::TextToNumberTranslator()
{

}

translators::TextToNumberTranslator::~TextToNumberTranslator()
{
    
}

std::string translators::TextToNumberTranslator::translate(const std::string &textToTranslate)
{
    //1) Tokenize the text in words.
    std::vector<std::string> tokens = Tools::Text::textToTokens(textToTranslate, " ");
    
    std::stringstream translatedTextStream;
    unsigned long numberTranslated = 0;  
    std::string lowerCaseWord;

    //2) Iterate through every token to translate words existing in the dictionary into numbers.
    for (std::vector<std::string>::iterator wordIterator = tokens.begin(); wordIterator != tokens.end(); ++wordIterator)
    {
        lowerCaseWord = Tools::Text::textToLowercase(*wordIterator);
        
        //2.1) Check if it is a number, a unit, a connector or a regular word.
        WordTranslation wordTranslation = getWordTranslation(lowerCaseWord);
        
        switch(wordTranslation.type)
        {
            case translators::WordType::NUMBER:
                numberTranslated += wordTranslation.translation;
            break;
            case translators::WordType::UNIT:
                numberTranslated *= wordTranslation.translation;
            break;
            case translators::WordType::CONNECTOR:
            {
                // We need to check if the next word after a connector is not a number
                // to discard cases where is used not in the construction of a number.
                if(numberTranslated == 0)
                {
                    translatedTextStream << *wordIterator << " ";
                }
                
                if(!isANumberConnector(wordIterator))
                {
                    translatedTextStream << std::to_string(numberTranslated) << " " << *wordIterator << " ";
                    numberTranslated=0;
                }
                
                break;
            }
            default:
            {
                // In case we found a word not part of a number, if there was a number before, translate both.
                if(numberTranslated > 0)
                {
                    translatedTextStream << std::to_string(numberTranslated) << " " << *wordIterator << " ";
                    numberTranslated = 0;
                }
                else
                {
                    translatedTextStream << *wordIterator << " ";
                }
                break;         
            }

        }    
    }

    // A text ends with a word which is not among the the one used in numbers.
    if(numberTranslated > 0)
    {
        translatedTextStream << std::to_string(numberTranslated);
    }

    //4) Trim any possible ending spaces.
    std::string translatedText = translatedTextStream.str();
    Tools::Text::textTrim(translatedText);
    BOOST_LOG_TRIVIAL(trace) << "Text translated to: " << translatedText;

    return translatedText;
}


translators::WordTranslation translators::TextToNumberTranslator::getWordTranslation(const std::string &wordToTranslate)
{
    translators::WordTranslation wordTranslation;
    wordTranslation.type = translators::WordType::WORD;
    wordTranslation.translation = 0;

    // Search for a number.
    auto numberIterator = m_numbersDictionary.find(wordToTranslate);
    if(numberIterator != m_numbersDictionary.end())
    {
        wordTranslation.type = translators::WordType::NUMBER;
        wordTranslation.translation = numberIterator->second;
        BOOST_LOG_TRIVIAL(debug) << "NUMBER Translation: " << numberIterator->first << " to: " << wordTranslation.translation;
        return wordTranslation;
    }

    // Search for a unit.
    auto unitsIterator = m_unitsDictionary.find(wordToTranslate);
    if(unitsIterator != m_unitsDictionary.end())
    {
        wordTranslation.type = translators::WordType::UNIT;
        wordTranslation.translation = unitsIterator->second;
        BOOST_LOG_TRIVIAL(debug) << "UNIT Translation: " << unitsIterator->first << " to: " << wordTranslation.translation;
        return wordTranslation;
    }

    // Search for connectors.
    auto connectorIterator = m_connectorDictionary.find(wordToTranslate);
    if(connectorIterator != m_connectorDictionary.end())
    {
        wordTranslation.type = translators::WordType::CONNECTOR;
        wordTranslation.translation = 0;
        BOOST_LOG_TRIVIAL(trace) << "Connector found: " << connectorIterator->first;
        return wordTranslation;
    }

    BOOST_LOG_TRIVIAL(trace) << "No translation found for: " << wordToTranslate;
    return wordTranslation;
}

bool translators::TextToNumberTranslator::isANumberConnector(std::vector<std::string>::iterator wordIterator)
{
    bool retVal=false;
    std::vector<std::string>::iterator nextWordIterator = wordIterator;
    std::advance(nextWordIterator, 1);

    WordTranslation nextWordTranslation = getWordTranslation(*nextWordIterator);
    if(nextWordTranslation.type == translators::WordType::NUMBER)
    {
        retVal = true;
    }

    return retVal;
}