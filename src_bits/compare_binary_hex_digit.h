#pragma once

#include "defexport.h"

#include <string>
#pragma once
#include "defexport.h"

namespace junk
{
    namespace numbers
    {
        BITS_EXPORT int str_to_int(const std::string &str, int base);

        BITS_EXPORT bool compare_hex_bin(const std::string &hex, const std::string &bin);
    }
}