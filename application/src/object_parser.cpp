#include "object_parser.h"

#include "linalg.h"

#include <array>
#include <fstream>
#include <span>
#include <type_traits>
#include <vector>

using namespace App;

using Rendering::Color;
using Rendering::makeNormal;
using Rendering::Matrix3x3;
using Rendering::Object;
using Rendering::Triangle;
using Rendering::Vector3;

using Vertexes = std::vector<Vector3>;
using VertexesOrError = ValueOrError<Vertexes, ParsingError>;

using Faces = std::vector<Triangle>;
using FacesOrError = ValueOrError<Faces, ParsingError>;

namespace {

bool IsVertexNext(char c) {
    return c == 'v';
}

bool IsFaceNext(char c) {
    return c == 'f';
}

VertexesOrError ParseVertexes(std::istream& is) {
    std::vector<Vector3> vertexes;
    int i = 0;
    while (!is.eof()) {
        // todo: handle windows and mac new lines
        while (is.peek() == '\n') {
            (void)is.get();
        }

        if (!IsVertexNext(is.peek())) {
            break;
        }

        (void)is.get();
        double x, y, z;
        is >> x >> y >> z;
        vertexes.emplace_back(x, y, z);
    }

    return vertexes;
}

FacesOrError ParseFaces(std::istream& is, std::span<const Vector3> vertexes) {
    if (vertexes.empty()) {
        return ParsingError::EmptyObject;
    }

    std::vector<Triangle> triangles;
    while (!is.eof()) {
        while (is.peek() == '\n') {
            (void)is.get();
        }

        if (!IsFaceNext(is.peek())) {
            break;
        }

        (void)is.get();
        constexpr size_t kCountIndexes = 3;
        std::array<size_t, kCountIndexes> indexes = {0};
        for (size_t i = 0; i < indexes.size(); ++i) {
            is >> indexes[i];
            // index in .obj format starts with 1
            if (indexes[i] == 0) {
                return ParsingError::ZeroIndex;
            }

            indexes[i] -= 1;

            if (indexes[i] >= vertexes.size()) {
                return ParsingError::IndexOutOfBounds;
            }
        }

        Matrix3x3 triangleVertexes;
        for (size_t i = 0; i < indexes.size(); ++i) {
            size_t index = indexes[i];
            triangleVertexes.col(i) = vertexes[index];
        }

        Vector3 normal = makeNormal(triangleVertexes);
        triangles.emplace_back(std::move(triangleVertexes), std::move(normal),
                               Color::White());
    }
    return triangles;
}

} // namespace

namespace App {

ObjectOrError ParseObjectFromFile(const std::filesystem::path& path) {
    std::ifstream fstream(path);
    if (!fstream.is_open()) {
        return ParsingError::FailedToOpenFile;
    }

    VertexesOrError vertexesOrError = ParseVertexes(fstream);
    if (vertexesOrError.index() == kErrorIndex) {
        return std::get<kErrorIndex>(vertexesOrError);
    }

    Vertexes& vertexes = std::get<kValueIndex>(vertexesOrError);
    FacesOrError trianglesOrError = ParseFaces(fstream, vertexes);
    if (trianglesOrError.index() == kErrorIndex) {
        return std::get<kErrorIndex>(trianglesOrError);
    }

    Faces&& triangles = std::get<kValueIndex>(std::move(trianglesOrError));
    return Object(std::move(triangles));
}

} // namespace App
