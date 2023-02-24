#pragma once

/**
 * Esta clase tiene que manejar el comportamiento a la hora de
 * ejecutar la aplicacion,de saber que hacer teniendo en cuenta
 * la entrada del usuario.
 *
 * Uno de los requerimientos, es que el usuario de esta clase
 * pueda definir comportamientos de forma jerarquica
 *
 * Por ejemplo:
 *
 * void PrintHelpMessage();
 * void Save(std::string arg);
 *
 * ConsoleApplication cli;
 *
 * cli.AddCommand("-(-help|h)", PrintHelpMessage);
 * cli.AddCommand("-s *", Save);
 *
 * En este caso el programa buscará primero el comando `help` y lo ejecutara
 *
 *
 */

#include <unordered_map>
#include <functional>
#include <string>

namespace cli
{
    using String = std::string;

    using Action = std::function<void(int, const char **)>;

    struct Option
    {
        int NumOfArgs{};
        Action action{};
    };

    class ConsoleApplication
    {
    public:
        template <typename Key, typename Value>
        using HashMap = std::unordered_map<Key, Value>;

        void AddCommand(String cname, Action action, int argc);

        void Execute(int argc, const char **args);

    private:

        void ExecuteCommand(String command, const char** args);

        bool Exists(String& command);

        void CommandNotExistError(String& command);

        void ArgumentNotProvidedError(String& command, int numOfArgsProv);

        HashMap<String, Option> Options;
    };

} // namespace cli
