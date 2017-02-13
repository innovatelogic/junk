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

        JUNK_EXPORT int32_t ClearFromBit32(int32_t value, unsigned int n);

        JUNK_EXPORT int32_t UpdateBit32(int32_t value, unsigned int n, unsigned int v);

        JUNK_EXPORT int32_t MergeTwoNum32(int32_t in, int32_t v, unsigned int i, unsigned int j);

        JUNK_EXPORT size_t CountOneByteInNum32(int32_t value);

        JUNK_EXPORT size_t GetNextClosestSameBits(int32_t value);
    }
}