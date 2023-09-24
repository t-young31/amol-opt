#include "molecule.hpp"
#include "rbff.hpp"
#include "sdoptimiser.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

int main() {

  auto molecule = Molecule::from_xyz_file("h2.xyz");
  auto ff = RBForceField::from_molecule(molecule);

  auto optimiser = SDOptimiser();
  optimiser.step_size = 0.01; // Å
  optimiser.optimise(molecule, ff);

  molecule.write_xyz_file("opt.xyz");

  return 0;
}
