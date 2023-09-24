#include "rbff.hpp"
#include <iostream>

int enzyme_dup;   // Enzyme duplicate argument
int enzyme_const; // Enzyme constant argument

RBForceField RBForceField::from_molecule(const Molecule &molecule) {
  auto ff = RBForceField();

  for (auto const &bond : molecule.connectivity.bonds) {
    auto c_i = molecule.atoms[bond.i].covalent_radius();
    auto c_j = molecule.atoms[bond.j].covalent_radius();
    auto r_eqm = c_i + c_j;

    ff.harmonic_bonds.push_back(HarmonicBond{bond.i, bond.j, 25., r_eqm});
  }

  for (auto const &pair : molecule.connectivity.non_bonded) {
    ff.repulsive_pairs.push_back(RepulsivePair{pair.i, pair.j, 0.5});
  }

  return ff;
}

double RBForceField::harmonic_energy(Coordinate *coordinates,
                                     HarmonicBond *bonds, std::size_t n) {
  double energy = 0.0;

  for (auto i = 0; i < n; i++) {
    auto bond = bonds[i];
    auto r = coordinates[bond.i].distance_to(coordinates[bond.j]);
    auto d = (r - bond.r_eqm);
    energy += bond.half_k * d * d;
  }

  return energy;
}

double RBForceField::repulsive_energy(Coordinate *coordinates,
                                      RepulsivePair *pairs, std::size_t n) {
  double energy = 0.0;

  for (auto i = 0; i < n; i++) {
    auto pair = pairs[i];
    auto r = coordinates[pair.i].distance_to(coordinates[pair.j]);
    energy += pair.c / (r * r);
  }

  return energy;
}

void RBForceField::update_gradient(Molecule &molecule) const {
  // Enzyme accumulates gradients so zero and then add for the harmonic and
  // repulsive terms
  molecule.gradient.zero();

  __enzyme_autodiff((void *)RBForceField::harmonic_energy, enzyme_dup,
                    molecule.coordinates_ptr(), molecule.gradient_ptr(),
                    enzyme_const, harmonic_bonds.data(), enzyme_const,
                    harmonic_bonds.size());
  __enzyme_autodiff((void *)RBForceField::repulsive_energy, enzyme_dup,
                    molecule.coordinates_ptr(), molecule.gradient_ptr(),
                    enzyme_const, repulsive_pairs.data(), enzyme_const,
                    repulsive_pairs.size());
}
