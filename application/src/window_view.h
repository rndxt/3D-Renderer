#ifndef WINDOW_VIEW_H
#define WINDOW_VIEW_H

#include "draw_data.h"
#include "observer.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace App {

class WindowView {
  public:
    explicit WindowView(sf::RenderWindow* window);

    ObserverByValue<DrawData>* port();

  private:
    void drawPixels(DrawData pixels);

    HotObserverByValue<DrawData> in_port_;
    sf::RenderWindow* window_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};

} // namespace App

#endif // WINDOW_VIEW_H
