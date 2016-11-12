#include "gtest/gtest.h"
#include "../matrix_rotation.h"

namespace junk
{
    namespace matrix
    {
        TEST(Matrix, RotateCW_3x3)
        {
            {
                const int N = 3;

                int **matrix = new int*[N];
                for (int i = 0; i < N; ++i) {
                    matrix[i] = new int[N];
                }

                matrix[0][0] = 0; matrix[0][1] = 1; matrix[0][2] = 2;
                matrix[1][0] = 3; matrix[1][1] = 4; matrix[1][2] = 5;
                matrix[2][0] = 6; matrix[2][1] = 7; matrix[2][2] = 8;

                matrix_rotate_cw(matrix, N);

                EXPECT_TRUE(
                    matrix[0][0] == 6 && matrix[0][1] == 3 && matrix[0][2] == 0 &&
                    matrix[1][0] == 7 && matrix[1][1] == 4 && matrix[1][2] == 1 &&
                    matrix[2][0] == 8 && matrix[2][1] == 5 && matrix[2][2] == 2);

                for (int i = 0; i < N; ++i) {
                    delete[] matrix[i];
                }
                delete[] matrix;
            }
        }

        TEST(Matrix, RotateCW_5x5)
        {
            {
                const int N = 5;

                int **matrix = new int*[N];
                for (int i = 0; i < N; ++i) {
                    matrix[i] = new int[N];
                }

                matrix[0][0] = 0; matrix[0][1] = 1; matrix[0][2] = 2; matrix[0][3] = 3; matrix[0][4] = 4;
                matrix[1][0] = 5; matrix[1][1] = 6; matrix[1][2] = 7; matrix[1][3] = 8; matrix[1][4] = 9;
                matrix[2][0] = 10; matrix[2][1] = 11; matrix[2][2] = 12; matrix[2][3] = 13; matrix[2][4] = 14;
                matrix[3][0] = 15; matrix[3][1] = 16; matrix[3][2] = 17; matrix[3][3] = 18; matrix[3][4] = 19;
                matrix[4][0] = 20; matrix[4][1] = 21; matrix[4][2] = 22; matrix[4][3] = 23; matrix[4][4] = 24;

                matrix_rotate_cw(matrix, N);

                EXPECT_TRUE(
                    matrix[0][0] == 20 && matrix[0][1] == 15 && matrix[0][2] == 10 && matrix[0][3] == 5 && matrix[0][4] == 0 &&
                    matrix[1][0] == 21 && matrix[1][1] == 16 && matrix[1][2] == 11 && matrix[1][3] == 6 && matrix[1][4] == 1 &&
                    matrix[2][0] == 22 && matrix[2][1] == 17 && matrix[2][2] == 12 && matrix[2][3] == 7 && matrix[2][4] == 2 &&
                    matrix[3][0] == 23 && matrix[3][1] == 18 && matrix[3][2] == 13 && matrix[3][3] == 8 && matrix[3][4] == 3 &&
                    matrix[4][0] == 24 && matrix[4][1] == 19 && matrix[4][2] == 14 && matrix[4][3] == 9 && matrix[4][4] == 4
                    );

                for (int i = 0; i < N; ++i) {
                    delete[] matrix[i];
                }
                delete[] matrix;
            }
        }
    }
}