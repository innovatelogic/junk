#pragma once
#include <vector>

namespace junk
{
    namespace isertion_sort_probe_a
    {
        template<typename T>
        size_t find_min_index(const std::vector<T> &in, size_t start)
        {
            size_t min_idx = start;
            if (start < in.size())
            {
                for (size_t i = start + 1; i < in.size(); ++i)
                {
                    if (in[min_idx] > in[i]) {
                        min_idx = i;
                    }
                }
            }
            return min_idx;
        }

        template<typename T>
        void isertion_sort(std::vector<T> &in)
        {
            for (size_t i = 0; i < in.size() - 1; ++i)
            {
                size_t min_idx = find_min_index(in, i + 1);
                if ( min_idx > i)
                {
                    int min = in[min_idx];

                    for (size_t j = min_idx; j > i; --j)
                    {
                        in[j] = in[j - 1];
                    }
                    in[i] = min;
                }
            }
        }
    }
}