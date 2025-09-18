#include <string>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/argparser.h"

TEST_CASE("ShouldCreateArgParseObjectWithEmptyOptions") {
  ap::ArgParser argParser;
  CHECK(argParser.get_options_size() == 0);
}

TEST_CASE("ShouldAddArguments") {
  ap::ArgParser argParser;

  bool value = false;
  argParser.add_arguments("-h", "--help", &value, ap::BOOL);
  argParser.add_arguments("-l", "--len", &value, ap::INT);

  CHECK(argParser.get_options_size() == 2);
}

TEST_CASE("ShouldShowAllArgumentInUsageReport") {
  ap::ArgParser argParser;

  bool value = false;
  argParser.add_arguments("-h", "--help", &value, ap::BOOL);
  argParser.add_arguments("-l", "--len", &value, ap::INT);

  std::string usage = argParser.usage();
  // test de content of usage should not be empty
  // tests the content should be exact like this...
}

TEST_CASE("ShouldParserBoolFlags") {}

TEST_CASE("ShouldParserIntegerFlags") {}

TEST_CASE("ShouldCombinedShortArgumentsBoolFlags") {}

TEST_CASE("ShouldReturnErrorIfNotEspecifiedValueOfTheArgument") {}
