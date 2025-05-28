#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "linalg.h"
#include "screen.h"
#include "world.h"

#include <cstdint>
#include <functional>
#include <span>

namespace Rendering {

class Renderer {
  public:
    Renderer();

    Screen render(const World& scene, const Camera& camera, Screen&& screen);

    void setNormalMode();
    void setWireframeMode();

  private:
    using DirectionalLights = std::span<const DirectionalLight>;
    using RenderF = std::function<void(Renderer&, const Triangle& triangle,
                                       DirectionalLights directional_lights,
                                       const AmbientLight& ambient_light,
                                       Screen& screen)>;

    void renderTriangle(const Object& object, const Triangle& triangle,
                        const Camera& camera, const World& world,
                        Screen& screen);

    void renderTriangleWireframe(const Triangle& triangle,
                                 DirectionalLights directional_lights,
                                 const AmbientLight& ambient_light,
                                 Screen& screen);

    void renderTriangleFilled(const Triangle& triangle_pr,
                              DirectionalLights directional_lights,
                              const AmbientLight& ambient_light,
                              Screen& screen);

    void drawPixelIfInTriangle(int x, int y, const Matrix2x3i& vertexes,
                               const Triangle& triangle,
                               DirectionalLights directional_lights,
                               const AmbientLight& ambient_light,
                               Screen& screen);

    RenderF render_triangle_;
    Array2 z_buffer_;
};

} // namespace Rendering

#endif // RENDERER_H
