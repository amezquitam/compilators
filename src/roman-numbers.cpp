#include <cli.hpp>
#include <fstream>
#include <unordered_map>
#include <automaton.hpp>

std::unordered_map<std::string, Automaton> automatons;
std::unordered_map<std::string, Alphabet> alphabets;

const char *helpMessage = R"(     
    Usage: 
        automaton [Options]
    Options:
        -l                  Load an auto file
        -s                  Select the section
        -a                  Select the automaton
        -e                  Specify the expresion to eval
        -h                  Prints this message
    Example
        automaton -l test.auto -s my-section -a 'MyAutomaton' -e 'Expresion'
)";

void help(int, char const **)
{
    printf("%s", helpMessage);
}

std::string getFileContent(const char *filename)
{
    std::string fileContent, buffer;
    std::ifstream autofile(filename, std::ios::binary);

    while (!autofile.eof())
    {
        std::getline(autofile, buffer);
        fileContent.append(buffer + "\n");
    }

    return fileContent;
}

std::vector<std::string> tokenize(std::string &source)
{
    std::vector<std::string> tokens;
    std::string currentToken;

    std::string specialChars = "()";

    for (int i = 0; i < source.length(); ++i)
    {
        auto c = source[i];

        if (c == '\'')
        {
            int j = source.find('\'', i + 1);
            tokens.push_back(source.substr(i, j - i + 1));
            i = j;
            continue;
        }

        if (c == ' ')
        {
            if (currentToken.length() > 0)
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            continue;
        }

        if (c == '\n')
        {
            if (tokens.size() > 0 and tokens.back() != "\n")
            {
                if (currentToken.length())
                {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
                tokens.push_back("\n");
            }
            continue;
        }

        if (specialChars.find(c) != std::string::npos)
        {
            if (currentToken.length() > 0)
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string("") + c);
            continue;
        }

        currentToken.push_back(c);
    }

    return tokens;
}

// define alphabet 'name' as 'chars'
void defineAlphabet(std::string const &name, std::string const &chars)
{
    alphabets[name] = Alphabet(name.c_str(), chars.c_str());
}

void defineAutomaton(std::string const &name)
{
    automatons[name] = Automaton();
}

void defineHeader(std::string const& autoName, std::vector<std::string>& alphanames)
{
}

void loadFile(int argc, const char **argv)
{
    std::string fileContent = getFileContent(argv[0]);
    auto tokens = tokenize(fileContent);
}

int main(int, char const *[])
{
    int argc = 3;
    const char *argv[] = {"/home/miguel/Documents/github/amezquitam/Compilators/src", "-l", "/home/miguel/Documents/github/amezquitam/Compilators/src/roman-numbers.auto"};

    cli::ConsoleApplication app;

    app.AddCommand("--help", help, 0);
    app.AddCommand("-l", loadFile, 1);

    app.Execute(argc, argv);

    return 0;
}
