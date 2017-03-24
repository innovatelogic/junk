#pragma once

namespace junk
{
    namespace merge_sort_probe_a
    {
        template<typename T>
        void merge(int *dest, int *a1, int *a2, int n1, int n2)
        {
            if (!dest || !a1 || !a2) {
                return;
            }

            int d_idx = 0;
            int n1_idx = 0;
            int n2_idx = 0;

            while (n1_idx < n1 && n2_idx < n2) {
                dest[d_idx++] = (a1[n1_idx] <= a2[n2_idx]) ? a1[n1_idx++] : a2[n2_idx++];
            }

            if (n1_idx < n1) {
                for (int i = n1_idx; i < n1; ++i) {
                    dest[d_idx++] = a1[i];
                }
            }

            if (n2_idx < n2) {
                for (int i = n2_idx; i < n2; ++i) {
                    dest[d_idx++] = a2[i];
                }
            }
        }

        template<typename T>
        void merge_sort(int *arr, int start, int len, int *tmp)
        {
            if (!arr || !tmp) {
                return;
            }

            if (len <= 1) {
                return;
            }

            if (len == 2)
            {
                if (arr[start] > arr[start + 1]) {
                    std::swap(arr[start], arr[start + 1]);
                }
                return;
            }

            merge_sort<T>(arr, start, len / 2, tmp);
            merge_sort<T>(arr, start + len / 2, len - len / 2, tmp);

            merge<T>(tmp + start, arr + start, arr + start + len / 2, len / 2, len - len / 2);

            memcpy(static_cast<void*>(arr + start), static_cast<void*>(tmp + start), len * sizeof(int));

        }
    }
}