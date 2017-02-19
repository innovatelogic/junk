#include "sort_selection.h"

namespace junk
{
    namespace selection_sort
    {
        //----------------------------------------------------------------------------------------------
        size_t FindMinimumIndex(std::vector<int> &in, size_t start)
        {
            size_t min_idx = start;

            for (size_t i = start + 1; i < in.size(); i++)
            {
                if (in[i] < in[min_idx])
                {
                    min_idx = i;
                }
            }
            return min_idx;
        }

        //----------------------------------------------------------------------------------------------
        void SelectionSortImpl(std::vector<int> &in)
        {
            for (size_t i = 0; i < in.size() - 1; i++)
            {
                std::swap(in[i], in[FindMinimumIndex(in, i)]);
            }
        }

        //----------------------------------------------------------------------------------------------
        void SelectionSort(std::vector<int> &in)
        {
            if (in.size() > 1)
            {
                SelectionSortImpl(in);
            }
        }
    }
}