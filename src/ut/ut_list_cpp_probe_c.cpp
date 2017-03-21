#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_cpp_probe_c
    {
        TEST(Lists, Build_ArrayA_over_ArrayB)
        {
            List list;

            const int SIZE = 4;
            int arrayA[] = { 12, 24, 8, 32 };
            int arrayB[] = { 13, 25, 32, 11 };

            for (int i = 0; i < SIZE; ++i){
                list.insert_value(arrayA[i], MASK_A);
            }
            for (int i = 0; i < SIZE; ++i) {
                list.insert_value(arrayB[i], MASK_B);
            }

            std::vector<int> A, B;
            list.shuffle(A, B);

            EXPECT_TRUE(A.size() == SIZE && B.size() == SIZE);
            
            int countA = 0;
            int countB = 0;

            for (int i = 0; i < SIZE; ++i) 
            {
                if (A[i] == B[i]) {
                    continue;
                }

                if (A[i] > B[i]){
                    countA++;
                }
                else{
                    countB++;
                }
            }
            EXPECT_TRUE(countA > countB);
        }
    }
}