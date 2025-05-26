#include "color.h"

#include <algorithm>

namespace Rendering {

Color::Color(double r, double g, double b) : r_(r), g_(g), b_(b) {
}

std::uint8_t Color::red() const {
    return static_cast<std::uint8_t>(r_ * kMaxComponentValue);
}

std::uint8_t Color::green() const {
    return static_cast<std::uint8_t>(g_ * kMaxComponentValue);
}

std::uint8_t Color::blue() const {
    return static_cast<std::uint8_t>(b_ * kMaxComponentValue);
}

std::uint8_t Color::alpha() const {
    return 0xff;
}

Color Color::operator+(const Color& other) const {
    Color result = *this;
    result += other;
    return result;
}

Color Color::operator*(const Color& other) const {
    Color result = *this;
    result *= other;
    return result;
}

Color Color::operator*(double scalar) const {
    return Color(std::clamp(r_ * scalar, 0.0, 1.0),
                 std::clamp(g_ * scalar, 0.0, 1.0),
                 std::clamp(b_ * scalar, 0.0, 1.0));
}

Color& Color::operator+=(const Color& other) {
    r_ = std::clamp(r_ + other.r_, 0.0, 1.0);
    g_ = std::clamp(g_ + other.g_, 0.0, 1.0);
    b_ = std::clamp(b_ + other.b_, 0.0, 1.0);
    return *this;
}

Color& Color::operator*=(const Color& other) {
    r_ = std::clamp(r_ * other.r_, 0.0, 1.0);
    g_ = std::clamp(g_ * other.g_, 0.0, 1.0);
    b_ = std::clamp(b_ * other.b_, 0.0, 1.0);
    return *this;
}

Color& Color::operator*=(double scalar) {
    r_ = std::clamp(r_ * scalar, 0.0, 1.0);
    g_ = std::clamp(g_ * scalar, 0.0, 1.0);
    b_ = std::clamp(b_ * scalar, 0.0, 1.0);
    return *this;
}

Color Color::Black() {
    return Color{0x000000};
}

Color Color::White() {
    return Color{0xffffff};
}

Color operator*(double scalar, const Color& color) {
    return color * scalar;
}

} // namespace Rendering
