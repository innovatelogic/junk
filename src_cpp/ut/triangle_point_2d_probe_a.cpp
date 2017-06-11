#include "../cpp.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace triangle_point_2d_probe_a
    {
        TEST(Math, TrianglePoint_2d_probe)
        {
            const float a[2] = { 1.f, 1.f };
            const float b[2] = { 4.f, 2.f };
            const float c[2] = { 2.f, 4.f };

            EXPECT_TRUE(TestPointInTriangle2d<void>(a[0], a[1], b[0], b[1], c[0], c[1], 2.f, 2.f));
            EXPECT_TRUE(TestPointInTriangle2d<void>(a[0], a[1], b[0], b[1], c[0], c[1], a[0], a[1]));
            EXPECT_TRUE(TestPointInTriangle2d<void>(a[0], a[1], b[0], b[1], c[0], c[1], b[0], b[1]));
            EXPECT_TRUE(TestPointInTriangle2d<void>(a[0], a[1], b[0], b[1], c[0], c[1], c[0], c[1]));

            EXPECT_FALSE(TestPointInTriangle2d<void>(a[0], a[1], b[0], b[1], c[0], c[1], 1.f, 2.f));
            EXPECT_FALSE(TestPointInTriangle2d<void>(a[0], a[1], b[0], b[1], c[0], c[1], 3.f, 1.f));
            EXPECT_FALSE(TestPointInTriangle2d<void>(a[0], a[1], b[0], b[1], c[0], c[1], 4.f, 3.f));
        }
    }
}
