#include "command_line.h"

namespace App {
namespace Cl {

// todo: handle errors: "Too few arguments"
std::optional<Options> ParseCommandLineOptions(int argc, char* argv[]) {
    constexpr int objectPathIndex = 1;
    if (argc == 1) {
        return std::nullopt;
    }

    return Options{.objectPath = argv[objectPathIndex]};
}

} // namespace Cl
} // namespace App
