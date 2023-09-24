#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP
#include <cmath>
#include <vector>

class Vector3D {
public:
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;

  Vector3D() = default;
  double norm_squared() const;
  double norm() const;
  double distance_to(const Vector3D &other) const;
};

double distance(const Vector3D &r_i, const Vector3D &r_j);

#endif /* VECTOR3D_HPP */
