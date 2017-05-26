#include "graph.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace array_2d_dyn_bfs_path_find
    {
        TEST(Graph, Array2dDynBFS_PathFind)
        {
            const size_t ROWS = 7;
            const size_t COLS = 7;

            char **field;
            field = new char*[ROWS];

            for (int i = 0; i < COLS; i++){
                field[i] = new char[COLS];
            }
            /*
            [ROWS][COLS] = {
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 7 },
            };
            */
            std::vector<std::pair<int, int>> path;
            bool flag = search_path<char>(field, ROWS, COLS, 2, 2, 7, path);

            for (int i = 0; i < COLS; i++) {
                delete field[i];
            }
            delete[] field;
        }
    }
}