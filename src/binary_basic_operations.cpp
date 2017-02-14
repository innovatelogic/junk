
#include "binary_basic_operations.h"
#include <math.h>
#include <climits>

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

        size_t CountOneByteInNum32(int32_t value)
        {
            size_t n = 0;

            for (int i = 0; i < sizeof(int32_t); i++)
            {
                if ((value & 1) == 1) {
                    n++;
                }
                value >>= 1;
            }
            return n;
        }

        int32_t GetNextClosestSameBits(int32_t value)
        {
            int32_t n = value;
            size_t c0 = 0;
            size_t c1 = 0;

            // find trailing 0-s from the end
            while (n > 0 && (n & 1) == 0) {
                c0++;
                n >>= 1;
            }

            // find trailing 1-s from the end
            while (n > 0 && (n & 1) == 1)
            {
                c1++;
                n >>= 1;
            }

            int p = c0 + c1;

            if (p == (sizeof(int32_t) * CHAR_BIT) - 1 || c0 + c1 == 0) {
                return -1;
            }

            value |= (1 << p); // set p bit to 1
            value &= ~((1 << p) - 1); // clear prev to p bits
            value |= (1 << (c1 - 1)) - 1; // set c1 - 1 bits right to p

            return value;
        }

        int32_t GetPrevClosetSameBits(int32_t value)
        {
            int32_t temp = value;

            int c0 = 0;
            int c1 = 0;

            // find ending trailing 1's
            while (temp > 0 && (temp & 1) == 1)
            {
                temp >>= 1;
                c1++;
            }

            if (temp == 0){
                return -1;
            }

            // find ending trailing 0's
            while (temp > 0 && (temp & 1) == 0)
            {
                temp >>= 1;
                c0++;
            }

            int p = c0 + c1;
            value &= (~0) << (p + 1);
            int mask = (1 << (c1 + 1)) - 1;
            value |= mask << (c0 - 1);

            return value;
        }
    }
}