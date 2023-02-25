
#include <vector>
#include <string>
#include <unordered_map>

enum class Identifier
{
    id
};

enum class Keyword
{
    as,
    end,
    begin,
    state,
    define,
    header,
    section,
    alphabet,
    automaton,
};

enum class Separator
{
    endl,
    comma,
    open_parethesis,
    close_parethesis,
};

enum class Literal
{
    string,
    numeric,
    boolean,
    integral,
    identifier
};

class LanguageNode
{
public:
    LanguageNode(const std::string &token)
        : token(token) {}

    LanguageNode &expect(Keyword keyword)
    {
    }

    LanguageNode &expect(Literal l)
    {
    }

    LanguageNode &expect(Separator keyword)
    {
    }

    LanguageNode &expect(Identifier l)
    {
    }

    LanguageNode *getChild(const std::string &tokenChild) noexcept
    {
        for (auto &child : children)
        {
            if (child.token == tokenChild || child.token == "\\*\\")
                return &child;
        }
        return nullptr;
    }

private:
    std::string token;
    std::vector<LanguageNode> children;
};

std::vector<std::string> tokenize(std::string const &chain)
{
    using namespace std::string_literals;

    std::vector<std::string> tokens;

    std::string current;

    for (auto c : chain)
    {
        if (c == ' ')
        {
            if (current.length() > 0)
                tokens.emplace_back(current);
            current.clear();
            continue;
        }

        if ("()\n"s.find(c) != std::string::npos)
        {
            if (!current.empty())
            {
                tokens.emplace_back(current);
                current.clear();
            }
            current.push_back(c);
            tokens.emplace_back(current);
            current.clear();
            continue;
        }

        current.push_back(c);
    }

    return tokens;
}

class Token
{
    std::string_view value;
    std::size_t line;
};

class Language
{
private:
    inline static std::unordered_map<Keyword, std::string_view> ReservedKeywords{
        {Keyword::as            , "as"          },
        {Keyword::end           , "end"         },
        {Keyword::begin         , "begin"       },
        {Keyword::state         , "state"       },
        {Keyword::begin         , "begin"       },
        {Keyword::header        , "header"      },
        {Keyword::define        , "define"      },
        {Keyword::section       , "section"     },
        {Keyword::alphabet      , "alphabet"    },
        {Keyword::automaton     , "automaton"   },
    };

    std::vector<Token> tokens;
};

int main()
{
    std::string test = "begin section numeric\n";

    LanguageNode root("");

    auto &insection = root.expect(Keyword::begin).expect(Keyword::section).expect(Identifier::id).expect(Separator::endl);

    auto &define = insection.expect(Keyword::define);
    auto &end = insection.expect(Keyword::end);

    define.expect(Keyword::alphabet).expect(Literal::string).expect(Keyword::as).expect(Literal::string).expect(Literal::identifier).expect(Separator::endl);
    define.expect(Keyword::automaton);

    LanguageNode *current = &root;

    for (auto token : tokenize(test))
    {
        std::printf("Current: %s\n", token.c_str());
        current = current->getChild(token);
        if (!current)
        {
            std::printf("Sintax error\n");
            break;
        }
    }
}
