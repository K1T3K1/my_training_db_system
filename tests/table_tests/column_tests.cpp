#include <gtest/gtest.h>

#include "table/column.h"

static const char* constraint_error{"Provided data couldn't satisfy column's constraint"};

TEST(ColumnConstraintTests, NumPositiveConstrainTest) {
  auto constraint = [](auto arg) { return arg > 0; };
  using col_int = Column<int, false, constraint>;
  using col_float = Column<float, false, constraint>;
  try {
    col_int{-1};
    col_float{-2.5};
    FAIL();
  } catch (const std::invalid_argument& exception) {
    ASSERT_STREQ(constraint_error, exception.what());
  }
  ASSERT_NO_THROW(col_int(1));
  ASSERT_NO_THROW(col_float(2.5));
}

TEST(ColumnConstraintTests, ModuloConstraintTest) {
  auto constraint = [](auto arg) { return (arg % 2) == 0; };
  using col_int = Column<int, false, constraint>;
  try {
    col_int{3};
    FAIL();
  } catch (const std::invalid_argument& exception) {
    ASSERT_STREQ(constraint_error, exception.what());
  }
  ASSERT_NO_THROW(col_int(4));
}

TEST(ColumnConstraintTests, StringConstrainTest) {
  auto constraint = [](auto arg) { return arg[0] == 'A'; };
  using col = Column<std::string, false, constraint>;
  try {
    col{"abc"};
    FAIL();
  } catch (const std::invalid_argument& exception) {
    ASSERT_STREQ(constraint_error, exception.what());
  }
  ASSERT_NO_THROW(col("Abc"));
}