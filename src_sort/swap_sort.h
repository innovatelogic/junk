#include <vector>
#include <algorithm>

namespace junk
{
    template<class T>
    void swap_sort(std::vector<T> &arr)
    {
        if (arr.size() > 1)
        {
            const size_t size = arr.size();
            for (size_t i = 1; i < size; ++i)
            {
                int key = i;
                while (key > 0 && arr[key - 1] > arr[key])
                {
                    std::swap(arr[key], arr[key - 1]);
                    key--;
                }
            }
        }
    }
}