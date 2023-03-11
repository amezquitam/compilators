
#include <automaton.hpp>

Automat RomanNumberAutomaton;

bool has_been_initialized = false;

void InitAutomaton()
{
    if (has_been_initialized) return;

    auto I = Alphabet("I", "I");
    auto V = Alphabet("V", "V");
    auto X = Alphabet("X", "X");
    auto L = Alphabet("L", "L");
    auto C = Alphabet("C", "C");
    auto D = Alphabet("D", "D");
    auto M = Alphabet("M", "M");

    RomanNumberAutomaton.RegistAlphabets({I, V, X, L, C, D, M});

    RomanNumberAutomaton.MakeTable(
                   {"I", "V", "X" , "L" , "C" , "D" , "M"},
        {
            {"0",  {"1", "V", "6" , "9" , "11", "14", "15"}, false},
            {"1",  {"2", "3", "3" , "E" , "E" , "E" , "E" }, true },
            {"2",  {"3", "E", "E" , "E" , "E" , "E" , "E" }, true },
            {"3",  {"E", "E", "E" , "E" , "E" , "E" , "E" }, true },
            {"V",  {"5", "E", "E" , "E" , "E" , "E" , "E" }, true },
            {"4",  {"7", "E", "E" , "E" , "E" , "E" , "E" }, true },
            {"5",  {"2", "E", "E" , "E" , "E" , "E" , "E" }, true },
            {"6",  {"1", "V", "7" , "10", "8" , "E" , "E" }, true },
            {"7",  {"1", "V", "8" , "E" , "E" , "E" , "E" }, true },
            {"8",  {"1", "V", "E" , "E" , "E" , "E" , "E" }, true },
            {"9",  {"1", "V", "6" , "E" , "E" , "E" , "E" }, true },
            {"10", {"1", "V", "6" , "9" , "11", "12", "12"}, true },
            {"11", {"1", "V", "6" , "9" , "12", "13", "13"}, true },
            {"12", {"1", "V", "6" , "9" , "13", "E" , "E" }, true },
            {"13", {"1", "V", "6" , "9" , "E" , "E" , "E" }, true },
            {"14", {"1", "V", "6" , "9" , "11", "E" , "E" }, true },
            {"15", {"1", "V", "6" , "9" , "11", "14", "16"}, true },
            {"16", {"1", "V", "6" , "9" , "10", "14", "17"}, true },
            {"17", {"1", "V", "6" , "9" , "10", "14", "E" }, true },
            {"E",  {"E", "E", "E" , "E" , "E" , "E" , "E" }, false},
        });
    
    has_been_initialized = true;
}

bool IsRoman(const char *str)
{
    InitAutomaton();

    bool IsValid = RomanNumberAutomaton.Validate(str);

    return IsValid;
}
