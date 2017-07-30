#include "../algo.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace hash_table
    {
        TEST(HahsTable, InitHashTable)
        {
            HashTable<std::string, int> table;
            table.Insert("one", 1);
            table.Insert("two", 2);
            table.Insert("three", 3);
            table.Insert("four", 4);

            EXPECT_EQ(*table.getItem("one"), 1);
            EXPECT_EQ(*table.getItem("two"), 2);
            EXPECT_EQ(*table.getItem("three"), 3);
            EXPECT_EQ(*table.getItem("four"), 4);
        }
    }
}