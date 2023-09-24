#ifndef FF_HPP
#define FF_HPP
#include "molecule.hpp"

void __enzyme_autodiff(void *, ...);

class ForceField {
public:
  virtual void update_gradient(Molecule &molecule) const = 0;
};
#endif /* FF_HPP */
