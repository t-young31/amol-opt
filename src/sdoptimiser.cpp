#include "sdoptimiser.hpp"
#include <iostream>

void SDOptimiser::optimise(Molecule &molecule, const ForceField &ff) {

  for (auto i = 0; i < max_number_of_steps; i++) {
    ff.update_gradient(molecule);

    for (auto j = 0; j < molecule.n_atoms(); j++) {
      auto dx = scaled_component(-step_size * molecule.gradient[j].x);
      auto dy = scaled_component(-step_size * molecule.gradient[j].y);
      auto dz = scaled_component(-step_size * molecule.gradient[j].z);

      molecule.coordinates[j].x += dx;
      molecule.coordinates[j].y += dy;
      molecule.coordinates[j].z += dz;
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
    // smallest absolute value
    return std::max(step_component, -max_step_component);
  } else {
    return std::min(step_component, max_step_component);
  }
}
