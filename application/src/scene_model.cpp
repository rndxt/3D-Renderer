#include "scene_model.h"

#include <cassert>

using Rendering::Axis;

namespace App {

SceneModel::SceneModel(Width width, Height height)
    : screen_(width, height),
      camera_(screen_.getAspect(), kDefaultNear, kDefaultFar,
              kDefaultFieldOfViewAngle),
      model_port_([this]() { return screen_.getPixels(); }) {
    render();
}

void SceneModel::addObject(Object&& object) {
    world_.addObject(std::move(object));
    renderAndNotify();
}

void SceneModel::setAmbientLight(AmbientLight&& light) {
    world_.setAmbientLight(std::move(light));
    renderAndNotify();
}

void SceneModel::addDirectionalLight(DirectionalLight&& light) {
    world_.addDirectionalLight(std::move(light));
    renderAndNotify();
}

void SceneModel::setNormalRenderingMode() {
    renderer_.setNormalMode();
    renderAndNotify();
}

void SceneModel::setWireframeRenderingMode() {
    renderer_.setWireframeMode();
    renderAndNotify();
}

void SceneModel::moveCameraForward() {
    camera_.move(Axis::Z, kDefaultMove);
    renderAndNotify();
}

void SceneModel::moveCameraBackward() {
    camera_.move(Axis::Z, -kDefaultMove);
    renderAndNotify();
}

void SceneModel::moveCameraLeft() {
    camera_.move(Axis::X, -kDefaultMove);
    renderAndNotify();
}

void SceneModel::moveCameraRight() {
    camera_.move(Axis::X, kDefaultMove);
    renderAndNotify();
}

void SceneModel::rotateUpCamera() {
    camera_.rotate(Axis::X, kDefaultRotation);
    renderAndNotify();
}

void SceneModel::rotateDownCamera() {
    camera_.rotate(Axis::X, -kDefaultRotation);
    renderAndNotify();
}

void SceneModel::rotateLeftCamera() {
    camera_.rotate(Axis::Y, kDefaultRotation);
    renderAndNotify();
}

void SceneModel::rotateRightCamera() {
    camera_.rotate(Axis::Y, -kDefaultRotation);
    renderAndNotify();
}

void SceneModel::render() {
    screen_ = renderer_.render(world_, camera_, std::move(screen_));
}

void SceneModel::renderAndNotify() {
    render();
    model_port_.notify();
}

void SceneModel::subscribe(ObserverByValue<DrawData>* observer) {
    assert(observer != nullptr);
    model_port_.subscribe(observer);
}

} // namespace App
