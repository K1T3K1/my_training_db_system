#include "parser.h"

#include <fmt/core.h>

#include <sstream>
#include <vector>

#include "arg_reader.h"
#include "commands.h"

void parser::handle_user_input() {
  std::stringstream user_input = std::stringstream(arg_reader::read_args());
  std::string buffer;
  std::vector<std::string> stringed_query = std::vector<std::string>();
  while (user_input >> buffer) {
    stringed_query.push_back(buffer);
  }

  query parsed_query{get_command_from_string(stringed_query[0]), std::span<std::string>()};
  if (parsed_query._command == command::NONE) {
    fmt::print(
        "Query must begin with a keyword(i.e. {command::SELECT}),\n instead received {parsed_queries[0]}\n");
    return;
  }

  std::vector<query> parsed_queries = std::vector<query>();
  stringed_query.erase(stringed_query.begin());
  std::vector<std::string> _args_vector;
  for (auto& word : stringed_query) {
    if (get_command_from_string(word) == NONE) {
      _args_vector.push_back(word);
    } else if (auto _command = get_command_from_string(word);
               _command != NONE && parsed_query.validate_query()) {
      parsed_query._args = std::span<std::string>(_args_vector);
      parsed_queries.push_back(parsed_query);
      parsed_query._command = _command;
    } else {
      fmt::print("Invalid query");
      return;
    }
  }
}

constexpr bool query::validate_query() {
  if (_command == command::NONE || _args.empty()) {
    return false;
  }
  return true;
}