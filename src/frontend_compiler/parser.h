#ifndef PARSER_H_
#define PARSER_H_

#include <map>
#include <span>
#include <string>
#include <vector>

#include "commands.h"

struct Query {
  Query(Command _command, std::span<std::string> _args) : _command(_command), _args(_args){};
  Query() : _command(Command::NONE), _args(std::span<std::string>()) {}
  Command _command;
  std::span<std::string> _args;

  constexpr bool validate_query();
};

struct parser {
  void handle_user_input();
};

#endif