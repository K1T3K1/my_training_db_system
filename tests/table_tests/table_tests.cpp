#include <gtest/gtest.h>
#include "table/table.h"

#include <string>

TEST(RowTests, RowReturnsValidData) {
  constexpr int value_int{5};
  constexpr float value_float{25.0};
  std::string value_string{"string_sample"};

  Row<Column<int>, Column<float>, Column<std::string>> test_row{value_int, value_float, value_string};
  test_row.set_data<0>(value_int);
  test_row.set_data<1>(value_float);
  test_row.set_data<2>(value_string);

  ASSERT_EQ(test_row.get<0>(), value_int);
  ASSERT_EQ(test_row.get<1>(), value_float);
  ASSERT_EQ(test_row.get<2>(), value_string);
}
