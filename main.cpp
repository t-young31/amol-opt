#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

const char *atoms[] = {
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

inline bool is_blank(std::string &line) {
  for (auto c : line) {
    if (!std::isspace(c)) {
      return false;
    }
  }
  return true;
}

class Coordinate {
public:
  double x;
  double y;
  double z;

  Coordinate() = default;

  static Coordinate from_xyz_line(std::string &line);
};

inline Coordinate Coordinate::from_xyz_line(std::string &line) {
  std::vector<std::string> items; // e.g. ["H", "0.0", "0.0", "0.0"]
  std::string item;

  for (auto c : line) {
    if (!std::isspace(c)) {
      item += c;
      continue;
    }

    if (item.size() > 0) {
      items.push_back(item);
      item = "";
    }
  }
  items.push_back(item);

  if (items.size() < 4) {
    throw std::runtime_error(
        "Not enough items on xyz line to obtain coordinate");
  }

  auto coordinate = Coordinate();
  coordinate.x = stod(items[1]);
  coordinate.y = stod(items[2]);
  coordinate.z = stod(items[3]);

  return coordinate;
}

typedef std::vector<Coordinate> Coordinates;

class Atom {
public:
  std::string atomic_symbol;
  unsigned short atomic_number;

  static Atom from_xyz_line(std::string &line);

  bool has_valid_symbol();

private:
  Atom() = default;
};

inline Atom Atom::from_xyz_line(std::string &line) {
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

inline bool Atom::has_valid_symbol() {
  // std::cout << "Checking symbol [" << atomic_symbol << "] is valid" <<
  // std::endl;

  for (auto valid_atomic_symbol : atoms) {
    if (atomic_symbol == std::string(valid_atomic_symbol)) {
      return true;
    }
  }
  return false;
}

class Molecule {
public:
  static Molecule from_xyz_file(std::string filename);
  std::vector<Coordinate> coordinates;
  std::vector<Atom> atoms;

  uint n_atoms();

private:
  Molecule() = default;
};

inline Molecule Molecule::from_xyz_file(std::string filename) {
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

inline uint Molecule::n_atoms() { return atoms.size(); }

inline double distance(Coordinate &r_i, Coordinate &r_j) {
  auto r_x = r_i.x - r_j.x;
  auto r_y = r_i.y - r_j.y;
  auto r_z = r_i.z - r_j.z;
  return std::sqrt(r_x * r_x + r_y * r_y + r_z * r_z);
}

inline double energy(Coordinates coordinates) {
  auto d = distance(coordinates[0], coordinates[1]) - 0.77; // (r - 0.77 A)

  return 0.5 * d * d;
}

void __enzyme_autodiff(void *, int, Coordinates, Coordinates);

int enzyme_dup;

int main() {

  auto molecule = Molecule::from_xyz_file("h2.xyz");
  std::cout << energy(molecule.coordinates) << std::endl;

  auto g = Coordinates(molecule.n_atoms());

  __enzyme_autodiff((void *)energy, enzyme_dup, molecule.coordinates, g);
  std::cout << g[0].x << std::endl;

  return 0;
}
