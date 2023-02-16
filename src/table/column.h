#ifndef COLUMN_H_
#define COLUMN_H_

#include <functional>
#include <stdexcept>
#include <type_traits>

// Still not decided whether should I choose a template column
// or polymorphic columns with distinctions for each individual
// data types

template <typename data_t>
struct column {
  column<data_t>(std::function<bool(data_t)> _constraint) : constraint(_constraint){}
  column<data_t>(std::function<bool(data_t)> _constraint, bool _is_nullable)
      : constraint(_constraint), is_nullable(_is_nullable) {}

  // This constructor requires to validate whether provided data
  // satisfies provided constraint. If constraint isn't satisfied
  // an exception gets thrown. It needs to be handled
  column<data_t>(std::function<bool(data_t)> _constraint, bool _is_nullable, data_t _value)
      : constraint(_constraint), is_nullable(_is_nullable) {
    if (validate_data()) {
      value = _value;
    } else {
      throw std::invalid_argument("Provived data couldn't satisfy column's constraint");
    }
  }

  std::function<bool(data_t)> constraint;
  bool is_nullable = false;
  data_t value;

  bool validate_data() { return constraint(value); }

  template <typename T>
  bool validate_type(T) {
    return std::is_nothrow_convertible<T, data_t>();
  }
};

typedef __int128_t integral;
typedef long double numeric;
typedef char varchar[255];

#endif