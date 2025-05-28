#ifndef OBJECT_H
#define OBJECT_H

#include "color.h"
#include "triangle.h"

#include <span>
#include <vector>

namespace Rendering {

class Object {
  public:
    Object(std::vector<Triangle>&& triangles);

    // todo: maybe better provide iterator and sentinel
    std::span<const Triangle> getTriangles() const;
    const Vector3& getTranslation() const;
    const Matrix3x3& getRotation() const;

  private:
    std::vector<Triangle> triangles_;
    Vector3 translation_ = Vector3::Zero();
    Matrix3x3 rotation_ = Matrix3x3::Identity();
};

} // namespace Rendering

#endif // OBJECT_H
