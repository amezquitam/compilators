#include <automaton.hpp>
#include <numeric-expresion.hpp>

Automat NumericExpresion;

void initNumericExpresion() {
  static bool initialized = false; 

  if (initialized) return;

  NumericExpresion.RegistAlphabets({
    Alphabet( "numbers", "0123456789" ),
    Alphabet(   "signs", "+-"         ),
    Alphabet("exponent", "Ee"         ),
    Alphabet(   "point", "."          )
  });

  NumericExpresion.MakeTable (
                  { "numbers", "point", "exponent", "signs"},
    {
      { "Init" ,  {   "Digit", "Point",      "Err",  "Sign"}, false }, // estado inicial
      { "Sign" ,  {   "Digit", "Point",      "Err",  "Err" }, false }, // primer signo
      { "Digit",  {   "Digit",  "DSDP",       "ED",  "Err" }, true  }, // digitos antes del exponente y punto
      { "DSDP" ,  {    "DSDP",   "Err",       "ED",  "Err" }, true  }, // digitos despues del punto
      { "ED"   ,  {     "DED",   "Err",      "Err",  "DES" }, false }, // exponente
      { "DED"  ,  {     "DED",   "Err",      "Err",  "Err" }, true  }, // digitos del exponente
      { "DES"  ,  {     "DED",   "Err",      "Err",  "Err" }, false }, // digitos despues del signo del exponente
      { "Point",  {    "DSDP",   "Err",      "Err",  "Err" }, false }, // punto
      { "Err"  ,  {     "Err",   "Err",      "Err",  "Err" }, false }, // error irreparable
    }
  );

  initialized = true;
}

bool isNumericExpression(const char* str)
{
  initNumericExpresion();
  return NumericExpresion.Validate(str);
}

