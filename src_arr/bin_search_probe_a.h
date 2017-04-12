#pragma once

namespace junk
{
    namespace binary_search_probe_a
    {
        template<typename T>
        int bin_search(int *data, int start, int len, int x)
        {
            if (len == 0) {
                return -1;
            }

            int mid = start + (len / 2);

            if (data[mid] == x) {
                return mid;
            }
            else if (x < data[mid]) {
                return bin_search<T>(data, start, mid - start, x);
            }

            return bin_search<T>(data, mid + 1, (start + len) - (mid + 1), x);
        }
    }
}