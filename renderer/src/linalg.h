#ifndef LINALG_H
#define LINALG_H

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace Rendering {

using Index = Eigen::Index;
using Vector2i = Eigen::Vector2i;
using Matrix2x3i = Eigen::Matrix<int, 2, 3>;
using RowVector3 = Eigen::RowVector3d;
using Vector3 = Eigen::Vector3d;
using Vector4 = Eigen::Vector4d;
using Matrix3x3 = Eigen::Matrix3d;
using Matrix4x4 = Eigen::Matrix4d;
using Matrix4x3 = Eigen::Matrix<double, 4, 3>;
using Array2 = Eigen::ArrayXXd;

using AngleAxis = Eigen::AngleAxisd;
using Affine3 = Eigen::Affine3d;

inline Vector3 makeNormal(const Vector3& a, const Vector3& b,
                          const Vector3& c) {
    return (b - a).cross(c - a).normalized();
}

inline Vector3 makeNormal(const Matrix3x3& m) {
    return makeNormal(m.col(0), m.col(1), m.col(2));
}

} // namespace Rendering

#endif // LINALG_H
