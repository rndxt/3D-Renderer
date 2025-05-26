#include "renderer.h"

#include "linalg.h"
#include "object.h"
#include "screen.h"

#include <cassert>
#include <cmath>
#include <numeric>

using namespace Rendering;

namespace {

double distance(const Vector4& point, const Vector4& plane) {
    return plane.dot(point);
}

Vector4 intersectLineAndPlane(const Vector4& S, const Vector4& V,
                              const Vector4& plane) {
    double t = -plane.dot(S) / plane.dot(V);
    return S + t * V;
}

// todo:
// Join to template when fix ambigious call from Eigen expressions
Vector4 interpolate(const Vector4& a, const Vector4& b, double t) {
    return a - t * (b - a);
}

Vector3 interpolate3(const Vector3& a, const Vector3& b, double t) {
    return a - t * (b - a);
}

double getInterpolationCoeff(double x0, double x1, double x2) {
    return (x0 - x1) / (x2 - x1);
}

void DrawVerticalLine(Vector2i p1, Vector2i p2, const Color& color,
                      Screen& screen) {
    assert(p1.x() == p2.x());
    if (p1.y() > p2.y()) {
        std::swap(p1, p2);
    }

    int x = p1.x();
    for (int y = p1.y(); y <= p2.y(); ++y) {
        screen.setPixel(x, y, color);
    }
}

void DrawNonverticalLine(Vector2i p1, Vector2i p2, const Color& color,
                         Screen& screen) {
    assert(p1.x() < p2.x());
    Vector2i d = p2 - p1;
    if (p1.y() <= p2.y()) {
        double slope = static_cast<double>(d.y()) / d.x();
        if (slope <= 1.0) {
            for (int x = p1.x(); x <= p2.x(); ++x) {
                double alpha = getInterpolationCoeff(x, p1.x(), p2.x());
                int y
                    = static_cast<int>(std::lerp(p1.y(), p2.y(), alpha) + 0.5);
                screen.setPixel(x, static_cast<int>(y), color);
            }
        } else {
            for (int y = p1.y(); y <= p2.y(); ++y) {
                double alpha = getInterpolationCoeff(y, p1.y(), p2.y());
                int x
                    = static_cast<int>(std::lerp(p1.x(), p2.x(), alpha) + 0.5);
                screen.setPixel((int)x, static_cast<int>(y), color);
            }
        }
    } else {
        double slope = static_cast<double>(d.y()) / d.x();
        if (slope <= -1.0) {
            for (int y = p2.y(); y <= p1.y(); ++y) {
                double alpha = getInterpolationCoeff(y, p2.y(), p1.y());
                int x
                    = static_cast<int>(std::lerp(p2.x(), p1.x(), alpha) + 0.5);
                screen.setPixel(static_cast<int>(x), y, color);
            }
        } else {
            for (int x = p1.x(); x <= p2.x(); ++x) {
                double alpha = getInterpolationCoeff(x, p1.x(), p2.x());
                int y
                    = static_cast<int>(std::lerp(p1.y(), p2.y(), alpha) + 0.5);
                screen.setPixel(static_cast<int>(x), (int)y, color);
            }
        }
    }
}

void DrawLine(Vector2i p1, Vector2i p2, const Color& color, Screen& screen) {
    if (p1 == p2) {
        return;
    }

    if (p1.x() == p2.x()) {
        DrawVerticalLine(p1, p2, color, screen);
        return;
    }

    if (p1.x() > p2.x()) {
        std::swap(p1, p2);
    }

    DrawNonverticalLine(p1, p2, color, screen);
}

std::vector<TriangleProjected> ClipByPlane(const TriangleProjected& triangle_pr,
                                           const Vector4& planeVector) {
    constexpr size_t CountVertexes = 3;
    const auto& [vertexes, normal, color] = triangle_pr;
    size_t countVisible = 0;
    size_t countInvisible = 0;
    std::array<Index, CountVertexes> visible;
    std::array<Index, CountVertexes> invisible;
    for (Index i = 0; i < CountVertexes; ++i) {
        if (distance(vertexes.col(i), planeVector) < 0) {
            invisible[countInvisible++] = i;
        } else {
            visible[countVisible++] = i;
        }
    }

    if (countVisible == 3) {
        return {TriangleProjected{vertexes, normal, color}};
    }

    if (countVisible == 2) {
        std::vector clipped(2, TriangleProjected{vertexes, normal, color});
        Index A = invisible[0];
        Index B = visible[0];
        Index C = visible[1];
        Vector4 AB = intersectLineAndPlane(
            vertexes.col(B), vertexes.col(A) - vertexes.col(B), planeVector);
        Vector4 AC = intersectLineAndPlane(
            vertexes.col(C), vertexes.col(A) - vertexes.col(C), planeVector);
        clipped[0].vertexes.col(0) = vertexes.col(B);
        clipped[0].vertexes.col(1) = AB;
        clipped[0].vertexes.col(2) = AC;
        clipped[1].vertexes.col(0) = vertexes.col(C);
        clipped[1].vertexes.col(1) = vertexes.col(B);
        clipped[1].vertexes.col(2) = AC;
        return clipped;
    }

    if (countVisible == 1) {
        std::vector clipped(1, TriangleProjected{vertexes, normal, color});
        Index C = visible[0];
        Index A = invisible[0];
        Index B = invisible[1];
        Vector4 AC = intersectLineAndPlane(
            vertexes.col(C), vertexes.col(A) - vertexes.col(C), planeVector);
        Vector4 BC = intersectLineAndPlane(
            vertexes.col(C), vertexes.col(B) - vertexes.col(C), planeVector);
        clipped[0].vertexes.col(0) = vertexes.col(C);
        clipped[0].vertexes.col(1) = BC;
        clipped[0].vertexes.col(2) = AC;
        return clipped;
    }

    return {};
}

std::vector<TriangleProjected>
ClipByViewingFrustum(const TriangleProjected& triangle, const Camera& camera) {
    std::array planes = camera.makeViewingFrustumPlanes();
    std::vector result = {triangle};
    for (const auto& plane : planes) {
        std::vector<TriangleProjected> clipped;
        for (const auto& triangle : result) {
            std::vector tr = ClipByPlane(triangle, plane);
            clipped.insert(clipped.end(), tr.begin(), tr.end());
        }
        result = std::move(clipped);
    }
    return result;
}

Vector2i MapToPixels(const Vector3& point, const Screen& screen) {
    int w = screen.getWidth();
    int h = screen.getHeight();
    int x = static_cast<int>(w * std::midpoint(point.x(), 1.0));
    int y = static_cast<int>(h * std::midpoint(point.y(), 1.0));
    return {std::clamp(x, 0, w - 1), std::clamp(y, 0, h - 1)};
}

Matrix2x3i MapToPixels(const Triangle& triangle, const Screen& screen) {
    Matrix2x3i m;
    // clang-format off
    m << MapToPixels(triangle.vertexes.col(0), screen),
         MapToPixels(triangle.vertexes.col(1), screen),
         MapToPixels(triangle.vertexes.col(2), screen);
    // clang-format on
    return m;
}

Vector3 FromHClipSpaceToNormalizedDevice(const Vector4& point) {
    Vector3 v{point.x(), point.y(), point.z()};
    if (point.w() != 0.0) {
        v /= point.w();
    }
    return {std::clamp(v.x(), -1.0, 1.0), std::clamp(v.y(), -1.0, 1.0),
            std::clamp(v.z(), -1.0, 1.0)};
}

Matrix3x3 FromHClipSpaceToNormalizedDevice(const Matrix4x3& points) {
    Matrix3x3 vertexes;
    // fixme: ambigious call
    const Vector4& a = points.col(0);
    const Vector4& b = points.col(1);
    const Vector4& c = points.col(2);
    // clang-format off
    vertexes << FromHClipSpaceToNormalizedDevice(a),
                FromHClipSpaceToNormalizedDevice(b),
                FromHClipSpaceToNormalizedDevice(c);
    // clang-format on
    return vertexes;
}

Color AdjustAmbientLight(const Color& color, const AmbientLight& light) {
    return light.color * light.intensity * color;
}

Color AdjustDirectionalLight(const Color& base, const Vector3& normal,
                             std::span<const DirectionalLight> lights) {
    return std::accumulate(
        lights.begin(), lights.end(), Color::Black(),
        [&base, &normal](Color&& acc, const DirectionalLight& light) {
            const auto& [direction, color, intensity] = light;
            double diffuse = std::max(0.0, -direction.dot(normal));
            acc += diffuse * color * intensity * base;
            return acc;
        });
}

Color AdjustLight(const Color& color, const Vector3& normal,
                  std::span<const DirectionalLight> directional_lights,
                  const AmbientLight& ambient_light) {
    return AdjustAmbientLight(color, ambient_light)
           + AdjustDirectionalLight(color, normal, directional_lights);
}

double GetZCoordByArea(const Vector3 z, double w0, double w1, double w2,
                       double area) {

    Vector3 v{w0, w1, w2};
    v /= area;
    return v.dot(z);
}

Matrix3x3 GetGlobalCoordinates(const Object& object, const Triangle& triangle) {
    auto m = object.getRotation() * triangle.vertexes;
    Matrix3x3 r;
    for (int i = 0; i < 3; ++i) {
        r.col(i) = m.col(i) + object.getTranslation();
    }
    return m;
}

double GetSignedArea(double x0, double y0, double x1, double y1, double x,
                     double y) {
    return (y - y0) * (x1 - x0) - (x - x0) * (y1 - y0);
}

} // namespace

