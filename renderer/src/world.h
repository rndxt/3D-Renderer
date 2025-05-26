#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "light.h"
#include "object.h"

#include <span>
#include <vector>

namespace Rendering {

class World {
  public:
    void addObject(Object&& object);
    void setAmbientLight(AmbientLight&& light);
    void addDirectionalLight(DirectionalLight&& light);

    // todo: maybe better provide iterator and sentinel
    std::span<const Object> GetObjects() const;
    std::span<const DirectionalLight> GetDirectionalLights() const;
    const AmbientLight& GetAmbientLight() const;

  private:
    std::vector<Object> objects_;
    std::vector<DirectionalLight> directional_lights_;
    AmbientLight ambient_light_{Color::Black(), 0.0};
};

} // namespace Rendering

#endif // WORLD_H
