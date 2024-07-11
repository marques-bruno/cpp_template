#include <spdlog/spdlog.h>
#include <CLI/CLI.hpp>
#include <cstdlib>
#include <cstring>
#include <optional>
#include <string>
#include <sstream>
#include <exception>
#include <fmt/core.h>
#include <stdexcept>

#include "myproject/myproject.h"

// cmake-generated config file containing version, git SHA etc.
#include "details/config.hpp"

/// extract the components of the command to execute from the string message
bool extract_command(float& a, float& b, char& op, const std::string& message)
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
            throw std::invalid_argument(
                (std::string("Supporting only single-character operators: ") + str).c_str());
        }
        op = str[0];
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

/// Our main entry point.
///
/// Parses command line, extract command & run foo()
int main(int ac, char** av)
{
    try
    {
        CLI::App app{fmt::format("{} version {}", myproject::details::project_name,
                                 myproject::details::project_version)};

        std::optional<std::string> message;
        app.add_option("-c,--command", message, "The command to compute (ex. 42 + 1337)");
        bool show_version = false;
        app.add_flag("--version", show_version, "Show version information");

        CLI11_PARSE(app, ac, av);

        if (show_version)
        {
            fmt::print("{}\n", myproject::details::project_version);
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
