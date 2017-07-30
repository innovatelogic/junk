#include "../str.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace get_all_split_strings
    {
        TEST(Partitioning, SplitString)
        {
            PartitioningString part(std::string("123"));

            part.generate();
        }
    }
}