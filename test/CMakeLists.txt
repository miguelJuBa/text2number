add_executable(text2numberTests main.cpp
    TextToNumberTranslatorTests.cpp
    ${text2number_SOURCE_DIR}/src/TextToNumberTranslator.cpp
)

include_directories(${text2number_SOURCE_DIR}/external 
    ${text2number_SOURCE_DIR}/include
)

target_link_libraries(text2numberTests Boost::log Boost::log_setup)