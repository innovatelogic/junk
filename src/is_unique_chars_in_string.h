#pragma once

#include "defexport.h"
#include <string>
#include <stdio.h>

namespace junk
{
    namespace string
    {
        // ascii symbols only
        JUNK_EXPORT bool is_unique_chars_in_string(const std::string &str);

        JUNK_EXPORT bool is_unique_low_letters_in_string(const std::string &str);

        JUNK_EXPORT void rotate_right(char *str);

        JUNK_EXPORT void reverse(char *str);
    }
}