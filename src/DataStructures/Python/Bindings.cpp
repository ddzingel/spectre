// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <pybind11/pybind11.h>

#include "DataStructures/Python/DataVector.hpp"
#include "DataStructures/Python/Matrix.hpp"

PYBIND11_MODULE(_PyDataStructures, m) {  // NOLINT
  py_bindings::bind_datavector(m);
  py_bindings::bind_matrix(m);
}
