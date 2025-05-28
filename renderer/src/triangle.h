#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "color.h"
#include "linalg.h"

namespace Rendering {

struct Triangle {
    Matrix3x3 vertexes;
    Vector3 normal;
    Color color;
};

struct TriangleProjected {
    Matrix4x3 vertexes;
    Vector3 normal;
    Color color;
};

} // namespace Rendering

#endif // TRIANGLE_H
