#include <gtest/gtest.h>
#include <numeric-expresion.hpp>

using string = const char*;

string acepting[] {
  "45.4e-4", "45.4E-4", "-45.4e-4", 
  "45.e-4", "45.4E-4", "-45.4E-4", 
  "98.5e4", "45.4E-4", "-45.e-4", 
  ".4e-1", "45.4E-4", "-45.E-4", 
};

string rejecting[] {
  "45.4e-", "+-45.4E-4", "--45.4e-4", 
  "4.5.e-4", "45,4eE-4", "0-45.4E-4", 
  "98,5e4", "45.4f-4", "-45.e", 
  ".4e--1", "45..4E-4", "-.45,E-4", 
};


TEST(NumericExpresions, Test)
{
  for (auto &&str : acepting)
  {
    std::printf("str: %s\n", str);
    ASSERT_TRUE(isNumericExpression(str));
  }

  for (auto &&str : rejecting)
  {
    std::printf("str: %s\n", str);
    ASSERT_FALSE(isNumericExpression(str));
  }
}