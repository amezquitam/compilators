#include <automaton.hpp>

int main(int argc, char const *argv[])
{
  Automaton NumericExpresion;
  
  NumericExpresion.RegistAlphabets({
    Alphabet( "numbers", "0123456789" ),
    Alphabet(   "signs", "+-"         ),
    Alphabet("exponent", "Ee"         ),
    Alphabet(   "point", "."          )
  });

  NumericExpresion.MakeTable (
                  { "numbers", "point", "exponent", "signs"},
    {
      { "Init" ,  {   "Digit", "Point",      "Err",  "Sign"}, false },
      { "Sign" ,  {   "Digit", "Point",      "Err",  "Err" }, false },
      { "Digit",  {   "Digit",  "DSDP",       "ED",  "Err" }, true  },
      { "DSDP" ,  {    "DSDP",   "Err",       "ED",  "Err" }, true  },
      { "ED"   ,  {     "DED",   "Err",      "Err",  "DES" }, false },
      { "DED"  ,  {     "DED",   "Err",      "Err",  "Err" }, true  },
      { "DES"  ,  {     "DED",   "Err",      "Err",  "Err" }, false },
      { "Point",  {    "DSDP",   "Err",      "Err",  "Err" }, false },
      { "Err"  ,  {     "Err",   "Err",      "Err",  "Err" }, false },
    }
  );

  if (argc > 1) 
  {
    bool IsValid = NumericExpresion.Validate(argv[1]);
    std::printf("La expresion '%s'%s es una expresion numerica\n", argv[1], (IsValid ? "" : " no"));
  }

  return 0;
}
