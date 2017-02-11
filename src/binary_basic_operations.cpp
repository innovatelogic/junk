
#include "binary_basic_operations.h"

namespace junk
{
    namespace binary_op
    {
        bool GetBit32(int32_t value, unsigned int n)
        {
            return (value & (1 << (n - 1))) != 0;
        }

        int32_t SetBit32(int32_t value, unsigned int n)
        {
            return value | (1 << (n - 1));
        }
    }
}