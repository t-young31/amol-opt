#ifndef GRADIENT_HPP
#define GRADIENT_HPP
#include "vector3d.hpp"

class Gradient : public std::vector<Vector3D> {
public:
  void zero() {
    for (auto itr = begin(); itr != end(); ++itr) {
      itr->x = 0.0;
      itr->y = 0.0;
      itr->z = 0.0;
    }
  };
};

#endif /* GRADIENT_HPP */
