#pragma once

#include <stdint.h>
#include "defexport.h"

namespace junk
{
    namespace binary_op
    {
        BITS_EXPORT bool GetBit32(int32_t value, unsigned int n);

        BITS_EXPORT int32_t SetBit32(int32_t value, unsigned int n);

        BITS_EXPORT int32_t ClearBit32(int32_t value, unsigned int n);

        BITS_EXPORT int32_t ClearUpToBit32(int32_t value, unsigned int n);

        BITS_EXPORT int32_t ClearFromBit32(int32_t value, unsigned int n);

        BITS_EXPORT int32_t UpdateBit32(int32_t value, unsigned int n, unsigned int v);

        BITS_EXPORT int32_t MergeTwoNum32(int32_t in, int32_t v, unsigned int i, unsigned int j);

        BITS_EXPORT size_t CountOneByteInNum32(int32_t value);

        BITS_EXPORT int32_t GetNextClosestSameBits(int32_t value);

        BITS_EXPORT int32_t GetPrevClosetSameBits(int32_t value);

        BITS_EXPORT size_t BitSwapRequired(int32_t a, int32_t b);

        BITS_EXPORT bool IsLittleEndian();

        BITS_EXPORT uint32_t SwapEvenOddBits32(uint32_t value);
    }
}