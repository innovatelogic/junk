#pragma once

#include "defexport.h"

namespace junk
{
    namespace bits_sum
    {
        class BITS_EXPORT ExportType
        {
            ExportType() {}

            virtual ~ExportType() {}

            int test() { int k = 0; k++; return k; }
        };
    }
}