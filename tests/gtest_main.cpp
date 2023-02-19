#include <gtest/gtest.h>
#include "table_tests/table_tests.cpp"

int main(int argc, char **argv) {
  printf("Running main() from gtest_main.cpp\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();;
}