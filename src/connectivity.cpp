#include "connectivity.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>

Connectivity
Connectivity::from_atoms_and_coordinates(const Atoms &atoms,
                                         const Coordinates &coordinates) {
  if (atoms.size() != coordinates.size()) {
    throw std::runtime_error(
        "Cannot build connectivity for different number of atoms/coordinates");
  }

  auto connectivity = Connectivity();
  connectivity.add_bonds(atoms, coordinates);
  connectivity.add_non_bonded(coordinates);

  return connectivity;
}

void Connectivity::add_bonds(const Atoms &atoms,
                             const Coordinates &coordinates) {
  auto bond_factor = (atoms.are_h2()) ? 3.0 : 1.3;

  for (int i = 0; i < atoms.size(); i++) {
    std::map<double, AtomIndexPair> possible_bonds;

    for (int j = i + 1; j < atoms.size(); j++) {
      auto max_r = bond_factor *
                   (atoms[i].covalent_radius() + atoms[j].covalent_radius());
      auto r = coordinates[i].distance_to(coordinates[j]);

      if (r < max_r) {
        possible_bonds.emplace(std::make_pair(r, AtomIndexPair(i, j)));
      }
    }

    unsigned int n_bonds = 0;
    for (auto const &[r, pair] : possible_bonds) { // Maps are default sorted
      if (n_bonds == atoms[i].maximum_valance()) {
        break;
      }
      bonds.push_back(pair);
    }
  }
}

void Connectivity::add_non_bonded(const Coordinates &coordinates) {
  for (int i = 0; i < coordinates.size(); i++) {
    for (int j = i + 1; j < coordinates.size(); j++) {
      auto r = coordinates[i].distance_to(coordinates[j]);
      if (r > 10) { // 10 Å cuttoff for nonbonded pairs
        continue;
      }
      auto pair = AtomIndexPair(i, j);
      if (std::find(bonds.begin(), bonds.end(), pair) == bonds.end()) {
        non_bonded.push_back(pair);
      }
    }
  }
}
