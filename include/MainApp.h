#ifndef __H_MAIN_APP__
#define __H_MAIN_APP__

#include <string>

namespace mainApp
{
    class MainApp
    {
        public:
            MainApp();
            ~MainApp();

            // Calling this method with the input paramerts from main function will
            // start MainApp execution.
            void run(int argc, char ** argv);

        private:        
            std::string parseCommandlineParameters(int numberOfParameters, char ** parameters);

            std::string m_textToTranslate;
    };
}

#endif