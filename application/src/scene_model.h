#ifndef SCENE_MODEL_H
#define SCENE_MODEL_H

#include "draw_data.h"
#include "observer.h"
#include "renderer.h"

#include <numbers>

namespace App {

class SceneModel {
  public:
    using Width = Rendering::Width;
    using Height = Rendering::Height;
    using Object = Rendering::Object;
    using AmbientLight = Rendering::AmbientLight;
    using DirectionalLight = Rendering::DirectionalLight;

    explicit SceneModel(Width width, Height height);

    void addObject(Object&& object);
    void setAmbientLight(AmbientLight&& light);
    void addDirectionalLight(DirectionalLight&& light);
    void setNormalRenderingMode();
    void setWireframeRenderingMode();

    void moveCameraForward();
    void moveCameraBackward();
    void moveCameraLeft();
    void moveCameraRight();

    void rotateUpCamera();
    void rotateDownCamera();
    void rotateLeftCamera();
    void rotateRightCamera();

    void subscribe(ObserverByValue<DrawData>* observer);

  private:
    using Renderer = Rendering::Renderer;
    using Camera = Rendering::Camera;
    using Near = Rendering::Near;
    using Far = Rendering::Far;
    using FieldOfViewAngle = Rendering::FieldOfViewAngle;
    using Screen = Rendering::Screen;
    using World = Rendering::World;

    static constexpr double kDefaultRotation = std::numbers::pi / 36;
    static constexpr double kDefaultMove = 0.1;
    static constexpr Near kDefaultNear{0.1};
    static constexpr Far kDefaultFar{10.0};
    static constexpr FieldOfViewAngle kDefaultFieldOfViewAngle{60.0};

    void render();
    void renderAndNotify();

    // Observable std::span object is lightweight
    // view on continuous array, so I prefer to
    // pass it by value.
    ObservableByValue<DrawData> model_port_;
    Renderer renderer_;
    World world_;
    Screen screen_;
    Camera camera_;
};

} // namespace App

#endif // SCENE_MODEL_H
