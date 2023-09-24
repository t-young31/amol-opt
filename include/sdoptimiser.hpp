#include "optimiser.hpp"

class SDOptimiser : public Optimiser {
public:
  SDOptimiser() = default;

  void optimise(Molecule &molecule, const ForceField &ff) override;
};
