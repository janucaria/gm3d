#ifndef CPPID_GM3D_DETAIL_BASIC_POINT_VECTOR_HPP
#define CPPID_GM3D_DETAIL_BASIC_POINT_VECTOR_HPP

#include <cstddef>
#include <type_traits>
#include <utility>

#include <boost/qvm/all.hpp>

#include "type_traits.hpp"

namespace cppid::gm3d::detail {

template<typename TDerived, typename T, std::size_t N>
struct basic_point_vector {
  
  using scalar_type = T;

  static constexpr auto dimensions = N;

  scalar_type elems[dimensions];

  basic_point_vector() noexcept = default;

  template<
   typename... Us,
   typename = std::enable_if_t<((sizeof...(Us) == dimensions) && ... &&
                                std::is_convertible_v<Us, scalar_type>)>>
  basic_point_vector(Us... args) noexcept
  : elems{scalar_type(args)...}
  {
  }

  void x(scalar_type val) noexcept
  {
    elems[0] = val;
  }

  void y(scalar_type val) noexcept
  {
    elems[1] = val;
  }

  template<auto VN = dimensions, std::enable_if_t<(VN >= 3)>* = nullptr>
  void z(scalar_type val) noexcept
  {
    elems[2] = val;
  }

  template<auto VN = dimensions, std::enable_if_t<(VN >= 4)>* = nullptr>
  void w(scalar_type val) noexcept
  {
    elems[3] = val;
  }

  auto x() const noexcept -> scalar_type
  {
    return elems[0];
  }

  auto y() const noexcept -> scalar_type
  {
    return elems[1];
  }

  template<auto VN = dimensions, std::enable_if_t<(VN >= 3)>* = nullptr>
  auto z() const noexcept -> scalar_type
  {
    return elems[2];
  }

  template<auto VN = dimensions, std::enable_if_t<(VN >= 4)>* = nullptr>
  auto w() const noexcept -> scalar_type
  {
    return elems[3];
  }
};

} // namespace cppid::gm3d::detail

namespace boost::qvm {
template<typename TVec, typename T, std::size_t N>
struct vec_traits<cppid::gm3d::detail::basic_point_vector<TVec, T, N>> {
  using point_vector_type = cppid::gm3d::detail::basic_point_vector<TVec, T, N>;

  using scalar_type = typename point_vector_type::scalar_type;

  static constexpr int dim = point_vector_type::dimensions;

  template<int I>
  static inline auto write_element(point_vector_type& v) noexcept
   -> scalar_type&
  {
    return v.elems[I];
  }

  template<int I>
  static inline auto read_element(point_vector_type const& v) noexcept
   -> scalar_type
  {
    return v.elems[I];
  }

  static inline auto write_element_idx(int i, point_vector_type& v) noexcept
   -> scalar_type&
  {
    return v.elems[i];
  }

  static inline auto read_element_idx(int i,
                                      point_vector_type const& v) noexcept
   -> scalar_type
  {
    return v.elems[i];
  }
};

} // namespace boost::qvm

#endif
