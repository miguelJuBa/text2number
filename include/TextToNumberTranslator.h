#ifndef __H_TEXT_TO_NUMBER_TRANSLATOR__
#define __H_TEXT_TO_NUMBER_TRANSLATOR__

#include <map>

#include "ITranslator.hpp"
#include <boost/tokenizer.hpp>


namespace translators
{
    class TextToNumberTranslator : public ITranslator
    {
        public:
            TextToNumberTranslator();
            ~TextToNumberTranslator();
            std::string translate(const std::string &textToTranslate);

        private:


            std::map<std::string, unsigned long> m_unitsDictionary = {
                {"hundred", 100},
                {"thousand", 1000},
                {"million", 1000000},
                {"billion", 1000000000}
            };

            std::map<std::string, unsigned long> m_numbersDictionary = {
                {"one", 1},
                {"two", 2},
                {"three", 3},
                {"four", 4},
                {"five", 5},
                {"six", 6},
                {"seven", 7},
                {"height", 8},
                {"nine", 9},
                {"ten", 10},
                {"thirty", 30}
            };

            std::map<std::string, unsigned long> m_connectorDictionary = {
                {"and", 0}
            };
    };
}

#endif