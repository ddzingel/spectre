// Distributed under the MIT License.
// See LICENSE.txt for details.

#pragma once

#include "Evolution/Systems/Cce/AnalyticSolutions/LinearizedBondiSachs.hpp"
#include "Evolution/Systems/Cce/Initialize/InitializeJ.hpp"
#include "Parallel/RegisterDerivedClassesWithCharm.hpp"

/// \cond
namespace Cce {
namespace Solutions::LinearizedBondiSachs_detail::InitializeJ {
struct LinearizedBondiSachs;
}
/// \endcond

/// A function for registering all of the InitializeJ derived classes with
/// charm, including the ones not intended to be directly option-creatable
template <bool UsesPartiallyFlatCartesianCoordinates,
          typename BoundaryComponent>
void register_initialize_j_with_charm() {
  PUPable_reg(SINGLE_ARG(Solutions::LinearizedBondiSachs_detail::InitializeJ::
                         LinearizedBondiSachs));

  if constexpr (tt::is_a_v<AnalyticWorldtubeBoundary, BoundaryComponent>) {
    Parallel::register_derived_classes_with_charm<
        Cce::InitializeJ::InitializeJ<false>>();
  } else {
    Parallel::register_derived_classes_with_charm<Cce::InitializeJ::InitializeJ<
        UsesPartiallyFlatCartesianCoordinates>>();
  }
}
}  // namespace Cce
