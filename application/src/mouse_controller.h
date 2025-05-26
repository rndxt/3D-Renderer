#ifndef MOUSE_CONTROLLER_H
#define MOUSE_CONTROLLER_H

#include "mouse_action.h"
#include "observer.h"
#include "scene_model.h"

namespace App {

class MouseController {
  public:
    explicit MouseController(SceneModel* model);

    Observer<MouseAction>* port();

  private:
    using WheelScrolled = sf::Event::MouseWheelScrolled;

    void handleMouseAction(const MouseAction& action);
    void handleVerticalWheelScroll(const WheelScrolled& scroll);

    ColdObserver<MouseAction> in_port_;
    SceneModel* model_;
};

} // namespace App

#endif // MOUSE_CONTROLLER_H
