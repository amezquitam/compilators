#include <cli.hpp>
#include <fstream>

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

std::string getFileContent(const char* filename)
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

void loadFile(int argc, const char **argv)
{
    std::string fileContent = getFileContent(argv[0]);

    for (auto c : fileContent)
    {
        if (c == ' ' || c == '\n') 
        {
            continue;
        }
    }
}

int main(int argc, char const *argv[])
{
    cli::ConsoleApplication app;

    app.AddCommand("--help", help, 0);
    app.AddCommand("-l", loadFile, 1);

    app.Execute(argc, argv);

    return 0;
}
