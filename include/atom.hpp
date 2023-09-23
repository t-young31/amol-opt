#ifndef ATOM_HPP
#define ATOM_HPP
#include <string>
#include <vector>

extern const char *elements[];

class Atom {
public:
  std::string atomic_symbol;
  unsigned short atomic_number;

  static Atom from_xyz_line(std::string &line);

  bool has_valid_symbol();

private:
  Atom() = default;
};

typedef std::vector<Atom> Atoms;

class AtomIndexPair {
public:
  unsigned int i;
  unsigned int j;

  AtomIndexPair(unsigned int _i, unsigned int _j) {
    i = _i;
    j = _j;
  }
};

typedef std::vector<AtomIndexPair> AtomIndexPairs;
#endif /* ATOM_HPP */
