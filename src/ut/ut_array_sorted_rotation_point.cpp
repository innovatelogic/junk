#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace array_rotation_point
    {
        TEST(Array, RotationPoint_probe_a)
        {
            {
                int data[] = { 22, 25, 3, 7, 9, 15, 20 };
                int len = sizeof(data) / sizeof(int);

                EXPECT_EQ(2, get_array_rotation_point<void>(data, 0, len - 1, len));
            }

            {
                int data[] = { 3, 7, 9, 15, 20, 22, 25 };
                int len = sizeof(data) / sizeof(int);

                EXPECT_EQ(0, get_array_rotation_point<void>(data, 0, len - 1, len));
            }

            {
                int data[] = { 9, 15, 20, 22, 25, 3, 7,};
                int len = sizeof(data) / sizeof(int);

                EXPECT_EQ(5, get_array_rotation_point<void>(data, 0, len - 1, len));
            }
        }

        TEST(Array, SearchRotationArr_probe_a)
        {
            {
                int data[] = { 22, 25, 3, 7, 9, 15, 20 };
                int len = sizeof(data) / sizeof(int);

                EXPECT_EQ(5, binary_search_rotated<void>(data, len, 15));
            }

            {
                int data[] = { 3, 7, 9, 15, 20, 22, 25 };
                int len = sizeof(data) / sizeof(int);

                EXPECT_EQ(5, binary_search_rotated<void>(data, len, 22));
            }

            {
                int data[] = { 9, 15, 20, 22, 25, 3, 7, };
                int len = sizeof(data) / sizeof(int);

                EXPECT_EQ(1, binary_search_rotated<void>(data, len, 15));
            }

            {
                int data[] = { 25, 3, 7, 9, 15, 20, 22 };
                int len = sizeof(data) / sizeof(int);

                EXPECT_EQ(0, binary_search_rotated<void>(data, len, 25));
            }

            {
                int data[] = { 7, 9, 15, 20, 22, 25, 3 };
                int len = sizeof(data) / sizeof(int);

                EXPECT_EQ(6, binary_search_rotated<void>(data, len, 3));

                EXPECT_EQ(-1, binary_search_rotated<void>(data, len, 30));
            }
        }
    }
}