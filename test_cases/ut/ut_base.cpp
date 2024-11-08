#include "test_class.h"

#include <gtest/gtest.h>

TEST(TestClass, expect_one)
{
    junk::TestClass test_class;
    EXPECT_TRUE(1 == test_class.one());
}