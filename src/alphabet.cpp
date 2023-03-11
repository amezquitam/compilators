#include <alphabet.hpp>
#include <algorithm>

Alphabet::Alphabet(const char *name, const char *characters)
    : name(name), characters(characters)
{
  format();
}

Alphabet::Alphabet(const char *name, std::string &&characters)
    : name(name), characters(std::move(characters))
{
  format();
}

Alphabet::Alphabet(const char *name, Alphabet const &other) 
  : name(name), characters(other.characters)
{
  format();
}

void Alphabet::format() noexcept
{
  std::sort(characters.begin(), characters.end());
}

bool Alphabet::has(char val) const noexcept
{
  for (auto c : characters)
    if (c == val)
      return true;
  return false;
}

Alphabet Alphabet::operator+(const Alphabet &other)
{
  return Alphabet("default", characters + other.characters);
}
