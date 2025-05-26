#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "color.h"
#include "linalg.h"

namespace Rendering {

struct DirectionalLight {
    Vector3 direction;
    Color color;
    double intensity;
};

} // namespace Rendering

#endif // DIRECTIONAL_LIGHT_H
