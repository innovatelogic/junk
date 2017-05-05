#pragma once

namespace junk
{
    namespace coin_change_probe_a
    {
        template<typename T>
        int count(T S[], int m, T n)
        {
            // if n is 0 then there is 1 solution (do not include any coin)
            if (n == 0){
                return 1;
            }

            // if n is less than 0 than no solution exist
            if (n < 0){
                return 0;
            }
            // no coins left and n is greater than 0, no solution exist
            if (m <= 0 && n >= 1){
                return 0;
            }

            return count(S, m - 1, n) + count(S, m, n - S[m - 1]);
        }
    }
}