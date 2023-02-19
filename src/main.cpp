#include <fmt/core.h>

#include <iostream>

#include "arg_reader.h"
#include "column.h"
#include "commands.h"
#include "parser.h"
#include "table.h"

int main() {
  parser p = parser();
  p.handle_user_input();
  row<column<integral>, column<numeric>> new_row = row<column<integral>, column<numeric>>(5, 25.0);
  fmt::print("{} - {}\n", new_row.get<0>(), new_row.get<1>());
}