namespace Rendering {

Renderer::Renderer() {
    setWireframeMode();
}

void Renderer::setNormalMode() {
    render_triangle_ = &Renderer::renderTriangleFilled;
}

void Renderer::setWireframeMode() {
    render_triangle_ = &Renderer::renderTriangleWireframe;
}

Screen Renderer::render(const World& world, const Camera& camera,
                        Screen&& screen) {
    Color background = Color::Black();
    screen.fill(background);
    constexpr double kInfinity
        = std::numeric_limits<double>::infinity(); // todo: set 1
    z_buffer_.setConstant(screen.getWidth(), screen.getHeight(), kInfinity);
    for (const auto& object : world.getObjects()) {
        for (const auto& triangle : object.getTriangles()) {
            renderTriangle(object, triangle, camera, world, screen);
        }
    }
    return screen;
}

void Renderer::renderTriangle(const Object& object, const Triangle& triangle,
                              const Camera& camera, const World& world,
                              Screen& screen) {
    Matrix3x3 global_coordinates = GetGlobalCoordinates(object, triangle);
    Vector3 normal = makeNormal(global_coordinates);
    Matrix4x3 positions;
    positions << global_coordinates, RowVector3::Constant(1.0);
    // todo: copy of camera matrix on each iteration
    Matrix4x3 vertexes_in_camera_space = camera.makeViewMatrix() * positions;
    std::vector clipped_triangles = ClipByViewingFrustum(
        TriangleProjected{vertexes_in_camera_space, normal, triangle.color},
        camera);

    for (auto& clipped : clipped_triangles) {
        clipped.vertexes = camera.makeProjectionMatrix() * clipped.vertexes;
        Triangle tr = {FromHClipSpaceToNormalizedDevice(clipped.vertexes),
                       clipped.normal, clipped.color};
        render_triangle_(*this, tr, world.getDirectionalLights(),
                         world.getAmbientLight(), screen);
    }
}

void Renderer::renderTriangleWireframe(const Triangle& triangle,
                                       std::span<const DirectionalLight>,
                                       const AmbientLight&, Screen& screen) {
    Matrix2x3i vertexesOnScreen = MapToPixels(triangle, screen);
    const Vector2i& a = vertexesOnScreen.col(0);
    const Vector2i& b = vertexesOnScreen.col(1);
    const Vector2i& c = vertexesOnScreen.col(2);
    DrawLine(a, b, triangle.color, screen);
    DrawLine(b, c, triangle.color, screen);
    DrawLine(c, a, triangle.color, screen);
}

void Renderer::renderTriangleFilled(
    const Triangle& triangle,
    std::span<const DirectionalLight> directional_lights,
    const AmbientLight& ambient_light, Screen& screen) {
    Matrix2x3i vertexesOnScreen = MapToPixels(triangle, screen);
    const auto& a = vertexesOnScreen.col(0);
    const auto& b = vertexesOnScreen.col(1);
    const auto& c = vertexesOnScreen.col(2);
    auto [min_x, max_x] = std::ranges::minmax({a.x(), b.x(), c.x()});
    auto [min_y, max_y] = std::ranges::minmax({a.y(), b.y(), c.y()});
    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            drawPixelIfInTriangle(x, y, vertexesOnScreen, triangle,
                                  directional_lights, ambient_light, screen);
        }
    }
}

