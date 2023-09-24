#include "sdoptimiser.hpp"
#include <iostream>

void SDOptimiser::optimise(Molecule &molecule, const ForceField &ff) {

  for (auto i = 0; i < max_number_of_steps; i++) {
    ff.update_gradient(molecule);

    std::cout << "RMS(|g|) " << molecule.rms_gradient() << std::endl;

    if (molecule.rms_gradient() < gtol) {
      return;
    }
  }
}
