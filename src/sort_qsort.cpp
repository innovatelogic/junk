#include "sort_qsort.h"

namespace junk
{
    namespace sort_qsort
    {
        void QSortImpl(std::vector<int> &in, size_t start, size_t length)
        {
            if (length < 2) { return; }

            size_t pivotIndex = start + length / 2;
            size_t end = start + length;
            size_t curr = start;
            int pivotValue = in[pivotIndex];

            std::swap(in[pivotIndex], in[--end]);

            while (curr < end)
            {
                if (in[curr] < pivotValue){
                    curr++;
                }
                else{
                    std::swap(in[curr], in[--end]);
                }
            }

            std::swap(in[end], in[start + length - 1]);

            size_t llength = end - start;
            size_t rlength = length - llength - 1;

            if (llength > 1) {
                QSortImpl(in, start, llength);
            }

            if (rlength > 1) {
                QSortImpl(in, end + 1, rlength);
            }
        }

        void QSort(std::vector<int> &in)
        {
            if (in.size() > 1)
            {
                QSortImpl(in, 0, in.size());
            }
        }
    }
}