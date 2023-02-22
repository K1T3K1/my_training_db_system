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
struct Column {
  /*  MEMBERS  */
  std::string name;

  /*  CONSTRUCTORS  */
  // Create column without providing data
  Column(){
    throw std::invalid_argument("No column name provided");
  }
  Column(std::string name) : name(name) {}

  /*  MEMBER FUNCTIONS  */

  [[nodiscard]] const std::string& get_name() noexcept { return name; }
  void set_name(std::string& name) noexcept {this->name = name;}

  // validate data provided as function parameter
  [[nodiscard]] bool validate_data(void) noexcept { return nullable;}
  [[nodiscard]] bool validate_data(data_t data) noexcept { return (constraint(data)); }

  // validate whether provided parameter
  // matches column's type
  template <typename T>
  bool validate_type(T) {
    return std::is_nothrow_convertible<T, data_t>();
  }
};

template <typename data_t>
struct Cell {
  data_t data;
  bool is_null;

  Cell() : is_null(true) {}
  Cell(data_t data) : data(data), is_null(false) {}

  [[nodiscard]] data_t get() {
    if (is_null) {
      throw std::invalid_argument("cell is null");
    } else {
      return data;
    }
  }

  void set_data(data_t data) noexcept{
    this->data = data;
  }
};

typedef __int128_t integral;
typedef long double numeric;
typedef char varchar[255];

template <typename data_t, bool nullable = true, bool(constraint)(data_t) = default_constraint>
struct TypedColumn{
  using Column = Column<data_t, nullable, constraint>;
  TypedColumn(std::string name){
    c = std::make_unique<Column>(name);
  }
  std::unique_ptr<Column> c;
  std::unique_ptr<Column>& operator->(){return c;}
};

template <bool nullable = true, bool(constraint)(integral) = default_constraint>
struct ColumnIntegral : public TypedColumn<integral, nullable, constraint>{
  using TypedColumn = TypedColumn<integral, nullable, constraint>;
  ColumnIntegral(std::string name) : TypedColumn(name){}
};

template <bool nullable = true, bool(constraint)(numeric) = default_constraint>
struct ColumnNumeric : public TypedColumn<numeric, nullable, constraint>{
  using TypedColumn = TypedColumn<numeric, nullable, constraint>;
  ColumnNumeric(std::string name) : TypedColumn(name){}
};

template <bool nullable = true, bool(constraint)(varchar) = default_constraint>
struct ColumnVarchar : public TypedColumn<varchar, nullable, constraint>{
  using TypedColumn = TypedColumn<varchar, nullable, constraint>;
  ColumnVarchar(std::string name) : TypedColumn(name){}
};

#endif