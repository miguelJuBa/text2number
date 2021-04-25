#ifndef __H_ITRANSLATOR__
#define __H_ITRANSLATOR__

#include <string>

namespace translators
{
    class ITranslator
    {
        public:
            virtual std::string translate(const std::string &textToTranslate) = 0;
    };
}

#endif