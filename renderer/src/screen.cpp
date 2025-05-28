#include "screen.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <limits>

namespace Rendering {

Screen::Screen(Width width, Height height)
    : width_(width),
      pixels_(kRGBaColorInBytes * width * height) {
}

Width Screen::getWidth() const {
    return width_;
}

Height Screen::getHeight() const {
    return static_cast<Height>(getPixelsCount() / getWidth());
}

int Screen::getPixelsCount() const {
    return static_cast<int>(pixels_.size() / kRGBaColorInBytes);
}

double Screen::getAspect() const {
    double h = getHeight();
    double w = getWidth();
    return h / w;
}

std::span<const std::uint8_t> Screen::getPixels() const {
    return pixels_;
}

void Screen::setPixel(int x, int y, Color color) {
    size_t index = getIndex(x, y);
    pixels_[index] = color.red();
    pixels_[index + 1] = color.green();
    pixels_[index + 2] = color.blue();
    pixels_[index + 3] = color.alpha();
}

void Screen::fill(const Color& color) {
    for (size_t i = 0; i < pixels_.size(); i += 4) {
        pixels_[i] = color.red();
        pixels_[i + 1] = color.green();
        pixels_[i + 2] = color.blue();
        pixels_[i + 3] = color.alpha();
    }
}

size_t Screen::getIndex(int x, int y) const {
    assert(0 <= x && x < getWidth());
    assert(0 <= y && y < getHeight());
    // On computer screen axis Y points
    // from up to down
    return 4 * ((getHeight() - y - 1) * getWidth() + x);
}

} // namespace Rendering
