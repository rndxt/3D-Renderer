#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <filesystem>
#include <optional>

namespace App {
namespace Cl {

struct Options {
    std::filesystem::path objectPath;
};

std::optional<Options> ParseCommandLineOptions(int argc, char* argv[]);

} // namespace Cl
} // namespace App

#endif // COMMAND_LINE_H
