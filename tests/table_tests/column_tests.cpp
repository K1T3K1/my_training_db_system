#include <gtest/gtest.h>

#include "table/column.h"

static const char* constraint_error{"Provided data couldn't satisfy column's constraint"};

TEST(ColumnTests, CreateColumnsTest) {
  ASSERT_NO_THROW(ColumnIntegral("column_integral"));
  ASSERT_NO_THROW(ColumnNumeric("column_numeric"));
  ASSERT_NO_THROW(ColumnVarchar("column_varchar;"));
}

TEST(ColumnTests, PositiveNumberConstraintTest) {
  constexpr auto constraint = [](auto arg) { return arg > 0; };
  ColumnIntegral<false, constraint> col_int{"col_int"};
  ColumnNumeric<false, constraint> col_num{"col_float"};
  constexpr auto valid_data = 5;
  constexpr auto invalid_data = -1;
  ASSERT_EQ(col_int->validate_data(valid_data), true);
  ASSERT_EQ(col_num->validate_data(valid_data), true);
  ASSERT_EQ(col_int->validate_data(invalid_data), false);
  ASSERT_EQ(col_int->validate_data(invalid_data), false);
}

TEST(ColumnTests, ModuloTest) {
  constexpr auto constraint = [](auto arg) { return arg % 2 == 0; };
  ColumnIntegral<false, constraint> col_int{"col_int"};
  constexpr auto valid_data = 2;
  constexpr auto invalid_data = 1;
  ASSERT_EQ(col_int->validate_data(valid_data), true);
  ASSERT_EQ(col_int->validate_data(invalid_data), false);
}

TEST(ColumnTests, StringTest){
  constexpr auto constraint = [](auto arg){ return arg[0] == 'A';};
  ColumnVarchar<false, constraint> col_varchar{"col_varchar"};
  char valid_data[] = "Adam";
  char invalid_data[] = "adas";
  ASSERT_EQ(col_varchar->validate_data(valid_data), true);
  ASSERT_EQ(col_varchar->validate_data(invalid_data), false);
}