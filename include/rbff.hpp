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
  void update_gradient(Molecule &molecule) const override;

private:
  RBForceField() = default;

  std::vector<HarmonicBond> harmonic_bonds;
  std::vector<RepulsivePair> repulsive_pairs;

  // Needs to be static with raw pointers for EnzymeAD
  static double harmonic_energy(Coordinate *coordinates, HarmonicBond *bonds,
                                std::size_t n);
  static double repulsive_energy(Coordinate *coordinates, RepulsivePair *pairs,
                                 std::size_t n);
};
#endif /* RBFF_HPP */
