#include "../graph.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace array_2d_bfs_path_find
    {
        TEST(Graph, Array2dBFS_PathFind)
        {
            const size_t ROWS = 7;
            const size_t COLS = 7;

            int field[ROWS][COLS] = { 
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 7 },
            };

            std::vector<std::pair<int, int>> path;
            bool flag = search_path<ROWS, COLS>(field, ROWS, COLS, 2, 2, 7, path);
        }
    }
}