#ifndef PARSER_H_
#define PARSER_H_

#include <map>
#include <span>
#include <string>
#include <vector>

#include "commands.h"

struct query {
  query(command _command, std::span<std::string_view> _args) : _command(_command), _args(_args){};
  query() : _command(command::NONE), _args(std::span<std::string_view>()) {}
  command _command;
  std::span<std::string_view> _args;

  constexpr bool validate_query();
};

struct parser {
  std::vector<query> parsed_queries;
  void handle_user_input();
  void create_expressions();
};

#endif