void Renderer::drawPixelIfInTriangle(
    int x, int y, const Matrix2x3i& vertexes, const Triangle& triangle,
    std::span<const DirectionalLight> directional_lights,
    const AmbientLight& ambient_light, Screen& screen) {
    const auto& a = vertexes.col(0);
    const auto& b = vertexes.col(1);
    const auto& c = vertexes.col(2);
    const double area = GetSignedArea(a.x(), a.y(), b.x(), b.y(), c.x(), c.y());
    double w0 = GetSignedArea(b.x(), b.y(), c.x(), c.y(), x, y);
    double w1 = GetSignedArea(c.x(), c.y(), a.x(), a.y(), x, y);
    double w2 = GetSignedArea(a.x(), a.y(), b.x(), b.y(), x, y);
    if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
        double z = GetZCoordByArea(triangle.vertexes.row(2), w0, w1, w2, area);
        if (x < 0 || x >= screen.getWidth()) {
            return;
        }

        if (y < 0 || y >= screen.getHeight()) {
            return;
        }
        if (z < z_buffer_(x, y)) {
            z_buffer_(x, y) = z;
            Color adjustedColor
                = AdjustLight(triangle.color, triangle.normal,
                              directional_lights, ambient_light);
            screen.setPixel(x, y, adjustedColor);
        }
    }
}

} // namespace Rendering
