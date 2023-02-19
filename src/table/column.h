#ifndef COLUMN_H_
#define COLUMN_H_

#include <functional>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <variant>

// Still not decided whether should I choose a template column
// or polymorphic columns with distinctions for each individual
// data types

template <typename data_t>
bool default_constraint(data_t) {
  return true;
}

template <typename data_t, bool nullable = true, bool(constraint)(data_t) = default_constraint>
struct column {
  /*  MEMBERS  */
  static inline std::string constraint_error =
      std::string("Provided data couldn't satisfy column's constraint");
  data_t data;
  bool is_null;

  /*  CONSTRUCTORS  */
  // Create column without providing data
  column() : data(), is_null(true) {
    if (!validate_data()) {
      throw std::invalid_argument(constraint_error);
    }
  }

  // Create column and initialize it with data
  column(data_t data) : data(data), is_null(false) {
    if (!validate_data()) {
      throw std::invalid_argument(constraint_error);
    }
  }

  /*  MEMBER FUNCTIONS  */

  // Used to set data to existing column
  // Data validation is provided while is
  // this function
  void set_data(data_t data) {
    if (validate_data(data)) {
      this->data = data;
    } else {
      throw std::invalid_argument(constraint_error);
    }
  }

  // validate existing data
  [[nodiscard]] bool validate_data() noexcept { return (constraint(data) && (nullable || (!is_null))); }
  // validate data provided as function parameter
  [[nodiscard]] bool validate_data(data_t data) noexcept { return (constraint(data) && (nullable || (!is_null))); }
  [[nodiscard]] data_t get() noexcept { return data; }

  // validate whether provided parameter
  // matches column's type
  template <typename T>
  bool validate_type(T) {
    return std::is_nothrow_convertible<T, data_t>();
  }
};

typedef __int128_t integral;
typedef long double numeric;
typedef char varchar[255];

#endif