#pragma once

#include <bits/move.h>
#include <bits/stl_iterator_base_types.h>
#include <type_traits>
#include <iosfwd>

namespace Sphinx::Utils {

/// Output iterator that inserts a delimiter between elements.
template <typename _DelimT, typename ostream_type>
class joiner_iterator {
public:
  typedef std::output_iterator_tag iterator_category;
  typedef void value_type;
  typedef void difference_type;
  typedef void pointer;
  typedef void reference;

  joiner_iterator(ostream_type &__os, const _DelimT &__delimiter) noexcept(
      std::is_nothrow_copy_constructible_v<_DelimT>)
    : _M_out(std::__addressof(__os)), _M_delim(__delimiter)
  {
  }

  joiner_iterator(ostream_type &__os, _DelimT &&__delimiter) noexcept(
      std::is_nothrow_move_constructible_v<_DelimT>)
    : _M_out(std::__addressof(__os)), _M_delim(std::move(__delimiter))
  {
  }

  template <typename _Tp>
  joiner_iterator &operator=(const _Tp &__value)
  {
    if (!_M_first)
      *_M_out << _M_delim;
    _M_first = false;
    *_M_out << __value;
    return *this;
  }

  joiner_iterator &operator*() noexcept { return *this; }
  joiner_iterator &operator++() noexcept { return *this; }
  joiner_iterator &operator++(int)noexcept { return *this; }

private:
  ostream_type *_M_out;
  _DelimT _M_delim;
  bool _M_first = true;
};

/// Object generator for ostream_joiner.
template <typename ostream_type, typename _DelimT>
inline joiner_iterator<std::decay_t<_DelimT>, ostream_type>
make_joiner_iterator(ostream_type &__os, _DelimT &&__delimiter)
{
  return {__os, std::forward<_DelimT>(__delimiter)};
}

} // namespace Sphinx::Utils
