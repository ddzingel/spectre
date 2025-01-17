// Distributed under the MIT License.
// See LICENSE.txt for details.

#pragma once

#include <boost/rational.hpp>
#include <cstddef>
#include <vector>

#include "DataStructures/DataBox/DataBox.hpp"
#include "Domain/Domain.hpp"
#include "Domain/Tags.hpp"
#include "Parallel/GlobalCache.hpp"
#include "Parallel/Printf.hpp"
#include "Parallel/Reduction.hpp"
#include "Utilities/MakeString.hpp"
#include "Utilities/StdHelpers.hpp"
#include "Utilities/System/Abort.hpp"

namespace amr::Actions {

/// \brief Use the AMR diagnostics gathered from all of the Element%s
///
/// Checks the following:
/// - That the fraction of Block volume (in the logical coordinate frame)
/// covered by all Element%s is equal to the number of Block%s in the Domain
///
/// Prints the following (as integers):
/// - The number of elements
/// - The number of grid points
/// - The average refinement level by logical dimension (i.e. not by the
///   physical dimensions)
/// - The average number of grid points by logical dimension
struct RunAmrDiagnostics {
  template <typename ParallelComponent, typename DbTagList,
            typename Metavariables, typename ArrayIndex>
  static void apply(db::DataBox<DbTagList>& box,
                    const Parallel::GlobalCache<Metavariables>& /*cache*/,
                    const ArrayIndex& /*array_index*/,
                    const boost::rational<size_t>& volume,
                    const size_t number_of_elements,
                    const size_t number_of_grid_points,
                    std::vector<size_t> refinement_levels_by_dim,
                    std::vector<size_t> extents_by_dim) {
    constexpr size_t volume_dim = Metavariables::volume_dim;
    const boost::rational<size_t> number_of_blocks{
        db::get<::domain::Tags::Domain<Metavariables::volume_dim>>(box)
            .blocks()
            .size()};
    if (number_of_blocks != volume) {
      sys::abort(MakeString{} << "Check Domain failed!  Expected volume "
                              << number_of_blocks << ", not " << volume
                              << "\n");
    }
    for (size_t d = 0; d < volume_dim; ++d) {
      extents_by_dim[d] /= number_of_elements;
      refinement_levels_by_dim[d] /= number_of_elements;
    }
    const std::string string_gcc_needs_to_use_in_order_for_printf_to_compile =
        MakeString{} << "Average refinement levels: "
                     << refinement_levels_by_dim
                     << "\nAverage grid points: " << extents_by_dim << "\n";
    Parallel::printf(
        "Number of elements: %zu\n"
        "Number of grid points: %zu\n"
        "%s\n",
        number_of_elements, number_of_grid_points,
        string_gcc_needs_to_use_in_order_for_printf_to_compile);
  }
};
}  // namespace amr::Actions
