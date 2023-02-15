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
  query(command _command, std::span<std::string_view> _args) : _command(_command), _args(_args){};
  query() : _command(command::NONE), _args(std::span<std::string_view>()){}
  command _command;
  std::span<std::string_view> _args;
};

#endif