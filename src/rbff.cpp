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

    ff.harmonic_bonds.push_back(HarmonicBond{bond.i, bond.j, 500., r_eqm});
  }

  for (auto const &pair : molecule.connectivity.non_bonded) {
    ff.repulsive_pairs.push_back(RepulsivePair{pair.i, pair.j, 10.});
  }

  return ff;
}

double RBForceField::energy(Coordinate *coordinates, const RBForceField &ff) {
  double energy = 0.0;

  for (auto const &bond : ff.harmonic_bonds) {
    auto r = coordinates[bond.i].distance_to(coordinates[bond.j]);
    auto d = (r - bond.r_eqm);
    // std::cout << "Harmonic: " << bond.i << '\t' << bond.j << '\t' << r <<
    // '\t' << bond.r_eqm << '\t' << d << '\n';
    energy += bond.half_k * d * d;
  }
  // std::cout << '\n';

  for (auto const &pair : ff.repulsive_pairs) {
    auto r = coordinates[pair.i].distance_to(coordinates[pair.j]);
    // std::cout << "Repulsive: " << r << '\t' << pair.c << '\n';
    energy += pair.c / (r * r);
  }

  return energy;
}

void RBForceField::update_gradient(Molecule &molecule) const {
  molecule.gradient.zero();

  std::cout << "enzyme_const " << enzyme_const << '\n';
  std::cout << "this " << &*this << '\n';
  std::cout << "harm " << molecule.atoms[0].covalent_radius() << '\n';
  std::cout << "r_eqm " << harmonic_bonds[0].r_eqm << '\n';
  std::cout << "rep " << repulsive_pairs.size() << '\n';

  __enzyme_autodiff((void *)RBForceField::energy, enzyme_dup,
                    molecule.coordinates_ptr(), molecule.gradient_ptr(),
                    enzyme_const, &*this);
}
