#pragma once

#include <limits>
#include <vector>

namespace junk
{
    namespace coin_change_dp_probe_b
    {
       // template<typename T>
       // void getMinCoinsDenominations();

       template<typename>
        void getMinCoinsDenominations(
            int coins[], int coins_size,
            int R[], int r_size,
            std::vector<int> &out)
        {
            if (R[r_size - 1] == -1) {
                return;
            }

            int start = r_size - 1;
            while (start != 0)
            {
                int j = R[start];
                out.push_back(coins[j]);
                start = start - coins[j];
            }
        }

        /*!
            Bottom up way to count 
            coins input is sorted
            return MAX_VALUE - 1 if solution is not possible
        */
        template<typename>
        int count(int total, int coins[], int n, std::vector<int> &out)
        {
            const int arr_size = total + 1;
            int *T = new int[arr_size]; // array of T[0, 1..total]
            int *R = new int[arr_size]; // array of R[0, 1..total]

            T[0] = 0;
            for (int i = 1; i <= total; ++i) {
                T[i] = INT_MAX - 1;
                R[i] = -1;
            }
            for (int j = 0; j < n; ++j)
            {
                for (int i = 1; i <= total; i++)
                {
                    if (i >= coins[j])
                    {
                        if (T[i - coins[j]] + 1 < T[i]) {
                            T[i] = 1 + T[i - coins[j]];
                            R[i] = j;
                        }
                    }
                }
            }

            getMinCoinsDenominations<void>(coins, n, R, arr_size, out);

            int count = T[total];

            delete[] T;
            delete[] R;

            return count;
        }

        
    }
}