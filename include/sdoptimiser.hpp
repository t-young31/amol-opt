#include "optimiser.hpp"

class SDOptimiser : public Optimiser {
public:
  SDOptimiser() = default;
  double max_step_component = 0.1; // Å

  void optimise(Molecule &molecule, const ForceField &ff) override;

private:
  double scaled_component(double step_component);
};
