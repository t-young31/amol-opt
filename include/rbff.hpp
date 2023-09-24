#ifndef RBFF_HPP
#define RBFF_HPP
#include "ff.hpp"
#include <vector>

struct HarmonicBond {
  const unsigned int i;
  const unsigned int j;
  const double half_k;
  const double r_eqm;
};

struct RepulsivePair {
  unsigned int i;
  unsigned int j;
  double c;
};

class RBForceField : public ForceField {
public:
  static RBForceField from_molecule(const Molecule &molecule);

  // Needs to be static for EnzymeAD
  static double energy(Coordinate *coordinates, const RBForceField &ff);
  void update_gradient(Molecule &molecule) const override;

private:
  RBForceField() = default;

  std::vector<HarmonicBond> harmonic_bonds;
  std::vector<RepulsivePair> repulsive_pairs;
};
#endif /* RBFF_HPP */
