#ifndef TABLE_H_
#define TABLE_H_

#include <fmt/core.h>

#include <algorithm>
#include <any>
#include <map>
#include <span>
#include <stdexcept>
#include <string>

#include "column.h"

template <typename... C>
struct TypeRow {
  using column_tuple = std::tuple<C...>;
  column_tuple columns;

  TypeRow(C&&... c) : columns(std::forward<C>(c)...) {
    if (!validate_column_names()) {
      throw std::invalid_argument("Duplicate Column Names");
    }
  }

  template <int index>
  [[nodiscard]] auto get() {
    return std::get<index>(columns);
  }

  template <int index>
  [[nodiscard]] const std::string& get_name() {
    return std::get<index>(columns).get_name();
  }

  template <int index>
  void set_name(std::string& name) {
    std::get<index>(columns).set_name(name);
  }

  template <size_t I = 0, size_t J = 1>
  [[nodiscard]] bool validate_column_names() {
    if (std::tuple_size<column_tuple>() < 1) {
      return true;
    }
    bool no_duplicates = true;
    recursive_validate_column_names<I, J>(no_duplicates);
    if constexpr (I + 1 != std::tuple_size<column_tuple>() && J + 1 != std::tuple_size<column_tuple>()) {
      recursive_validate_column_names<I + 1, J + 1>(no_duplicates);
    }
    return no_duplicates;
  }

  template <size_t I, size_t J>
  void recursive_validate_column_names(bool& no_duplicates) {
    if (I != J && get_name<I>().compare(get_name<J>())) {
      no_duplicates = false;
    }
    if constexpr (J + 1 != std::tuple_size<column_tuple>()) {
      recursive_validate_column_names<I, J + 1>(no_duplicates);
    }
  }
};

template <typename... C>
struct DataRow {
  std::tuple<C...> cells;

  DataRow(C&&... c) : cells(std::forward<C>(c)...) {}

  template <int index>
  [[nodiscard]] auto get() {
    return std::get<index>(cells).get();
  }

  template <int index, typename data_t>
  void set_data(data_t data) {
    std::get<index>(cells).set_data(data);
  }
};

template <typename TR, typename DR>
struct Table {
  TR type_row;
  std::map<int, DR> rows;
  std::string name;

  Table(std::string name) : name(name){}
  
  [[nodiscard]] std::string& get_name(){
    return this->name;
  }

  void add_row(DR&& row) {
    int index;
    if (rows.empty()) {
      index = 0;
    } else {
      index = (rows.crbegin() + 1);
    }
    rows.insert(std::pair<int, DR>(index, row));
  }
};

#endif