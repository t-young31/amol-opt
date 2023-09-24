#include "ff.hpp"
#include "molecule.hpp"

class Optimiser {
public:
  double gtol = 0.01;     // tolerance on RMS(|g|)
  double step_size = 0.1; // Å
  unsigned int max_number_of_steps = 1000;

  virtual void optimise(Molecule &molecule, const ForceField &ff) = 0;
};
