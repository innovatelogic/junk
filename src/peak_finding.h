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

    template<class T>
    T PeakFind2dImpl(T **arr, size_t rows, int lbound, int rbound)
    {
        int mid = lbound + (rbound - lbound) / 2;

        // find a global maximum of column 'mid'
        size_t i = 0;
        size_t i_max = 0;
        T mx = arr[i][mid];
        for (i = 1; i < rows; i++)
        {
            T &val = arr[i][mid];
            if (val >= mx)
            {
                mx = val;
                i_max = i;
            }
        }

        // compare left & right neighbors
        int lhs = mid - 1;
        if (lhs >= lbound && arr[i_max][lhs] > arr[i_max][mid])
        {
            return PeakFind2dImpl(arr, rows, lbound, mid - 1);
        }

        int rhs = mid + 1;
        if (rhs < rbound && arr[i_max][rhs] > arr[i_max][mid]) 
        {
            return PeakFind2dImpl(arr, rows, mid + 1, rbound);
        }

        return arr[i_max][mid];
    }

    template<class T>
    bool PeakFind2d(T **arr, size_t rows, size_t cols, T &out)
    {
        if (!arr || cols == 0 || rows == 0) {
            return false;
        }

        out = PeakFind2dImpl(arr, rows, 0, cols);

        return true;
    }
}