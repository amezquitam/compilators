#pragma once

#include <string>
#include <algorithm>

/**
 * ---------------------------------------------------
 *          "Digito"    "Punto"     "Exp"   "Signo"
 * ---------------------------------------------------
 * "ini"    "digito"    "P"         "Err"   "signo"
 */

class Alphabet
{
public:
    Alphabet(const char *name, const char *characters)
        : name(name), characters(characters)
    {
        format();
    }

    Alphabet(const char *name, std::string &&characters)
        : name(name), characters(std::move(characters))
    {
        format();
    }

    Alphabet(const char *name, Alphabet alph)
        : name(name), characters(std::move(alph.characters))
    {
        format();
    }

private:
    void format() noexcept
    {
        std::sort(characters.begin(), characters.end());
    }

public:
    bool has(char val) const noexcept
    {
        for (auto c : characters)
            if (c == val)
                return true;
        return false;
    }

public:
    std::string name;
    std::string characters;
};

Alphabet operator+(Alphabet const &A1, Alphabet const &A2)
{
    return Alphabet("name", A1.characters + A2.characters);
}
