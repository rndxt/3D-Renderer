#include "event_manager.h"

#include "icon.h"

#include <cassert>

namespace App {

EventManager::EventManager(WindowSize size, const std::string& title)
    : window_(sf::VideoMode(size), title,
              sf::Style::Titlebar | sf::Style::Close) {
    window_.setIcon(kIconSize, kDefaultIconPixels.data());
}

sf::RenderWindow* EventManager::window() {
    return &window_;
}

void EventManager::manage() {
    while (window_.isOpen()) {
        window_.handleEvents([this](const auto& event) { handleEvent(event); });
    }
}

void EventManager::subscribe(Observer<KeyboardAction>* observer) {
    assert(observer != nullptr);
    keyboard_port_.subscribe(observer);
}

void EventManager::subscribe(Observer<MouseAction>* observer) {
    assert(observer != nullptr);
    mouse_port_.subscribe(observer);
}

void EventManager::handleEvent(const KeyPressedEvent& event) {
    keyboard_port_.set(event);
}

void EventManager::handleEvent(const WindowClosedEvent& /* event */) {
    window_.close();
}

void EventManager::handleEvent(const MouseWheelScrolledEvent& event) {
    mouse_port_.set(event);
}

void EventManager::handleEvent(const auto& /* event */) {
}

} // namespace App
