#include <gtest/gtest.h>
#include "math_kernel.c"

class ElementTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Set up any variables or objects needed for the tests.
  }

  void TearDown() override {
    // Clean up any resources used by the tests.
  }
};

TEST_F(ElementTest, TestGenerateRandomNumber) {
  // Test the generate_random_number function.
  int result = generate_random_number(1, 10);
  EXPECT_GE(result, 1);
  EXPECT_LE(result, 10);
}

TEST_F(ElementTest, TestGenerateExpression) {
  // Test the generate_expression function.
  Operation op;
  init_operation(&op, 10, "+-", 2, 1, 0);
  char expression[MAX_BUFFER];
  generate_expression(&op, expression);
  // Check that the expression has the expected format.
}

// Add more test cases as needed.

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}