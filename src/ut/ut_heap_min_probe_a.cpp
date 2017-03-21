#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
	namespace heap_min_probe_a
    {
        TEST(Heap, MinHeap_probe_a)
        {
            //int tasks[] = { 1, 2, 2, 6, 8, 3, 1 };
            int tasks[] = { 6, 5, 4, 3, 2, 1, 0 };
            HeapMin heap;
            
            for (int i = 0; i < sizeof(tasks) / sizeof(int); ++i) {
                heap.insert(tasks[i]);
            }
        }

        TEST(Heap, MinHeap_calc_task_max_min)
        {
            int tasks[] = { 2, 2, 3, 7, 1 };
            
            HeapMin heap;
            heap.insert(0); // add worker 1
            heap.insert(0); // add worker 2

            const int SIZE = sizeof(tasks) / sizeof(int);
            std::sort(tasks, tasks + SIZE);

            for (int i = SIZE - 1; i >= 0; --i) {
                heap.increase_min(tasks[i]);
            }
            EXPECT_EQ(heap.min(), 7);
            EXPECT_EQ(heap.max(), 8);
        }
    }
}