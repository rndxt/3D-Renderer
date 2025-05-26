#include "application.h"

#include "command_line.h"
#include "object_parser.h"

#include <cassert>

using App::SceneModel;
using Rendering::AmbientLight;
using Rendering::Color;
using Rendering::DirectionalLight;
using Rendering::Height;
using Rendering::Vector3;
using Rendering::Width;

namespace {

void InitializeDefaultLights(SceneModel& model) {
    constexpr Color kDefaultAmbientLightColor = 0x1a1a1a;
    constexpr Color kDefaultDirectionalLightColor = 0xffe6b2;

    // todo: magic numbers
    model.addDirectionalLight(DirectionalLight{
        Vector3::Constant(-1.0), kDefaultDirectionalLightColor, 0.8});
    model.setAmbientLight(AmbientLight{kDefaultAmbientLightColor, 1.0});
}

} // namespace

namespace App {

Application::Application(int argc, char* argv[])
    : Application(kWindowSize, kDefaultTitle) {
    std::optional options = Cl::ParseCommandLineOptions(argc, argv);
    // todo:
    // I don't know how handle parsing errors in this scope.
    // Maybe better create global cli options variable than
    // throws exceptions. Leave this as it is for review.
    assert(options.has_value());
    auto objectOrError = ParseObjectFromFile(options->objectPath);
    // todo:
    // Same as above.
    assert(objectOrError.index() == 1);

    model_.addObject(std::get<1>(std::move(objectOrError)));
    InitializeDefaultLights(model_);

    model_.subscribe(view_.port());
    manager_.subscribe(keyboard_controller_.port());
    manager_.subscribe(mouse_controller_.port());
}

Application::Application(WindowSize size, const std::string& title)
    : model_(Width(size.x), Height(size.y)),
      manager_(size, title),
      view_(manager_.window()),
      keyboard_controller_(&model_),
      mouse_controller_(&model_) {
}

void Application::run() {
    manager_.manage();
}

} // namespace App
