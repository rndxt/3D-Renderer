#include "mouse_controller.h"

#include <cassert>

namespace App {

MouseController::MouseController(SceneModel* model)
    : model_(model),
      in_port_([this](const MouseAction& data) { handleMouseAction(data); }) {
    assert(model_ != nullptr);
}

Observer<MouseAction>* MouseController::port() {
    assert(model_ != nullptr);
    return &in_port_;
}

void MouseController::handleMouseAction(const MouseAction& action) {
    assert(model_ != nullptr);
    switch (action.wheel) {
    case sf::Mouse::Wheel::Vertical:
        handleVerticalWheelScroll(action);
        break;
    case sf::Mouse::Wheel::Horizontal:
        break;
    }
}

void MouseController::handleVerticalWheelScroll(const WheelScrolled& scroll) {
    if (scroll.delta > 0) {
        model_->moveCameraForward();
    } else if (scroll.delta < 0) {
        model_->moveCameraBackward();
    }
}

} // namespace App
