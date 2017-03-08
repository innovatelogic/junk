
#pragma once

#include <stdio.h>
#include <limits>

namespace junk
{
    namespace egg_drop
    {
        template<typename T>
        int egg(int n, int h) {

            //Basis case
            if (n == 1) return h;
            if (h == 0) return 0;
            if (h == 1) return 1;

            int minimum = INT_MAX;

            //Recursion to find egg(n,k). The loop iterates i: 1,2,3,...h
            for (int x = 1; x <= h; x++) {
                minimum = std::min(minimum, (1 + std::max(egg<T>(n, h - x), egg<T>(n - 1, x - 1))));
            }
            return minimum;
        }

       
    }
}