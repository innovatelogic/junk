#include <gtest/gtest.h>
#include "../heap.h"

namespace junk
{
    //----------------------------------------------------------------------------------------------
    TEST(Heap, HeapFill)
    {
        std::vector<int> arr = { 0, 2, 1, 5, 4, 3, 6 };

        heap::heap<int> _heap(&arr[0], arr.size());

        _heap.heap_sort();

        const int *p_heap = _heap.c_array();
        const int last = _heap.last();

        std::vector<int> res;
        for (int i = 0; i <= last; i++)
        {
            res.push_back(p_heap[i]);
        }
    }
}