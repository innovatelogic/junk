#pragma once

#include "defexport.h"
#include <string>
#include <stdio.h>

namespace junk
{
    namespace is_unique_chars_in_string
    {
        // ascii symbols only
        STR_EXPORT bool is_unique_chars_in_string(const std::string &str);

        STR_EXPORT bool is_unique_low_letters_in_string(const std::string &str);

        //STR_EXPORT void rotate_right(char *str);

        STR_EXPORT void reverse(char *str);
    }
}