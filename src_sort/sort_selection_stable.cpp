#include "sort_selection_stable.h"
#include <assert.h>

namespace junk
{
    namespace sort_selection_stable
    {
        size_t FindMinIndex(std::vector<std::pair<int, int>> &in, size_t start)
        {
            size_t minIndex = start;

            for (size_t i = start + 1; i < in.size(); ++i)
            {
                if (in[i].first < in[minIndex].first)
                { 
                    minIndex = i;
                }
            }
            return minIndex;
        }

        void ShiftArray(std::vector<std::pair<int, int>> &in, size_t start, size_t last)
        {
            assert(last < in.size());

            while (start < last)
            {
                in[last] = in[last - 1];
                last--;
            }
        }

        void SortSelectionStableImpl(std::vector<std::pair<int, int>> &in)
        {
            for (size_t i = 0; i < in.size() - 1; ++i)
            {
                size_t min_idx = FindMinIndex(in, i);
                
                if (min_idx != i)
                {
                    std::pair<int, int> tmp = in[min_idx];
                    ShiftArray(in, i, min_idx);
                    in[i] = tmp;
                }
            }
        }

        void SortSelectionStable(std::vector<std::pair<int, int>> &in)
        {
            if (in.size() > 1)
            {
                SortSelectionStableImpl(in);
            }
        }
    }
}