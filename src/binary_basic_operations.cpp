
#include "binary_basic_operations.h"
#include <math.h>

namespace junk
{
    namespace binary_op
    {
        bool GetBit32(int32_t value, unsigned int n)
        {
            return (value & (1 << n)) != 0;
        }

        int32_t SetBit32(int32_t value, unsigned int n)
        {
            return value | (1 << n);
        }

        int32_t ClearBit32(int32_t value, unsigned int n)
        {
            int32_t mask = ~(1 << n);
            return value & mask;
        }

        int32_t ClearUpToBit32(int32_t value, unsigned int n)
        {
            int32_t mask = ~((1 << (n + 1)) - 1);
            return value & mask;
        }

        int32_t ClearFromBit32(int32_t value, unsigned int n)
        {
            int32_t mask = ((1 << (n + 1)) - 1);
            return value & mask;
        }

        int32_t UpdateBit32(int32_t value, unsigned int n, unsigned int v)
        {
            int32_t mask = ~(1 << n);
            return (value & mask) | (v << n);
        }

        // [i, j)
        int32_t MergeTwoNum32(int32_t in, int32_t v, unsigned int i, unsigned int j)
        {
            int32_t out = in;

            unsigned int n_bits = (j - i) + 1;

            if (v > 0 && (1 << (n_bits)) - 1 >= v) //check range
            {
                out &= (~((1 << (n_bits)) - 1) << i); // clear n bits
                out |= v << i;
            }
            return out;
        }
    }
}