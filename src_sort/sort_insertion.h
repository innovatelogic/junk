
#pragma once

#include <vector>

namespace junk
{
    namespace sort_insertion
    {
        template<typename>
        void InsertionSort(std::vector<int> &in)
        {
            for (size_t i = 1; i < in.size(); i++)
            {
                int key = in[i];
                
                int j = i - 1;
                for (; j >= 0 && in[j] > key; j--)
                {
                    in[j + 1] = in[j];
                }

                in[j + 1] = key;
            }
        }
    }
}