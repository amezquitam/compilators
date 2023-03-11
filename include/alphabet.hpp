#pragma once

#include <string>

class Alphabet
{
public:
    Alphabet(const char *name, const char *characters);

    Alphabet(const char *name, std::string &&characters);

    Alphabet(const char *name, Alphabet const& other);

private:
    void format() noexcept;

public:
    bool has(char val) const noexcept;

    Alphabet operator +(const Alphabet& other);

public:
    std::string name;
    std::string characters;
};

