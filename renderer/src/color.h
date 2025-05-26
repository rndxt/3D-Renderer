#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace Rendering {

// Eigen::Vector4d not constexpr for now,
// so I decided to work with doubles.
class Color {
  public:
    constexpr Color(std::uint32_t hex);

    std::uint8_t red() const;
    std::uint8_t green() const;
    std::uint8_t blue() const;
    std::uint8_t alpha() const;

    Color operator+(const Color& other) const;
    Color operator*(const Color& other) const;

    Color& operator+=(const Color& other);
    Color& operator*=(const Color& other);

    Color operator*(double scalar) const;
    Color& operator*=(double scalar);

    static Color Black();
    static Color White();

  private:
    Color(double r, double g, double b);

    static constexpr double kMaxComponentValue = 255.0;
    static constexpr uint32_t kRedShift = 16;
    static constexpr uint32_t kGreenShift = 8;
    static constexpr uint32_t kComponentMask = 0xff;

    constexpr double getRedComponent(std::uint32_t hex);
    constexpr double getGreenComponent(std::uint32_t hex);
    constexpr double getBlueComponent(std::uint32_t hex);

    double r_;
    double g_;
    double b_;
};

Color operator*(double scalar, const Color& color);

constexpr Color::Color(uint32_t hex)
    : r_(getRedComponent(hex)),
      g_(getGreenComponent(hex)),
      b_(getBlueComponent(hex)) {
}

constexpr double Color::getRedComponent(std::uint32_t hex) {
    return ((hex >> kRedShift) & kComponentMask) / kMaxComponentValue;
}
constexpr double Color::getGreenComponent(std::uint32_t hex) {
    return ((hex >> kGreenShift) & kComponentMask) / kMaxComponentValue;
}
constexpr double Color::getBlueComponent(std::uint32_t hex) {
    return (hex & kComponentMask) / kMaxComponentValue;
}

} // namespace Rendering

#endif // COLOR_H
