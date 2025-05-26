#ifndef CAMERA_HELPERS_H
#define CAMERA_HELPERS_H

#include <numbers>

namespace Rendering {

class FieldOfViewAngle {
  public:
    constexpr explicit FieldOfViewAngle(double value);
    constexpr double Get() const;

  private:
    double value_;
};

class Near {
  public:
    constexpr explicit Near(double value);
    constexpr double Get() const;

  private:
    double value_;
};

class Far {
  public:
    constexpr explicit Far(double value);
    constexpr double Get() const;

  private:
    double value_;
};

constexpr FieldOfViewAngle::FieldOfViewAngle(double value)
    : value_(value * std::numbers::pi / 180.0) {
}

constexpr double FieldOfViewAngle::Get() const {
    return value_;
}

constexpr Near::Near(double value) : value_(value) {
}

constexpr double Near::Get() const {
    return value_;
}

constexpr Far::Far(double value) : value_(value) {
}

constexpr double Far::Get() const {
    return value_;
}

} // namespace Rendering

#endif // CAMERA_HELPERS_H
