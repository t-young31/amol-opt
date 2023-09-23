#ifndef ATOM_HPP
#define ATOM_HPP
#include <array>
#include <string>
#include <vector>

class Atom {
public:
  std::string atomic_symbol;
  unsigned short atomic_number() const;

  static Atom from_xyz_line(std::string &line);
  bool has_valid_symbol() const;
  const double covalent_radius() const;
  const unsigned int maximum_valance() const;

private:
  Atom() = default;
};

class Atoms : public std::vector<Atom> {
public:
  bool are_h2() const {
    return size() == 2 && data()[0].atomic_symbol == "H" &&
           data()[1].atomic_symbol == "H";
  }
};

class AtomIndexPair {
public:
  unsigned int i;
  unsigned int j;

  AtomIndexPair(unsigned int _i, unsigned int _j) {
    i = _i;
    j = _j;
  }

  bool operator==(const AtomIndexPair &other) const {
    return i == other.i && j == other.j;
  }
};

typedef std::vector<AtomIndexPair> AtomIndexPairs;

namespace Elements {
extern const std::array<std::string, 118> atomic_symbols;
extern const std::array<double, 86> covalent_radii;
extern const std::array<unsigned int, 38> maximum_valencies;
} // namespace Elements

#endif /* ATOM_HPP */
