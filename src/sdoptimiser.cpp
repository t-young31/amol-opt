#include "sdoptimiser.hpp"
#include <iostream>

void SDOptimiser::optimise(Molecule &molecule, const ForceField &ff) {

  for (auto i = 0; i < max_number_of_steps; i++) {
    ff.update_gradient(molecule);

    for (auto j = 0; j < molecule.n_atoms(); j++) {
      molecule.coordinates[j].x +=
          scaled_component(-step_size * molecule.gradient[j].x);
      molecule.coordinates[j].y +=
          scaled_component(-step_size * molecule.gradient[j].y);
      molecule.coordinates[j].z +=
          scaled_component(-step_size * molecule.gradient[j].z);
    }

    // std::cout << " x(step) " << step_size * molecule.gradient[0].x
    //          << "  RMS(|g|) " << molecule.rms_gradient() << std::endl;

    if (molecule.rms_gradient() < gtol) {
      return;
    }
  }
}

double SDOptimiser::scaled_component(double step_component) {
  if (step_component < 0) {
    return std::max(step_component,
                    -max_step_component); // smallest absolute value
  } else {
    return std::min(step_component, max_step_component);
  }
}
