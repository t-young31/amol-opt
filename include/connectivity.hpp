#ifndef CONNECTIVITY_HPP
#define CONNECTIVITY_HPP
#include "atom.hpp"
#include "coordinate.hpp"

class Connectivity {
public:
  AtomIndexPairs bonds;

  Connectivity from_atoms_and_coordinates(Atoms &atoms,
                                          Coordinates &coordinates);
};

#endif /* CONNECTIVITY_HPP */
