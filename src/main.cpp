#include "atom.hpp"
#include "coordinate.hpp"
#include "molecule.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

inline double distance(Coordinate &r_i, Coordinate &r_j) {
  auto r_x = r_i.x - r_j.x;
  auto r_y = r_i.y - r_j.y;
  auto r_z = r_i.z - r_j.z;
  return std::sqrt(r_x * r_x + r_y * r_y + r_z * r_z);
}

inline double energy(Coordinate *coordinates) {
  auto d = distance(coordinates[0], coordinates[1]) - 0.77; // (r - 0.77 A)

  return 0.5 * d * d;
}

class RBForceField {
public:
  RBForceField from_molecule(const Molecule &molecule);

  static double energy(Coordinate *coordinates, uint n_atoms,
                       const RBForceField &ff);

private:
  RBForceField() = default;

  AtomIndexPairs bonded_pairs;
  AtomIndexPairs repulsive_pairs;
};

inline RBForceField RBForceField::from_molecule(const Molecule &molecule) {
  auto ff = RBForceField();

  return ff;
}

inline double RBForceField::energy(Coordinate *coordinates, uint n_atoms,
                                   const RBForceField &ff) {
  // TODO
  return 0.0;
}

void __enzyme_autodiff(void *, ...);

int enzyme_dup; // Enzyme duplicate argument

int main() {

  auto molecule = Molecule::from_xyz_file("h2.xyz");
  std::cout << energy(molecule.coordinates.data()) << std::endl;

  __enzyme_autodiff((void *)energy, enzyme_dup, molecule.coordinates_ptr(),
                    molecule.gradient_ptr());

  std::cout << molecule.gradient[0].x << std::endl;

  // https://github.com/EnzymeAD/Enzyme/issues/323
  return 0;
}
