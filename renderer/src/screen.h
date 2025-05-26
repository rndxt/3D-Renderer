#ifndef SCREEN_H
#define SCREEN_H

#include "color.h"

#include <cstdint>
#include <span>
#include <vector>

namespace Rendering {

enum Width : int;
enum Height : int;

class Screen {
  public:
    Screen(Width width, Height height);

    Width getWidth() const;
    Height getHeight() const;
    int getPixelsCount() const;
    double getAspect() const;

    std::span<const std::uint8_t> getPixels() const;
    void setPixel(int x, int y, Color color);

    void fill(const Color& color);

  private:
    static constexpr size_t kRGBaColorInBytes = 4;

    size_t getIndex(int x, int y) const;

    Width width_;
    std::vector<std::uint8_t> pixels_;
};

} // namespace Rendering

#endif // SCREEN_H
