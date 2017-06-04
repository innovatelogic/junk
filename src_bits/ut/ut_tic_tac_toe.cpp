#include "../bits_lib.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace tic_tac_toe
    {
        bool isEqual(const int a[3][3], const int b[3][3])
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (a[i][j] != b[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        TEST(Bits, TicTacToe_ConvertField)
        {
            {
                const int field[3][3] = {
                    { 0, 1, 0 },
                    { 1, 2, 1 },
                    { 0, 2, 0 },
                };

                int desc = convert_field_3x3<int>(field);

                int out_field[3][3];

                tic_tac_toe::convert_int_to_field<int>(desc, out_field);

                EXPECT_TRUE(isEqual(field, out_field));
            }

            {
                const int field[3][3] = {
                    { 1, 1, 1 },
                    { 1, 0, 1 },
                    { 2, 1, 2 },
                };

                int desc = convert_field_3x3<int>(field);

                int out_field[3][3];

                tic_tac_toe::convert_int_to_field<int>(desc, out_field);

                EXPECT_TRUE(isEqual(field, out_field));
            }
        }

        TEST(Bits, TicTacToe_checkWin)
        {
            // by rows
            for (int k = 0; k < 3; k++) // variations
            {
                for (int i = 0; i < 3; i++) // rows
                {
                    int field[3][3] = {
                             { 0, 0, 0 },
                             { 0, 0, 0 },
                             { 0, 0, 0 }
                    };

                    for (int j = 0; j < 3; j++){
                        field[i][0] = field[i][1] = field[i][2] = k;
                    }

                    int desc = convert_field_3x3<int>(field);

                    int out_field[3][3];
                    tic_tac_toe::convert_int_to_field<int>(desc, out_field);
                    EXPECT_TRUE(isEqual(field, out_field));

                    EXPECT_EQ((int)checkWin_3x3<int>(out_field), k);
                }
            }

            // by cols
            for (int k = 0; k < 3; k++) // variations
            {
                for (int i = 0; i < 3; i++) // rows
                {
                   int field[3][3] = {
                        { 0, 0, 0 },
                        { 0, 0, 0 },
                        { 0, 0, 0 }
                    };

                    for (int j = 0; j < 3; j++) {
                        field[0][i] = field[1][i] = field[2][i] = k;
                    }

                    int desc = convert_field_3x3<int>(field);

                    int out_field[3][3];
                    tic_tac_toe::convert_int_to_field<int>(desc, out_field);
                    EXPECT_TRUE(isEqual(field, out_field));

                    EXPECT_EQ((int)checkWin_3x3<int>(out_field), k);
                }
            }

            // diagonals
            for (int k = 0; k < 3; k++) // variations
            {
                {
                    int field[3][3] = {
                        { k, 0, 0 },
                        { 0, k, 0 },
                        { 0, 0, k }
                    };

                    int desc = convert_field_3x3<int>(field);

                    int out_field[3][3];
                    tic_tac_toe::convert_int_to_field<int>(desc, out_field);
                    EXPECT_TRUE(isEqual(field, out_field));

                    EXPECT_EQ((int)checkWin_3x3<int>(out_field), k);
                }

                // second
                {
                    int field[3][3] = {
                        { 0, 0, k },
                        { 0, k, 0 },
                        { k, 0, 0 }
                    };

                    int desc = convert_field_3x3<int>(field);

                    int out_field[3][3];
                    tic_tac_toe::convert_int_to_field<int>(desc, out_field);
                    EXPECT_TRUE(isEqual(field, out_field));

                    EXPECT_EQ((int)checkWin_3x3<int>(out_field), k);
                }
            }
        }
    }
}