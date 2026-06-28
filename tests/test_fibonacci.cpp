#include <gtest/gtest.h>

#include "fibonacci.h"

TEST(FibonacciTest, SmallIndices)
{
    EXPECT_EQ(get_fibonacci(0U), 0ULL);
    EXPECT_EQ(get_fibonacci(1U), 1ULL);
    EXPECT_EQ(get_fibonacci(2U), 1ULL);
    EXPECT_EQ(get_fibonacci(3U), 2ULL);
    EXPECT_EQ(get_fibonacci(4U), 3ULL);
    EXPECT_EQ(get_fibonacci(5U), 5ULL);
}

TEST(FibonacciTest, KnownValues)
{
    EXPECT_EQ(get_fibonacci(10U), 55ULL);
    EXPECT_EQ(get_fibonacci(20U), 6765ULL);
    EXPECT_EQ(get_fibonacci(30U), 832040ULL);
}
