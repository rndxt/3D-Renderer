#ifndef APPLICATION_H
#define APPLICATION_H

#include "event_manager.h"
#include "keyboard_controller.h"
#include "mouse_controller.h"
#include "scene_model.h"
#include "window_view.h"

#include <string>

namespace App {

class Application {
  public:
    explicit Application(int argc, char* argv[]);

    void run();

  private:
    using WindowSize = sf::Vector2u;
    static constexpr WindowSize kWindowSize{1280, 720};

    Application(WindowSize size, const std::string& title);

    // todo: give normal names
    SceneModel model_;
    EventManager manager_;
    WindowView view_;
    KeyboardController keyboard_controller_;
    MouseController mouse_controller_;
};

} // namespace App

#endif // APPLICATION_H
