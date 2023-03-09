#include <roman-numbers.hpp>
#include <cstdio>

int main(int argc, char const *argv[])
{
  if (argc > 1)
  {
    printf("La cadena '%s' %ses un numero romano\n", argv[1], IsRoman(argv[1]) ? "" : "no ");
  }
  return 0;
}

