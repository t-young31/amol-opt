#ifndef COORDINATE_HPP
#define COORDINATE_HPP
#include "vector3d.hpp"
#include <stdexcept>
#include <string>
#include <vector>

class Coordinate : public Vector3D {
public:
  Coordinate() = default;

  static Coordinate from_xyz_line(std::string &line);
};

typedef std::vector<Coordinate> Coordinates;
#endif /* COORDINATE_HPP */
