#include "molecule.hpp"
#include "rbff.hpp"
#include "sdoptimiser.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

int main() {

  auto molecule = Molecule::from_xyz_file("h2.xyz");
  auto ff = RBForceField::from_molecule(molecule);
  ff.update_gradient(molecule);
  std::cout << molecule.gradient[0].x << std::endl;

  // auto c = RBForceField::from_molecule(molecule);
  molecule.gradient.zero();
  ff.update_gradient(molecule);

  std::cout << molecule.gradient[0].x << std::endl;
  return 0;

  auto optimiser = SDOptimiser();
  optimiser.step_size = 0.1; // Å
  optimiser.optimise(molecule, ff);
  // molecule.write_xyz_file("opt.xyz");

  return 0;
}
