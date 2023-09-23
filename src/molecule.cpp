#include "molecule.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

inline bool is_blank(std::string &line) {
  for (auto c : line) {
    if (!std::isspace(c)) {
      return false;
    }
  }
  return true;
}

Molecule Molecule::from_xyz_file(std::string filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file!");
  }

  auto molecule = Molecule();
  std::string line;
  uint declared_number_of_atoms = 0;
  uint i = 0;

  while (getline(file, line)) {
    if (i == 0) { // Number of atoms line
      declared_number_of_atoms = std::stoi(line);
    } else if (i == 1) { // Title line
      // noop
    } else if (is_blank(line)) {
      break;
    } else {
      molecule.atoms.push_back(Atom::from_xyz_line(line));
      molecule.coordinates.push_back(Coordinate::from_xyz_line(line));
      molecule.gradient.push_back(Vector3D());
    }
    i += 1;
  }
  file.close();

  if (declared_number_of_atoms != molecule.atoms.size()) {
    throw std::runtime_error(
        "Number of atoms declared didn't equal the number found");
  }

  return molecule;
}

uint Molecule::n_atoms() { return atoms.size(); }
