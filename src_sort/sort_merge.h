#pragma once

#include "defexport.h"
#include <vector>

namespace junk
{
    namespace sort_merge
    {
        template<typename>
        void Merge(int *array, int *buffer, size_t left, size_t mid, size_t right)
        {
            size_t lind = left;
            size_t rind = mid + 1;
            size_t dind = left;

            while (lind <= mid && rind <= right)
            {
                if (array[lind] < array[rind])
                {
                    buffer[dind] = array[lind];
                    dind++;
                    lind++;
                }
                else
                {
                    buffer[dind] = array[rind];
                    dind++;
                    rind++;
                }
            }

            if (lind <= mid) {
                for (size_t i = lind; i <= mid; i++) {
                    buffer[dind++] = array[i];
                }
            }
            if (rind <= right) {
                for (size_t i = rind; i <= right; i++) {
                    buffer[dind++] = array[i];
                }
            }

            for (size_t i = left; i <= right; ++i) {
                array[i] = buffer[i];
            }
        }

        template<typename>
        void MergeSortImpl(int *array, int *buffer, size_t left, size_t right)
        {
            if (left < right) 
            {
                size_t mid = (left + (right - left) / 2);
                MergeSortImpl<void>(array, buffer, left, mid);
                MergeSortImpl<void>(array, buffer, mid + 1, right);

                Merge<void>(array, buffer, left, mid, right);
            }
        }

        template<typename>
        SORT_LIB_EXPORT void MergeSort(int *array, int *buffer, size_t size_n)
        {
            if (!array || !buffer || size_n == 0) {
                return;
            }

            MergeSortImpl<void>(array, buffer, 0, size_n - 1);
        }

    }

}