#include "world.h"

namespace Rendering {

void World::addObject(Object&& object) {
    objects_.push_back(std::move(object));
}

void World::setAmbientLight(AmbientLight&& light) {
    ambient_light_ = std::move(light);
}

void World::addDirectionalLight(DirectionalLight&& light) {
    directional_lights_.push_back(std::move(light));
}

std::span<const Object> World::GetObjects() const {
    return objects_;
}

std::span<const DirectionalLight> World::GetDirectionalLights() const {
    return directional_lights_;
}

const AmbientLight& World::GetAmbientLight() const {
    return ambient_light_;
}

} // namespace Rendering
