#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace histogram_max_rect_probe_a
    {
        TEST(Array, MaxRectHistogram_probe_a)
        {
            {
                /*
                          *
                      * * *   *
                    * * * * * *
                    - - - - - -
                    0 1 2 3 4 5
                */

                int arr[] = { 0, 2, 2, 3, 1, 2 };
                int size = sizeof(arr) / sizeof(int);
                EXPECT_EQ(get_max_rect<int>(arr, size), 6);
            }

            {
                /*
                *
                * * *   *
                * * *   * *
                - - - - - -
                0 1 2 3 4 5
                */

                int arr[] = { 3, 2, 2, 0, 1, 2 };
                int size = sizeof(arr) / sizeof(int);
                EXPECT_EQ(get_max_rect<int>(arr, size), 6);
            }
        }
    }
}