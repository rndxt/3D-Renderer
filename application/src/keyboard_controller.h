#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include "keyboard_action.h"
#include "observer.h"
#include "scene_model.h"

namespace App {

class KeyboardController {
  public:
    explicit KeyboardController(SceneModel* model);

    Observer<KeyboardAction>* port();

  private:
    using KeyPressedAction = sf::Event::KeyPressed;

    void handleKeyboardAction(const KeyboardAction& action);
    void handleKeyPressedAction(const KeyPressedAction& action);

    ColdObserver<KeyboardAction> in_port_;
    SceneModel* model_;
};

} // namespace App

#endif // KEYBOARD_CONTROLLER_H
