#pragma once

#include <vector>

namespace array
{
    namespace array_reverse_inplace
    {
        template<typename T>
        void Reverse(std::vector<T> &arr)
        {
            size_t j = arr.size() - 1;
            size_t i = 0;

            while (i < j)
            {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
    }
}