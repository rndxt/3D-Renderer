#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "keyboard_action.h"
#include "mouse_action.h"
#include "observer.h"
#include "renderer.h" // todo: only for Width / Height types

#include <SFML/Graphics/RenderWindow.hpp>

namespace App {

class EventManager {
  public:
    using Width = Rendering::Width;
    using Height = Rendering::Height;
    using WindowSize = sf::Vector2u;

    // todo:
    // maybe better construct this class from sf::RenderWindows&&
    explicit EventManager(WindowSize size, const std::string& title);

    sf::RenderWindow* window();

    void manage();

    void subscribe(Observer<KeyboardAction>* observer);
    void subscribe(Observer<MouseAction>* observer);

  private:
    using KeyPressedEvent = sf::Event::KeyPressed;
    using WindowClosedEvent = sf::Event::Closed;
    using MouseWheelScrolledEvent = sf::Event::MouseWheelScrolled;

    void handleEvent(const KeyPressedEvent& event);
    void handleEvent(const WindowClosedEvent&);
    void handleEvent(const MouseWheelScrolledEvent& event);
    void handleEvent(const auto&);

    ObservableData<KeyboardAction> keyboard_port_;
    ObservableData<MouseAction> mouse_port_;
    sf::RenderWindow window_;
};

} // namespace App

#endif // EVENT_MANAGER_H
