#include "molecule.hpp"
#include "rbff.hpp"
#include "sdoptimiser.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    throw std::runtime_error("Must be called with a .xyz file");
  }

  auto filename = std::string(argv[1]);
  auto molecule = Molecule::from_xyz_file(filename);
  auto ff = RBForceField::from_molecule(molecule);

  auto optimiser = SDOptimiser();
  optimiser.step_size = 0.01; // Å
  optimiser.optimise(molecule, ff);

  molecule.write_xyz_file("opt.xyz");

  return 0;
}
