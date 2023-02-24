
#include <automaton.hpp>
#include <iostream>

int main(int argc, const char* args[])
{
    Automaton NumericExpresion;

    auto D = Alphabet("Digit", "0123456789");
    auto P = Alphabet("Point", "."         );
    auto E = Alphabet(  "Exp", "Ee"        );
    auto S = Alphabet( "Sign", "+-"        );

    NumericExpresion.RegistAlphabets({D, P, E, S});
    
    NumericExpresion.MakeTable(
                        { "Digit", "Point", "Exp", "Sign"},
        {
            { "Init" ,  { "Digit", "Point", "Err", "Sign"}, false },
            { "Sign" ,  { "Digit", "Point", "Err", "Err" }, false },
            { "Digit",  { "Digit", "DSDP" , "ED" , "Err" }, true  },
            { "DSDP" ,  { "DSDP" , "Err"  , "ED" , "Err" }, true  },
            { "ED"   ,  { "DED"  , "Err"  , "Err", "DES" }, false },
            { "DED"  ,  { "DED"  , "Err"  , "Err", "Err" }, true  },
            { "DES"  ,  { "DED"  , "Err"  , "Err", "Err" }, false },
            { "Point",  { "DSDP" , "Err"  , "Err", "Err" }, false },
            { "Err"  ,  { "Err"  , "Err"  , "Err", "Err" }, false },
        }
    );

    if (argc > 1) 
    {
        bool IsValid = NumericExpresion.Validate(args[1]);
        std::printf("La frase ingresada %s es una expresion numerica\n", (IsValid ? "" : "no"));
    }

    return 0;
}
