#ifndef OBJECT_PARSER_H
#define OBJECT_PARSER_H

#include "object.h"

#include <filesystem>
#include <variant>

namespace App {

template <typename T, typename E>
using ValueOrError = std::variant<std::monostate, T, E>;

constexpr std::size_t kValueIndex = 1;
constexpr std::size_t kErrorIndex = 2;

enum class ParsingError {
    FailedToOpenFile,
    EmptyObject,
    ZeroIndex,
    IndexOutOfBounds
};

using ObjectOrError = ValueOrError<Rendering::Object, ParsingError>;

ObjectOrError ParseObjectFromFile(const std::filesystem::path& path);

} // namespace App

#endif // OBJECT_PARSER_H
