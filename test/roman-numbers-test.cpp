#include <gtest/gtest.h>
#include <roman-numbers.hpp>
#include <fstream>
#include <string>

TEST(RomanNumbers, Test)
{
  std::ifstream file(std::string(RESOURCES_PATH) + "test_file");

  std::string line;

  while (!file.eof())
  {
    std::getline(file, line);
    std::cout << line << '\n';
    ASSERT_TRUE(IsRoman(line.c_str()));
  }
}