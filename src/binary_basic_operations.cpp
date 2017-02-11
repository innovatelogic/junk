
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
    }
}