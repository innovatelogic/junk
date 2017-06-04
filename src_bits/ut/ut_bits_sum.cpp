#include "../bits_lib.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace swap_no_tmp
    {
        TEST(Bits, SwapNoTmp)
        {
            {
                int a = 10;
                int b = 20;
                
                var_swap_no_tmp<int>(a, b);

                EXPECT_EQ(a, 20);
                EXPECT_EQ(b, 10);
            }

            {
                int a = 20;
                int b = 10;

                var_swap_no_tmp<int>(a, b);

                EXPECT_EQ(a, 10);
                EXPECT_EQ(b, 20);
            }

            {
                int a = -10;
                int b = 20;

                var_swap_no_tmp<int>(a, b);

                EXPECT_EQ(a, 20);
                EXPECT_EQ(b, -10);
            }

            {
                int a = 10;
                int b = -20;

                var_swap_no_tmp<int>(a, b);

                EXPECT_EQ(a, -20);
                EXPECT_EQ(b, 10);
            }
        }

        TEST(Bits, SwapNoTmp_Bits)
        {
            {
                int a = 10;
                int b = 20;

                var_swap_no_tmp_bits<int>(a, b);

                EXPECT_EQ(a, 20);
                EXPECT_EQ(b, 10);
            }

            {
                int a = 20;
                int b = 10;

                var_swap_no_tmp_bits<int>(a, b);

                EXPECT_EQ(a, 10);
                EXPECT_EQ(b, 20);
            }

            {
                int a = -10;
                int b = 20;

                var_swap_no_tmp_bits<int>(a, b);

                EXPECT_EQ(a, 20);
                EXPECT_EQ(b, -10);
            }

            {
                int a = 10;
                int b = -20;

                var_swap_no_tmp_bits<int>(a, b);

                EXPECT_EQ(a, -20);
                EXPECT_EQ(b, 10);
            }
        }
    }
}