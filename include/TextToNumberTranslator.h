#ifndef __H_TEXT_TO_NUMBER_TRANSLATOR__
#define __H_TEXT_TO_NUMBER_TRANSLATOR__

#include <map>
#include <utility>
#include <vector>

#include "ITranslator.hpp"

namespace translators
{
    enum class WordType
    {
        NUMBER,
        UNIT,
        CONNECTOR,
        WORD
    };

    struct WordTranslation
    {
        WordType type;
        unsigned long translation;
    };

    class TextToNumberTranslator : public ITranslator
    {
        public:
            TextToNumberTranslator();
            ~TextToNumberTranslator();
            std::string translate(const std::string &textToTranslate);

        private:
            WordTranslation getWordTranslation(const std::string &wordToTranslate);
            bool isANumberConnector(std::vector<std::string>::iterator wordIterator);

            std::map<std::string, unsigned long> m_unitsDictionary = {
                {"hundred", 100},
                {"thousand", 1000},
                {"million", 1000000},
                {"billion", 1000000000}
            };

            std::map<std::string, unsigned long> m_connectorDictionary = {
                {"and", 0}
            };

            std::map<std::string, unsigned long> m_numbersDictionary = {
                {"one", 1},
                {"two", 2},
                {"three", 3},
                {"four", 4},
                {"five", 5},
                {"six", 6},
                {"seven", 7},
                {"eigh", 8},
                {"nine", 9},
                {"ten", 10},
                {"eleven", 11},
                {"twelve", 12},
                {"thridteen", 13},
                {"fourteen", 14},
                {"fifteen", 15},
                {"sixteen", 16},
                {"seventeen", 17},
                {"eighteen", 18},
                {"nineteen", 19},
                {"twenty", 20},
                {"twenty one", 21},
                {"twenty two", 22},
                {"twenty three", 23},
                {"twenty four", 24},
                {"twenty five", 25},
                {"twenty six", 26},
                {"twenty seven", 27},
                {"twenty eight", 28},
                {"twenty nine", 29},
                {"thirty", 30},
                {"thirty one", 31},
                {"thirty two", 32},
                {"thirty three", 33},
                {"thirty four", 34},
                {"thirty five", 35},
                {"thirty six", 36},
                {"thirty seven", 37},
                {"thirty eigh", 38},
                {"thirty nine", 39},
                {"forty", 40},
                {"forty one", 41},
                {"forty two", 42},
                {"forty three", 43},
                {"forty four", 44},
                {"forty five", 45},
                {"forty six", 46},
                {"forty seven", 47},
                {"forty eigh", 48},
                {"forty nine", 49},
                {"fifty", 50},
                {"sixty", 60},
                {"seventy", 70},
                {"eighty", 80},
                {"ninety", 90}
            };
    };
}

#endif