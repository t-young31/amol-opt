#include "atom.hpp"
#include <stdexcept>

Atom Atom::from_xyz_line(std::string &line) {
  auto atom = Atom();

  for (auto c : line) {
    if (std::isspace(c)) {
      break;
    }
    atom.atomic_symbol += c;
  }

  if (!atom.has_valid_symbol()) {
    throw std::runtime_error("Atom has unknown symbol");
  }

  return atom;
}

bool Atom::has_valid_symbol() const {
  for (auto valid_atomic_symbol : Elements::atomic_symbols) {
    if (atomic_symbol == std::string(valid_atomic_symbol)) {
      return true;
    }
  }
  return false;
}

unsigned short Atom::atomic_number() const {
  for (auto i = 0; i < Elements::atomic_symbols.size(); i++) {
    if (Elements::atomic_symbols[i] == atomic_symbol) {
      return i + 1;
    }
  }
  throw std::runtime_error("Atom has unknown symbol");
}

const double Atom::covalent_radius() const {
  auto atomic_index = atomic_number() - 1;
  if (atomic_index >= Elements::covalent_radii.size()) {
    return 1.5; // Default 150 pm
  }

  double PICOMETER_TO_ANGSTROM = 0.01;
  return PICOMETER_TO_ANGSTROM * Elements::covalent_radii[atomic_index];
}

const unsigned int Atom::maximum_valance() const {
  auto atomic_index = atomic_number() - 1;

  if (atomic_index >= Elements::maximum_valencies.size()) {
    return 6; // Default
  }

  return Elements::maximum_valencies[atomic_index];
}

namespace Elements {
const std::array<std::string, 118> atomic_symbols = {
    "H",  "He", "Li", "Be", "B",  "C",  "N",  "O",  "F",  "Ne", "Na", "Mg",
    "Al", "Si", "P",  "S",  "Cl", "Ar", "K",  "Ca", "Sc", "Ti", "V",  "Cr",
    "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
    "Rb", "Sr", "Y",  "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd",
    "In", "Sn", "Sb", "Te", "I",  "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd",
    "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf",
    "Ta", "W",  "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po",
    "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U",  "Np", "Pu", "Am", "Cm",
    "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs",
    "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og",
};

const std::array<double, 86> covalent_radii = {
    31.,  28.,  128., 96.,  84.,  76.,  71.,  66.,  57.,  58.,  166.,
    141., 121., 111., 107., 105., 102., 106., 102., 203., 176., 170.,
    160., 153., 139., 161., 152., 150., 124., 132., 122., 122., 120.,
    119., 120., 116., 220., 195., 190., 175., 164., 154., 147., 146.,
    142., 139., 145., 144., 142., 139., 139., 138., 139., 140., 244.,
    215., 207., 204., 203., 201., 199., 198., 198., 196., 194., 192.,
    192., 189., 190., 187., 175., 187., 170., 162., 151., 144., 141.,
    136., 136., 132., 145., 146., 148., 140., 150., 150.,
};

const std::array<unsigned int, 38> maximum_valencies = {
    1, 0, 1, 2, 3, 4, 5, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1,
    2, 3, 4, 5, 6, 7, 7, 5, 4, 4, 6, 3, 4, 5, 6, 7, 2, 1, 2,
};

} // namespace Elements
