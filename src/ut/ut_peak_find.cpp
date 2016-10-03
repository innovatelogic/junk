#include "../peak_finding.h"
#include <gtest/gtest.h>

namespace junk
{

    TEST(PeakFind, 1D_array)
    {
        int ipeak = 0;

        std::vector<int> arr = {};
        EXPECT_EQ(PeakFind(arr, ipeak), false);

        arr = {0};
        EXPECT_EQ(PeakFind(arr, ipeak), true);
        EXPECT_EQ(ipeak, 0);

        arr = { 0, 1 };
        EXPECT_EQ(PeakFind(arr, ipeak), true);
        EXPECT_EQ(ipeak, 1);

        arr = { 0, 1, 2, 3, 4, 5, 6 };
        EXPECT_EQ(PeakFind(arr, ipeak), true);
        EXPECT_EQ(ipeak, 6);

        arr = { 6, 5, 4, 3, 2, 1, 0 };
        EXPECT_EQ(PeakFind(arr, ipeak), true);
        EXPECT_EQ(ipeak, 6);

        arr = { 0, 0, 0, 0, 0, 1, 1, 0, 0 };
        EXPECT_EQ(PeakFind(arr, ipeak), true);
        EXPECT_EQ(ipeak, 1);

        arr = { 0, 0, 1, 1, 0, 0, 0, 0, 0 };
        EXPECT_EQ(PeakFind(arr, ipeak), true);
        EXPECT_EQ(ipeak, 1);
    }
}