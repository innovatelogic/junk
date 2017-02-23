#pragma once

#include "defexport.h"
#include <vector>
#include <algorithm>

namespace junk
{
    //----------------------------------------------------------------------------------------------
    template<class T> 
    JUNK_EXPORT void merge(std::vector<T> &arr, size_t left, size_t mid, size_t right)
    {
        size_t n1 = mid - left + 1;
        size_t n2 = right - mid;

        std::vector<T> L;
        std::vector<T> R;

        for (size_t i = 0; i < n1; i++) {
            L.push_back(left + i);
        }
        for (size_t j = 0; j < n1; j++) {
            R.push_back(mid + 1 + j);
        }

        size_t i = 0;
        size_t j = 0;
        size_t k = left;

        while (i < n1 && j < n2)
        {
            if (L[i] < R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            arr[k] = L[i];
            k++;
            i++;
        }

        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    //----------------------------------------------------------------------------------------------
    template<class T>
    JUNK_EXPORT void merge_sort(std::vector<T> &arr, size_t l, size_t r)
    {
        if (l < r)
        {
            const size_t mid = l + (r - l) / 2;

            merge_sort(arr, l, mid);
            merge_sort(arr, mid + 1, r);
            merge(arr, l, mid, r);
        }
    }
}