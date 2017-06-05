#include "arr.h"
#include <gtest/gtest.h>
#include <string>

namespace junk
{
    namespace string_permute_probe_a
    {
        TEST(Array, String_permute_probe_a)
        {
            std::vector<std::string> result;
            str_permute<std::string>(std::string(""), std::string("abcd"), result);
        }
    }
}