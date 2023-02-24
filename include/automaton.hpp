#pragma once

#include <vector>
#include <cstdio>
#include <string>
#include <string_view>
#include <unordered_map>
#include <initializer_list>

#include "alphabet.hpp"

void MyAssert(bool Exp, std::string_view Message)
{
    if (!Exp)
        printf("Assertion Failed: %s", Message.data());
}

class Automaton
{
public:
    struct State
    {
        std::string_view name;
        std::initializer_list<std::string_view> states;
        bool IsValid;
    };

    void RegistAlphabets(std::initializer_list<Alphabet> alphabets)
    {
        m_alphabets.reserve(alphabets.size());
        m_alphabets.insert(m_alphabets.cend(), alphabets);
    }

    void MakeTable(std::initializer_list<std::string_view> alphabets,
                   std::initializer_list<State> states)
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

    bool Validate(std::string_view TestCh)
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

private:
    void AssertAlphabetRegistered(std::string_view alphabet_name)
    {
        using namespace std::string_literals;

        bool IsRegistered = false;
        for (auto &m_alphabet : m_alphabets)
            if (m_alphabet.name == alphabet_name)
                IsRegistered = true;

        MyAssert(IsRegistered, std::string(alphabet_name) + " no esta registrado");
    }

    std::pair<std::string_view, bool> GetAlphabetOf(char c)
    {
        for (auto &alph : m_alphabets)
            if (alph.has(c))
                return {alph.name, false};

        return {"", true};
    }

private:
    std::string_view m_InitialState;

    std::vector<Alphabet> m_alphabets;

    std::unordered_map<
        std::string_view,
        std::unordered_map<std::string_view, std::string_view>>
        m_table;

    std::unordered_map<std::string_view, bool> m_ValidTable;
};
