#pragma once
#include <stdlib.h>
#include <stdio.h>
namespace junk
{
    namespace merge_sort_probe_b
    {
        template<typename T>
        void merge(int *data, int *tmp, int l, int llen, int r, int rlen)
        {
            int l_idx = l;
            int r_idx = r;
            int d_idx = l_idx;

            while (l_idx < l + llen && r_idx < r + rlen)
            {
                if (data[l_idx] < data[r_idx]) {
                    tmp[d_idx++] = data[l_idx++];
                }
                else {
                    tmp[d_idx++] = data[r_idx++];
                }
            }

            if (l_idx < l + llen)
            {
                for (int i = l_idx; i < l + llen; ++i) {
                    tmp[d_idx++] = data[i];
                }
            }

            if (r_idx < r + rlen)
            {
                for (int i = r_idx; i < r + rlen; ++i) {
                    tmp[d_idx++] = data[i];
                }
            }
        }

        template<typename T>
        void merge_sort_impl(int *data, int *tmp, int l, int r)
        {
            int size = r - l + 1;

            if (size <= 1) {
                return;
            }

            if (size == 2)
            {
                if (data[r] < data[l]) {
                    std::swap(data[r], data[l]);
                }
                return;
            }

            int mid_idx = ((r - l) / 2) + l;

            merge_sort_impl<T>(data, tmp, l, mid_idx);
            merge_sort_impl<T>(data, tmp, mid_idx + 1, r);

            merge<T>(data, tmp, l, mid_idx - l + 1, mid_idx + 1, r - mid_idx);

            memcpy(static_cast<void*>(data + l), static_cast<void*>(tmp + l), sizeof(int) * (r - l) + 1);
        }

        template<typename T>
        void merge_sort(int *data, int *tmp, int size)
        {
            if (!data || !tmp || size == 0) {
                return;
            }
            merge_sort_impl<T>(data, tmp, 0, size - 1);
        }
    }
}