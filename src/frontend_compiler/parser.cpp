#include "parser.h"

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
  std::vector<query> parsed_queries = std::vector<query>();
  query parsed_query{command::NONE, std::span<std::string_view>()};
  for(auto& word : stringed_query){
    if(parsed_query._command){return;}
  }
}