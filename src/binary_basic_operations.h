#pragma once

#include <stdint.h>
#include "defexport.h"

namespace junk
{
    namespace binary_op
    {
        JUNK_EXPORT bool GetBit32(int32_t value, unsigned int n);

        JUNK_EXPORT int32_t SetBit32(int32_t value, unsigned int n);

        JUNK_EXPORT int32_t ClearBit32(int32_t value, unsigned int n);

        JUNK_EXPORT int32_t ClearUpToBit32(int32_t value, unsigned int n);
    }
}