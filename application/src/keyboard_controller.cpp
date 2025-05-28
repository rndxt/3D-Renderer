#include "keyboard_controller.h"

#include <cassert>

namespace App {

KeyboardController::KeyboardController(SceneModel* model)
    : model_(model),
      in_port_(
          [this](const KeyboardAction& data) { handleKeyboardAction(data); }) {
    assert(model_ != nullptr);
}

Observer<KeyboardAction>* KeyboardController::port() {
    assert(model_ != nullptr);
    return &in_port_;
}

void KeyboardController::handleKeyboardAction(const KeyboardAction& action) {
    handleKeyPressedAction(action);
}

void KeyboardController::handleKeyPressedAction(
    const KeyPressedAction& action) {
    using enum sf::Keyboard::Scancode;

    assert(model_ != nullptr);
    switch (action.scancode) {
    case Up:
        model_->rotateUpCamera();
        break;
    case Down:
        model_->rotateDownCamera();
        break;
    case Left:
        model_->rotateLeftCamera();
        break;
    case Right:
        model_->rotateRightCamera();
        break;
    case W:
        model_->moveCameraForward();
        break;
    case S:
        model_->moveCameraBackward();
        break;
    case A:
        model_->moveCameraLeft();
        break;
    case D:
        model_->moveCameraRight();
        break;
    case Num1:
        model_->setNormalRenderingMode();
        break;
    case Num2:
        model_->setWireframeRenderingMode();
        break;
    default:
        break;
    }
}

} // namespace App
