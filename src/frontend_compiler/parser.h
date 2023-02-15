#ifndef PARSER_H_
#define PARSER_H_

#include <map>
#include <string>
#include <span>

#include "commands.h"
struct parser {
  static void handle_user_input();
};

struct query {
  using command = commands::command_types;
  command _command;
  std::span<std::string> _args;
};

#endif