#ifndef CAMERA_H
#define CAMERA_H

#include "camera_helpers.h"
#include "linalg.h"
#include "screen.h"

namespace Rendering {

enum class Axis { X, Y, Z };

class Camera {
  public:
    static constexpr size_t kCountFrustumPlanes = 6;
    using FrustumPlanes = std::array<Vector4, kCountFrustumPlanes>;

    Camera(double aspect, Near near, Far far, FieldOfViewAngle fov);

    Matrix4x4 makeViewMatrix() const;
    Matrix4x4 makeProjectionMatrix() const;

    FrustumPlanes makeViewingFrustumPlanes() const;

    void move(Axis axis, double distance);
    void rotate(Axis axis, double angle);

  private:
    double aspect_ratio_;
    double near_;
    double far_;
    double fov_;
    Matrix4x4 projection_matrix_;
    Affine3 axis_transform_ = Affine3::Identity();
};

} // namespace Rendering

#endif // CAMERA_H
