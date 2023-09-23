#ifndef CONNECTIVITY_HPP
#define CONNECTIVITY_HPP
#include "atom.hpp"
#include "coordinate.hpp"

class Connectivity {
public:
  AtomIndexPairs bonds;
  AtomIndexPairs non_bonded;

  static Connectivity
  from_atoms_and_coordinates(const Atoms &atoms,
                             const Coordinates &coordinates);

private:
  void add_bonds(const Atoms &atoms, const Coordinates &coordinates);
  void add_non_bonded(const Coordinates &coordinates);
};

#endif /* CONNECTIVITY_HPP */
