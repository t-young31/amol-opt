#include "atom.hpp"
#include "coordinate.hpp"
#include "molecule.hpp"
#include "rbff.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

void __enzyme_autodiff(void *, ...);

int enzyme_dup;   // Enzyme duplicate argument
int enzyme_const; // Enzyme constant argument

int main() {

  auto molecule = Molecule::from_xyz_file("h2.xyz");
  auto ff = RBForceField::from_molecule(molecule);

  std::cout << RBForceField::energy(molecule.coordinates_ptr(), ff)
            << std::endl;

  __enzyme_autodiff((void *)RBForceField::energy, enzyme_dup,
                    molecule.coordinates_ptr(), molecule.gradient_ptr(),
                    enzyme_const, &ff);

  std::cout << molecule.gradient[0].x << std::endl;

  // https://github.com/EnzymeAD/Enzyme/issues/323
  return 0;
}
