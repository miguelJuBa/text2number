#ifndef __H_TEXT_TOOLS__
#define __H_TEXT_TOOLS__

#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

namespace Tools
{
    namespace Text
    {
        std::vector<std::string> textToTokens(const std::string &text, const std::string &separator)
        {
            boost::char_separator<char> splitBy(separator.c_str());
            boost::tokenizer<boost::char_separator<char>> tokens(text, splitBy);
            std::vector<std::string> tokenVector;

            for(auto &token : tokens)
            {
                tokenVector.push_back(token);
            }

            return tokenVector;
        }
    }
}

#endif