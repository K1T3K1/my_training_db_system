#ifndef TABLE_H_
#define TABLE_H_

#include <any>
#include <span>
#include <string>
#include <fmt/core.h>

#include "column.h"

template <typename... C>
struct row {
  std::tuple<C...> columns;

  row(C&&... c) : columns(std::forward<C>(c)...){}

  template<int index>
  [[nodiscard]] auto get() {
    return std::get<index>(columns).get();
  }

  template<int index, typename data_t>
  void set_data(data_t data){
    std::get<index>(columns).set_data(data);
  }
};

template <typename... col_types>
struct table {

};

#endif