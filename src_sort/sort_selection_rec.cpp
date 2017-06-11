#include "sort_selection_rec.h"
#include <assert.h>

namespace junk
{
    namespace sort_selection_rec
    {
        //----------------------------------------------------------------------------------------------
        size_t findMinElementIndex(size_t start, std::vector<int> &in)
        {
            assert(start < in.size());

            int min_idx = start;

            for (size_t i = start + 1; i < in.size(); ++i)
            {
                if (in[i] < in[min_idx])
                {
                    min_idx = i;
                }
            }
            return min_idx;
        }

        //----------------------------------------------------------------------------------------------
        void SelectionSortRecImpl(size_t start, std::vector<int> &in)
        {
            if (start == in.size() - 1) {
                return;
            }

            std::swap(in[start], in[findMinElementIndex(start, in)]);
            SelectionSortRecImpl(start + 1, in);
        }

        //----------------------------------------------------------------------------------------------
        void SelectionSortRec(std::vector<int> &in)
        {
            if (in.size() > 1){
                SelectionSortRecImpl(0, in);
            }
        }
    }
}