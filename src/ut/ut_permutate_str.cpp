#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace permutate_str
    {
        TEST(Permutate, StringPermutation)
        {
            std::string str("abcd");
            std::vector<std::string> out;

            Permutate r(str, out);
        }
    }
}