#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

int main(int ac, char** av)
{
  try {
    CLI::App app{ fmt::format("{} version {}", "myproject", "0.1") };

    std::optional<std::string> message;
    app.add_option("-m,--message", message, "A message to print back out");
    bool show_version = false;
    app.add_flag("--version", show_version, "Show version information");

    CLI11_PARSE(app, ac, av);

    if (show_version) {
      fmt::print("{}\n", "0.1");
      return EXIT_SUCCESS;
    }

    spdlog::info("Hellow World! :)");
    
    if (message) {
      fmt::print("Message: '{}'\n", *message);
    } else {
      fmt::print("No Message Provided :(\n");
    }
  } catch (const std::exception &e) {
    spdlog::error("Unhandled exception in main: {}", e.what());
  }
}
