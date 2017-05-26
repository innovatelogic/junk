#pragma once

#include <queue>
#include <vector>
#include <utility>
#include <map>

namespace junk
{
    namespace array_2d_dyn_bfs_path_find
    {
        struct pairhash {
        public:
            template <typename T, typename U>
            std::size_t operator()(const std::pair<T, U> &x) const
            {
                return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
            }
        };

        template<typename T>
        bool isObstacle(const T chr)
        {
            return chr == T('#') || chr == T('?');
        }

        template<typename T>
        bool search_path(T **array, int n_rows, int n_cols, 
                         int row_x, int col_y, 
                         T to_find, std::vector<std::pair<int, int>> &path)
        {
            if (!array || n_cols == 0 || n_rows == 0){
                return false;
            }
            
            if ((row_x < 0 || row_x >= n_rows) || (col_y < 0 || col_y >= n_cols)){
                return false;
            }

            typedef typename std::pair<int, int> t_point;
            std::queue<t_point> wave;
            std::map<t_point, t_point> visited;

            wave.push({row_x, col_y});
            visited.insert({ {(int)row_x, (int)col_y}, {-1, -1} });

            while (!wave.empty())
            {
                t_point curr = wave.front();

                if (array[curr.first][curr.second] == to_find)
                {
                    t_point iter = curr;

                    while (iter.first != -1 || iter.second != -1)
                    {
                        path.push_back({ iter.first, iter.second });

                        std::map<t_point, t_point>::iterator prev = visited.find(iter);
                        
                        iter.first = prev->second.first;
                        iter.second = prev->second.second;
                    }

                    return true;
                }
                
                wave.pop();

                t_point up = t_point(curr.first - 1, curr.second);
                t_point down = t_point(curr.first + 1, curr.second);
                t_point left = t_point(curr.first, curr.second - 1);
                t_point right = t_point(curr.first, curr.second + 1);

                if ((up.first >= 0 && up.first < n_rows) && (up.second >= 0 && up.second < n_cols))
                {
                    if (visited.find(up) == visited.end() && !isObstacle(array[up.first][up.second]))
                    {    
                        wave.push(up);
                        visited.insert(std::make_pair(up, curr));
                    }
                }

                if ((down.first >= 0 && down.first < n_rows) && (down.second >= 0 && down.second < n_cols))
                {
                    if (visited.find(down) == visited.end() && !isObstacle(array[down.first][down.second]))
                    {    
                        wave.push(down);
                        visited.insert({down, curr});
                    }
                }

                if ((left.first >= 0 && left.first < n_rows) && (left.second >= 0 && left.second < n_cols))
                {
                    if (visited.find(left) == visited.end() && !isObstacle(array[left.first][left.second]))
                    {    
                        wave.push(left);
                        visited.insert({left, curr});
                    }
                }

                if ((right.first >= 0 && right.first < n_rows) && (right.second >= 0 && right.second < n_cols))
                {
                    if (visited.find(right) == visited.end() && !isObstacle(array[right.first][right.second]))
                    {
                        wave.push(right);
                        visited.insert({right, curr});
                    }
                }
            }

            return false;
        }
    }
}