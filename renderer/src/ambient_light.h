#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "color.h"

namespace Rendering {

struct AmbientLight {
    Color color;
    double intensity;
};

} // namespace Rendering

#endif // AMBIENT_LIGHT_H
