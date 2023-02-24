#include <cli.hpp>
#include <iostream>

void cli::ConsoleApplication::AddCommand(String cname, Action action, int argc)
{
    Options[cname] = Option{argc, action};
}

void cli::ConsoleApplication::Execute(int argc, const char **args)
{
    for (int i = 1; i < argc; ++i)
    {
        String command = args[i];

        if (!Exists(command)) 
        {
            CommandNotExistError(command);
            return;
        }

        auto& options = Options[command];
        int NumOfArgsProvided = argc - i - 1;

        if (NumOfArgsProvided < options.NumOfArgs)
        {
            ArgumentNotProvidedError(command, NumOfArgsProvided);
            return;
        }

        ExecuteCommand(command, args + i + 1);
        i += options.NumOfArgs;
    }
}

void cli::ConsoleApplication::ExecuteCommand(String command, const char **args)
{
    auto option = Options[command];
    option.action(option.NumOfArgs, args);
}

bool cli::ConsoleApplication::Exists(String& command)
{
    return Options.find(command) != Options.end();
}

void cli::ConsoleApplication::CommandNotExistError(String& command)
{
    std::printf("%s: Command don't exists\n", command.c_str());
}

void cli::ConsoleApplication::ArgumentNotProvidedError(String& command, int numOfArgsProv)
{
    auto& option = Options[command];
    std::printf("%s: Require %d arguments, and %d was provided", command.c_str(), option.NumOfArgs, numOfArgsProv);
}
