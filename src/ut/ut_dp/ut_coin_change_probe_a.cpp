#include "dp.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace coin_change_probe_a
    {
        TEST(Dp, CoinChangeCount_probe_a)
        {
            int arr[] = { 1, 2, 3 };
            int m = sizeof(arr) / sizeof(arr[0]);

            int k = count<int>(arr, m, 4);
        }
    }
}