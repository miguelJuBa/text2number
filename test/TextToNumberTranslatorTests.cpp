#include "catch2/catch.hpp"

#include "TextToNumberTranslator.h"


TEST_CASE("Empty text will return an empty translation", "[TextToNumberTranslator]") 
{
    translators::TextToNumberTranslator translator;
    const std::string translation = translator.translate("");

    REQUIRE(translation.empty() == true);
}

TEST_CASE("Non empty text will return always something", "[TextToNumberTranslator]") 
{
    translators::TextToNumberTranslator translator;
    const std::string translation = translator.translate("Hello there");

    REQUIRE(translation.empty() == false);
}

TEST_CASE("Number intervals boundaries will translate correctly", "[TextToNumberTranslator]") 
{
    translators::TextToNumberTranslator translator;

    const std::string oneTranslation = translator.translate("one");
    const std::string oneTranslationCheck("1");
    REQUIRE(oneTranslation == oneTranslationCheck);

    const std::string oneBillionTranslation = translator.translate("one billion");
    const std::string oneBillionTranslationCheck("1000000000");
    REQUIRE(oneBillionTranslation == oneBillionTranslationCheck);
}

TEST_CASE("Upper case & lower case must not matter", "[TextToNumberTranslator]")
{
    translators::TextToNumberTranslator translator;
    const std::string mixedCaseTranslation = translator.translate("One hunDreD thIrtY FouR");
    const std::string mixedCaseTranslationCheck("134");
    REQUIRE(mixedCaseTranslation == mixedCaseTranslationCheck);
}

TEST_CASE("'And' word must not affect the translation", "[TextToNumberTranslator]")
{
    translators::TextToNumberTranslator translator;
    const std::string separatorsTranslation = translator.translate("I have one hundred and one apples");
    const std::string separatorsTranslationCheck("I have 101 apples");
    REQUIRE(separatorsTranslation == separatorsTranslationCheck);
}

TEST_CASE("'And' word can be part of a phrase without a name", "[TextToNumberTranslator]")
{
    translators::TextToNumberTranslator translator;
    const std::string andTranslation = translator.translate("I have one hundred and one apples and one lemon");
    const std::string andTranslationCheck("I have 101 apples and 1 lemon");
    REQUIRE(andTranslation == andTranslationCheck);
}

TEST_CASE("'And' between numbers but not as part of them", "[TextToNumberTranslator]")
{
    translators::TextToNumberTranslator translator;
    const std::string andTranslation = translator.translate("Number one and number two");
    const std::string andTranslationCheck("Number 1 and number 2");
    REQUIRE(andTranslation == andTranslationCheck);
}