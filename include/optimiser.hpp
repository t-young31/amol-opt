#include "ff.hpp"
#include "molecule.hpp"

class Optimiser {
public:
  double gtol = 0.01;                    // tolerance on RMS(|g|)
  double step_size = 0.005;              // Å
  unsigned int max_number_of_steps = 10; // TODO

  virtual void optimise(Molecule &molecule, const ForceField &ff) = 0;
};
