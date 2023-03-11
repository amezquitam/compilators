#include <automaton.hpp>

void MyAssert(bool Exp, std::string_view Message)
{
  if (!Exp)
    printf("Assertion Failed: %s", Message.data());
}

void Automat::RegistAlphabets(std::vector<Alphabet> const &alphabets)
{
  m_alphabets.reserve(alphabets.size());
  m_alphabets.insert(m_alphabets.end(), alphabets.begin(), alphabets.end());
}

void Automat::MakeTable(std::vector<std::string_view> alphabets, std::vector<State> states)
{
  for (auto &state : states)
  {
    MyAssert(state.states.size() == alphabets.size(), "El numero de columnas debe ser igual en todas las filas");
  }

  for (auto &alphabet : alphabets)
  {
    AssertAlphabetRegistered(alphabet);
  }

  for (auto &state : states)
  {
    for (int i = 0; i < alphabets.size(); ++i)
    {
      m_table[state.name][alphabets.begin()[i]] = state.states.begin()[i];
    }

    // Fill valid table
    m_ValidTable[state.name] = state.IsValid;
  }

  for (auto &state : states)
  {
    for (auto &substate : state.states)
    {
      MyAssert(m_table.find(substate) != m_table.end(), std::string(substate) + " no es un estado registrado");
    }
  }

  m_InitialState = states.begin()[0].name;
}

bool Automat::Validate(std::string_view TestCh)
{
  std::string_view state = m_InitialState;

  for (auto c : TestCh)
  {
    auto [alph, err] = GetAlphabetOf(c);

    if (err)
      return false;

    state = m_table[state][alph];
  }

  return m_ValidTable[state];
}

void Automat::AssertAlphabetRegistered(std::string_view alphabet_name)
{
  bool IsRegistered = false;
  for (auto &m_alphabet : m_alphabets)
    if (m_alphabet.name == alphabet_name)
      IsRegistered = true;

  MyAssert(IsRegistered, std::string(alphabet_name) + " no esta registrado");
}

std::pair<std::string_view, bool> Automat::GetAlphabetOf(char c)
{
  for (auto &alph : m_alphabets)
    if (alph.has(c))
      return {alph.name, false};

  return {"", true};
}