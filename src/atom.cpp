#include "atom.hpp"
#include <stdexcept>

const char *elements[] = {
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

bool Atom::has_valid_symbol() {
  // std::cout << "Checking symbol [" << atomic_symbol << "] is valid" <<
  // std::endl;

  for (auto valid_atomic_symbol : elements) {
    if (atomic_symbol == std::string(valid_atomic_symbol)) {
      return true;
    }
  }
  return false;
}
