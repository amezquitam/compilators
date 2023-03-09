#include <numeric-expresion.hpp>
#include <cstdio>

int main(int argc, char const *argv[])
{
  if (argc > 1)
  {
    bool IsValid = isNumericExpression(argv[1]);
    std::printf("La expresion '%s'%s es una expresion numerica\n", argv[1], (IsValid ? "" : " no"));
  }

  return 0;
}