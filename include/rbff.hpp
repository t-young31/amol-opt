#include "molecule.hpp"
#include <vector>

struct HarmonicBond {
  unsigned int i;
  unsigned int j;
  double half_k;
  double r_eqm;
};

struct RepulsivePair {
  unsigned int i;
  unsigned int j;
  double c;
};

class RBForceField {
public:
  static RBForceField from_molecule(const Molecule &molecule);

  // Needs to be static for EnzymeAD
  static double energy(Coordinate *coordinates, const RBForceField &ff);

private:
  RBForceField() = default;

  std::vector<HarmonicBond> harmonic_bonds;
  std::vector<RepulsivePair> repulsive_pairs;
};
