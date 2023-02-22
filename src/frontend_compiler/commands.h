#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <boost/algorithm/string.hpp>
#include <map>
#include <string>
#include <variant>
#include <type_traits>
#include <array>

enum class Command { SELECT, FROM, WHERE, JOIN, UNION, CREATE, ALTER, DROP, INSERT, UPDATE, DELETE, NONE };

constexpr auto get_number_from_command(Command _command){return std::to_underlying(_command);}
constexpr auto get_command_count() { return get_number_from_command(Command::NONE);}
const std::array<std::pair<std::string, Command>, get_command_count()> string_command{{
    {"SELECT", Command::SELECT}, {"FROM", Command::FROM},     {"WHERE", Command::WHERE},  {"JOIN", Command::JOIN},
    {"UNION", Command::UNION},   {"CREATE", Command::CREATE}, {"ALTER", Command::ALTER},  {"DROP", Command::DROP},
    {"INSERT INTO", Command::INSERT}, {"UPDATE", Command::UPDATE}, {"DELETE", Command::DELETE}}};

inline auto get_command_from_string(const std::string user_input) {
  std::string user_input_copy = user_input;
  boost::to_upper(user_input_copy);
  auto predicate = [&user_input_copy](std::pair<std::string, Command> comparator){return comparator.first.compare(user_input_copy) == 0;};
  if (auto _command = std::find_if(string_command.cbegin(), string_command.cend(), predicate); _command != string_command.end()) {
    return (*_command).second;
  }
  return Command::NONE;
}

#endif