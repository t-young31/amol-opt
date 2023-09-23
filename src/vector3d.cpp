#include "vector3d.hpp"

double distance(const Vector3D &r_i, const Vector3D &r_j) {
  auto r_x = r_i.x - r_j.x;
  auto r_y = r_i.y - r_j.y;
  auto r_z = r_i.z - r_j.z;
  return std::sqrt(r_x * r_x + r_y * r_y + r_z * r_z);
}

double Vector3D::distance_to(const Vector3D &other) const {
  return distance(*this, other);
}
