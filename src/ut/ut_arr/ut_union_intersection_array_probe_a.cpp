#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace union_intersection_array_probe_a
    {
        TEST(Array, UnionArray_probe_a)
        {
            {
                int A[] = { 0, 1, 4, 6, 7 };
                int B[] = { 4, 5, 10, 11 };

                std::vector<int> out;
                Union<int>(A, sizeof(A) / sizeof(int), B, sizeof(B) / sizeof(int), out);

                EXPECT_EQ(out, std::vector<int>({ 0, 1, 4, 5, 6, 7, 10, 11 }));
            }
        }

        TEST(Array, IntersectionArray_probe_a)
        {
            {
                int A[] = { 0, 1, 4, 6, 7, 11 };
                int B[] = { 4, 5, 10, 11 };

                std::vector<int> out;
                Intersection<int>(A, sizeof(A) / sizeof(int), B, sizeof(B) / sizeof(int), out);

                EXPECT_EQ(out, std::vector<int>({ 4, 11 }));
            }
        }
    }
}