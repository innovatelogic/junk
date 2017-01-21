
#include <iostream>
#include <gtest/gtest.h>

//----------------------------------------------------------------------------------------------
TEST(TestMath, DummyAddTwoDigit)
{
	int i = 1 + 2;
	EXPECT_EQ(i, 3);
}

//----------------------------------------------------------------------------------------------
TEST(TestMath, DummySubstractTwoDigit)
{
    int i = 1 - 2;
	EXPECT_EQ(i, -1);
}
