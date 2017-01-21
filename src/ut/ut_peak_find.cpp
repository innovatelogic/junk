#include "../junk.h"
#include <gtest/gtest.h>

namespace junk
{
    void setup_arr(int **&arr, int rows, int cols)
    {
        arr = new int*[rows];
        for (int i = 0; i < rows; i++) {
            arr[i] = new int[cols];
        }
    }

    void clear(int **&arr, int rows)
    {
        for (int i = 0; i < rows; i++) {
            delete [] arr[i];
        }
        delete [] arr;
    }

    TEST(PeakFind, 1D)
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

    TEST(PeakFind, 2D)
    {
        #define A(i, j) arr[i][j]
        int ipeak = 0;
        int **arr = nullptr;

        { 
            const int N = 4; // rows
            const int M = 4; // cols

            setup_arr(arr, N, M);

            A(0, 0) = 0; A(0, 1) = 0; A(0, 2) = 0; A(0, 3) = 0;
            A(1, 0) = 0; A(1, 1) = 0; A(1, 2) = 0; A(1, 3) = 5;
            A(2, 0) = 0; A(2, 1) = 0; A(2, 2) = 3; A(2, 3) = 4;
            A(3, 0) = 0; A(3, 1) = 0; A(3, 2) = 0; A(3, 3) = 0;

            EXPECT_EQ(PeakFind2d(arr, N, M, ipeak), true);
            EXPECT_EQ(ipeak, 5);

            clear(arr, N);
        }

        {
            
            const int N = 4;
            const int M = 4;

            setup_arr(arr, N, M);

            A(0, 0) = 0; A(0, 1) = 0; A(0, 2) = 0; A(0, 3) = 0;
            A(1, 0) = 6; A(1, 1) = 5; A(1, 2) = 0; A(1, 3) = 0;
            A(2, 0) = 7; A(2, 1) = 4; A(2, 2) = 3; A(2, 3) = 0;
            A(3, 0) = 0; A(3, 1) = 0; A(3, 2) = 0; A(3, 3) = 0;

            EXPECT_EQ(PeakFind2d(arr, N, M, ipeak), true);
            EXPECT_EQ(ipeak, 7);

            clear(arr, N);
        }

        {
            const int N = 4; // rows
            const int M = 5; // cols
            
            setup_arr(arr, N, M);

            A(0, 0) = 0; A(0, 1) = 0; A(0, 2) = 0; A(0, 3) = 0; A(0, 4) = 0;
            A(1, 0) = 6; A(1, 1) = 5; A(1, 2) = 0; A(1, 3) = 0; A(1, 4) = 0;
            A(2, 0) = 7; A(2, 1) = 4; A(2, 2) = 3; A(2, 3) = 0; A(2, 4) = 0;
            A(3, 0) = 0; A(3, 1) = 0; A(3, 2) = 0; A(3, 3) = 0; A(3, 4) = 0;

            EXPECT_EQ(PeakFind2d(arr, N, M, ipeak), true);
            EXPECT_EQ(ipeak, 7);

            clear(arr, N);
        }

        {
            const int N = 4; // rows
            const int M = 5; // cols

            setup_arr(arr, N, M);

            A(0, 0) = 0; A(0, 1) = 0; A(0, 2) = 0; A(0, 3) = 0; A(0, 4) = 0;
            A(1, 0) = 0; A(1, 1) = 5; A(1, 2) = 0; A(1, 3) = 5; A(1, 4) = 6;
            A(2, 0) = 0; A(2, 1) = 0; A(2, 2) = 3; A(2, 3) = 4; A(2, 4) = 7;
            A(3, 0) = 0; A(3, 1) = 0; A(3, 2) = 0; A(3, 3) = 0; A(3, 4) = 0;

            EXPECT_EQ(PeakFind2d(arr, N, M, ipeak), true);
            EXPECT_EQ(ipeak, 7);

            clear(arr, N);
        }
    }
}