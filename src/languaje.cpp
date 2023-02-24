
#include <vector>
#include <string>

class LanguageNode
{
public:
    LanguageNode(const std::string &token)
        : token(token) {}

    LanguageNode &expect(std::string const &newChild)
    {
        return children.emplace_back(newChild);
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

        if ("'()\n"s.find(c) != std::string::npos)
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

int main()
{
    std::string test = "begin section numeric\n";

    LanguageNode root("");

    auto& begin = root.expect("begin");

    auto &section = begin.expect("section");

    auto &expr = section.expect("\\*\\");

    expr.expect("\n");

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
