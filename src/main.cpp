#include <spdlog/spdlog.h>

#include <CLI/CLI.hpp>
#include <cstdlib>
#include <cstring>
#include <list>
#include <sstream>

#include "myproject/myproject.h"

bool extract_command(float& a, float& b, char& c, const std::string& message)
{
    try
    {
        std::stringstream iss(message);
        std::string str;
        iss >> str;
        a = std::stof(str);
        iss >> str;
        if (str.size() != 1)
        {
            std::__throw_invalid_argument(
                (std::string("Supporting only single-character operators: ") + str).c_str());
            return false;
        }
        c = str[0];
        iss >> str;
        b = std::stof(str);
        return true;
    }
    catch (std::exception& e)
    {
        if (std::strcmp(e.what(), "stof") != 0)
        {
            spdlog::error(e.what());
        }
        else
        {
            spdlog::error("could not read the provided command. must be in the form 'a + b'");
        }
        return false;
    }
}

int main(int ac, char** av)
{
    try
    {
        CLI::App app{fmt::format("{} version {}", "myproject", "0.1")};

        std::optional<std::string> message;
        app.add_option("-c,--command", message, "The command to compute (ex. 42 + 1337)");
        bool show_version = false;
        app.add_flag("--version", show_version, "Show version information");

        CLI11_PARSE(app, ac, av);

        if (show_version)
        {
            fmt::print("{}\n", "0.1");
            return EXIT_SUCCESS;
        }

        spdlog::info("Hello World! :)");

        if (message)
        {
            float a = 0;
            float b = 0;
            char c = 0;
            if (!extract_command(a, b, c, *message))
            {
                return EXIT_SUCCESS;
            }
            fmt::print("Computing '{0} {1:c} {2}':\n", a, c, b);
            fmt::print("Result: '{}'", myproject::foo(a, b, c));
        }
        else
        {
            fmt::print("No command provided :(\n");
        }
    }
    catch (const std::exception& e)
    {
        spdlog::error("Unhandled exception in main: {}", e.what());
    }
}
