add_executable(text2number main.cpp 
    MainApp.cpp
    TextToNumberTranslator.cpp
)

include_directories(${text2number_SOURCE_DIR}/include)

target_link_libraries(text2number Boost::log Boost::log_setup)