#include "parser.h"

#include <fmt/core.h>

#include <sstream>
#include <vector>

#include "arg_reader.h"
#include "commands.h"

void parser::handle_user_input() {
  std::stringstream user_input = std::stringstream(ArgReader::read_args());
  std::string buffer;
  std::vector<std::string> stringed_query = std::vector<std::string>();
  while (user_input >> buffer) {
    stringed_query.push_back(buffer);
  }

  Query parsed_query{get_command_from_string(stringed_query[0]), std::span<std::string>()};
  if (parsed_query._command == Command::NONE) {
    fmt::print(
        "Query must begin with a keyword(i.e. {Command::SELECT}),\n instead received {parsed_queries[0]}\n");
    return;
  }

  std::vector<Query> parsed_queries = std::vector<Query>();
  stringed_query.erase(stringed_query.begin());
  std::vector<std::string> _args_vector;
  for (auto& word : stringed_query) {
    if (get_command_from_string(word) == Command::NONE) {
      _args_vector.push_back(word);
    } else if (auto _command = get_command_from_string(word);
               _command != Command::NONE && parsed_query.validate_query()) {
      parsed_query._args = std::span<std::string>(_args_vector);
      parsed_queries.push_back(parsed_query);
      parsed_query._command = _command;
    } else {
      fmt::print("Invalid query");
      return;
    }
  }
}

constexpr bool Query::validate_query() {
  if (_command == Command::NONE || _args.empty()) {
    return false;
  }
  return true;
}