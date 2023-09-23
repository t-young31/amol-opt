#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP
#include <vector>

class Vector3D {
public:
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;

  Vector3D() = default;
};

typedef std::vector<Vector3D> Gradient;
#endif /* VECTOR3D_HPP */
