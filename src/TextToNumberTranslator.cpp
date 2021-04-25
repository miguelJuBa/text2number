#include <algorithm>
#include <iterator>
#include <cctype>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
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
    boost::char_separator<char> sep(" ");
    boost::tokenizer<boost::char_separator<char>> tokens(textToTranslate, sep);

    //std::vector<std::string> vtokens = Tools::Text::textToTokens(textToTranslate, " ");
    
    //2) Iterate through every token to translate words existing in the dictionary into numbers.
    std::stringstream translatedTextStream;
    unsigned long numberTranslated = 0;
    std::string lowerCaseWord;
    std::string word;

    for (boost::tokenizer<boost::char_separator<char>>::iterator tokenIter = tokens.begin(); tokenIter != tokens.end(); ++tokenIter)
    {
        word = *tokenIter;
        lowerCaseWord = word;
        std::transform(lowerCaseWord.begin(), lowerCaseWord.end(), lowerCaseWord.begin(),
        [](unsigned char c){ return std::tolower(c); });

        auto numberIterator = m_numbersDictionary.find(lowerCaseWord);
        if(numberIterator != m_numbersDictionary.end())
        {
            numberTranslated += numberIterator->second;
            BOOST_LOG_TRIVIAL(debug) << "Translation: " << numberIterator->first << " to: " << numberTranslated;
        }
        else
        {
            auto unitsIterator = m_unitsDictionary.find(lowerCaseWord);
            if(unitsIterator != m_unitsDictionary.end())
            {
                numberTranslated *= unitsIterator->second;
                BOOST_LOG_TRIVIAL(debug) << "Translation: " << unitsIterator->first << " to: " << numberTranslated;
            }
            else
            {
                auto connectorIterator = m_connectorDictionary.find(lowerCaseWord);
                if(connectorIterator != m_connectorDictionary.end())
                {
                    boost::tokenizer<boost::char_separator<char>>::iterator tokenIterBack = tokenIter;
                    std::advance(tokenIterBack, 1);
                    BOOST_LOG_TRIVIAL(trace) << "Connector found: -" << word << "- next: " << *tokenIterBack;
                    auto numberIterator = m_numbersDictionary.find(*tokenIterBack);
                    if(numberTranslated == 0)
                    {
                        translatedTextStream << word << " ";
                    }
                    if(numberIterator == m_numbersDictionary.end())
                    {
                        translatedTextStream << std::to_string(numberTranslated) << " " << word << " ";
                        numberTranslated=0;
                    }
                }
                else
                {
                    BOOST_LOG_TRIVIAL(trace) << "No translation found for: " << word;
                    if(numberTranslated > 0)
                    {
                        translatedTextStream << std::to_string(numberTranslated) << " " << word << " ";
                        numberTranslated = 0;
                    }
                    else
                    {
                        translatedTextStream << word << " ";
                    }                    
                }   
            }           
        }
    }

    // Remainder found.
    if(numberTranslated > 0)
    {
        translatedTextStream << std::to_string(numberTranslated);
    }

    //4) Trim any possible ending spaces.
    std::string translatedText = translatedTextStream.str();
    boost::trim_right(translatedText);
    return translatedText;
}
