#include "camera.h"

#include <cassert>
#include <cmath>
#include <numbers>

namespace Rendering {

Camera::Camera(double aspectRatio, Near near, Far far, FieldOfViewAngle angle)
    : aspect_ratio_(aspectRatio),
      near_(near.Get()),
      far_(far.Get()),
      fov_(angle.Get()),
      projection_matrix_(MakeProjectionMatrix()) {
    assert(aspect_ratio_ > 0.0);
    assert(fov_ > 0.0 && fov_ < std::numbers::pi);
    assert(near_ > 0.0);
    assert(near_ < far_);
}

Matrix4x4 Camera::makeViewMatrix() const {
    return axis_transform_.matrix().inverse();
}

Matrix4x4 Camera::MakeProjectionMatrix() const {
    double a = aspect_ratio_;
    double n = near_;
    double f = far_;
    double e = 1.0 / tan(fov_ / 2);
    double l = -n / e;
    double r = n / e;
    double b = -a * n / e;
    double t = a * n / e;
    return Matrix4x4{{2 * n / (r - l), 0, (r + l) / (r - l), 0},
                     {0, 2 * n / (t - b), (t + b) / (t - b), 0},
                     {0, 0, -(f + n) / (f - n), -2 * n * f / (f - n)},
                     {0, 0, -1.0, 0}};
}

Camera::FrustumPlanes Camera::makeViewingFrustumPlanes() const {
    double e = 1.0 / std::tan(fov_ / 2.0);
    double a = aspect_ratio_;
    double e1 = e / std::hypot(e, 1);
    double e3 = 1.0 / std::hypot(e, 1);
    double e2 = e / std::hypot(e, a);
    double a1 = a / std::hypot(e, a);
    return {
        Vector4{0, 0, -1, -near_}, Vector4{0, 0, 1, far_},
        Vector4{e1, 0, -e3, 0},    Vector4{-e1, 0, -e3, 0},
        Vector4{0, e2, -a1, 0},    Vector4{0, -e2, -a1, 0},
    };
}

void Camera::move(Axis axis, double distance) {
    using enum Axis;
    switch (axis) {
    case X:
        axis_transform_.translate(distance * Vector3::UnitX());
        break;
    case Y:
        axis_transform_.translate(distance * Vector3::UnitY());
        break;
    case Z:
        axis_transform_.translate(distance * -Vector3::UnitZ());
        break;
    default:
        assert(false);
    }
}

void Camera::rotate(Axis axis, double angle) {
    using enum Axis;
    switch (axis) {
    case X:
        axis_transform_.rotate(AngleAxis(angle, Vector3::UnitX()));
        break;
    case Y:
        axis_transform_.rotate(AngleAxis(angle, Vector3::UnitY()));
        break;
    case Z:
        axis_transform_.rotate(AngleAxis(angle, Vector3::UnitZ()));
        break;
    default:
        assert(false);
    }
}

} // namespace Rendering
