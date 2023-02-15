#include "parser.h"

#include <sstream>
#include <vector>

#include "arg_reader.h"
#include "commands.h"

void parser::handle_user_input() {
  std::stringstream user_input = std::stringstream(arg_reader::read_args());
  std::string buffer;
  std::vector<std::string> query = std::vector<std::string>();
  while (user_input >> buffer) {
    query.push_back(buffer);
  }
}