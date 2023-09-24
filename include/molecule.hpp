#ifndef MOLECULE_HPP
#define MOLECULE_HPP
#include "atom.hpp"
#include "connectivity.hpp"
#include "coordinate.hpp"
#include "gradient.hpp"

class Molecule {
public:
  static Molecule from_xyz_file(std::string filename);
  Coordinates coordinates;
  Gradient gradient;
  Atoms atoms;
  Connectivity connectivity;

  unsigned int n_atoms() { return atoms.size(); }
  Coordinate *coordinates_ptr() { return coordinates.data(); }
  Vector3D *gradient_ptr() { return gradient.data(); }
  double rms_gradient() const;

private:
  Molecule() = default;
};

#endif /* MOLECULE_HPP */
