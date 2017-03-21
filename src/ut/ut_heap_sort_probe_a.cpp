#include "junk.h"
#include <gtest/gtest.h>


namespace junk
{
    namespace heap_sort_probe_a
    {
        TEST(Heap, HeapSort_probe_a)
        {
            Heap heap;

            int arr[] = { 9, 8, 7, 6, 5, 4, 3, 0, 2, 1 };
            for (int i = 0; i < sizeof(arr) / sizeof(int); i++){
                heap.insert(arr[i]);
            }

            heap.heap_sort();

            const int *a = heap.array();

            for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
            {
                EXPECT_EQ(*(a + i), i);
            }
        }
    }
}