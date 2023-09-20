#include "tmp.h"
#include <iostream>

int main() {

  double x = 3.14; // y = x^2 -> dydx  = 2x
  double grad_x = __enzyme_autodiff((void *)square, x);

  printf("square'(%f) = %f\n", x, grad_x);
  return 0;
}
