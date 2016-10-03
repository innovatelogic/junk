#pragma once

#include <vector>

namespace junk
{
    template<class T>
    T PeakFindImpl(const std::vector<T> &arr, int left = 0, int right = -1)
    {
        const int size = arr.size();

        if (right == -1) {
            right = size;
        }

        // (x - y)/2 + y => x/2 - y/2 + y => x/2 + y/2
        int j = (left + right) / 2;

        if (j - 1 >= 0 && arr[j] < arr[j - 1]) {
            return PeakFindImpl(arr, left, j - 1);
        }
        else if (j + 1 < size && arr[j] < arr[j + 1]) {
            return PeakFindImpl(arr, j + 1, right);
        }
        return arr[j];
    }

    template<class T>
    bool PeakFind(const std::vector<T> &arr, T &out)
    {
        if (arr.empty())
            return false;

        out = PeakFindImpl(arr);

        return true;
    }


}