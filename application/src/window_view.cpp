#include "window_view.h"

#include <cassert>

namespace App {

WindowView::WindowView(sf::RenderWindow* window)
    : window_(window),
      texture_(window_->getSize()),
      sprite_(texture_),
      in_port_([this](DrawData pixels) { drawPixels(pixels); }) {
    assert(window_ != nullptr);
}

ObserverByValue<DrawData>* WindowView::port() {
    assert(window_ != nullptr);
    return &in_port_;
}

void WindowView::drawPixels(DrawData pixels) {
    assert(window_ != nullptr);
    // todo:
    // update() copies data to GPU memory, but
    // I don't know another way to draw pixels to screen in SFML
    texture_.update(pixels.data());
    window_->clear();
    window_->draw(sprite_);
    window_->display();
}

} // namespace App
