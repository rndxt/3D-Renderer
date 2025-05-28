#include "object.h"

namespace Rendering {

Object::Object(std::vector<Triangle>&& triangles)
    : triangles_(std::move(triangles)) {
}

std::span<const Triangle> Object::getTriangles() const {
    return triangles_;
}

const Vector3& Object::getTranslation() const {
    return translation_;
}

const Matrix3x3& Object::getRotation() const {
    return rotation_;
}

} // namespace Rendering
