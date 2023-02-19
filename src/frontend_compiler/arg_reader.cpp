#include "arg_reader.h"

#include <iostream>

std::string ArgReader::read_args() {
  std::cout << "Write query: ";
  std::string string_return;
  std::getline(std::cin, string_return);
  return string_return;
}