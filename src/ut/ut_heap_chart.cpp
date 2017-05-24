#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace heap_chart
    {
        TEST(Heap, Chart)
        {
            Chart chart;

            chart.PlaySong("Lady Gaga", "La-la-la");
            chart.PlaySong("Lady Gaga", "Pokerface");
            chart.PlaySong("Lady Gaga", "Pokerface");

            chart.PlaySong("Sting", "Desert rose");

            EXPECT_EQ(chart.TopSong("Lady Gaga"), std::string("Pokerface"));
        }
    }
}

