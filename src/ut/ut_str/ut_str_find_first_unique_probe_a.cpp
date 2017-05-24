#include "str.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace string_find_first_unique_probe_a
    {
        TEST(String, FindFirstUnique_probe_a)
        {
            {
                std::string str("abcdeadcb");
                EXPECT_EQ(findFirstUniqueIndex<void>(str), 4);
            }

            {
                std::string str("abcdabcd");
                EXPECT_EQ(findFirstUniqueIndex<void>(str), -1);
            }
        }
    }
}