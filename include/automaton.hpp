#pragma once

#include <vector>
#include <cstdio>
#include <string>
#include <string_view>
#include <unordered_map>

#include "alphabet.hpp"

void MyAssert(bool Exp, std::string_view Message);

class Automat
{
public:
    struct State
    {
        std::string_view name;
        std::vector<std::string_view> states;
        bool IsValid;
    };

    void RegistAlphabets(std::vector<Alphabet> const &alphabets);

    void MakeTable(std::vector<std::string_view> const alphabets, std::vector<State> const states);

    bool Validate(std::string_view TestCh);

private:
    void AssertAlphabetRegistered(std::string_view alphabet_name);

    std::pair<std::string_view, bool> GetAlphabetOf(char c);

private:
    std::string_view m_InitialState;

    std::vector<Alphabet> m_alphabets;

    std::unordered_map<
        std::string_view,
        std::unordered_map<std::string_view, std::string_view>>
        m_table;

    std::unordered_map<std::string_view, bool> m_ValidTable;
};
