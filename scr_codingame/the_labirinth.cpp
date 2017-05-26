#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;


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
            return chr == T('#');// || chr == T('?');
        }

        template<typename T>
        bool search_path(T **array, int n_rows, int n_cols, 
                         int row_x, int col_y, 
                         T to_find, std::vector<std::pair<int, int>> &path, std::string obstackles = "#?")
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
                    if (visited.find(up) == visited.end() && 
                        obstackles.find(array[up.first][up.second]) == std::string::npos)
                    {    
                        wave.push(up);
                        visited.insert(std::make_pair(up, curr));
                    }
                }

                if ((down.first >= 0 && down.first < n_rows) && (down.second >= 0 && down.second < n_cols))
                {
                    if (visited.find(down) == visited.end() &&
                        obstackles.find(array[down.first][down.second]) == std::string::npos)
                    {    
                        wave.push(down);
                        visited.insert({down, curr});
                    }
                }

                if ((left.first >= 0 && left.first < n_rows) && (left.second >= 0 && left.second < n_cols))
                {
                    if (visited.find(left) == visited.end() && 
                        obstackles.find(array[left.first][left.second]) == std::string::npos)
                    {    
                        wave.push(left);
                        visited.insert({left, curr});
                    }
                }

                if ((right.first >= 0 && right.first < n_rows) && (right.second >= 0 && right.second < n_cols))
                {
                    if (visited.find(right) == visited.end() && 
                        obstackles.find(array[right.first][right.second]) == std::string::npos)
                    {
                        wave.push(right);
                        visited.insert({right, curr});
                    }
                }
            }

            return false;
        }
        
        std::string getDir(int dy, int dx, int &posY, int &posX)
        {
            if (dy > 0)
            {
                posY++;
                return "DOWN";
            }
            else if (dy < 0)
            {
                posY--;
                return "UP";
            }
            
            if (dx > 0)
            {
                 posX++;
                 return "RIGHT";
            }
            else if (dx < 0)
            {
                 posX--;
                 return "LEFT";
            }
        }
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int R; // number of rows.
    int C; // number of columns.
    int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    cin >> R >> C >> A; cin.ignore();
    
    char **field;
    field = new char*[R];

    for (int i = 0; i < C; i++){
        field[i] = new char[C];
    }
    
    bool bControlReached = false;
    bool bControlFound = false;
    
    std::vector<std::pair<int, int>> path;
    std::vector<std::pair<int, int>> back_path;
    std::vector<std::pair<int, int>> rambling_path;
    
    int ramble_x = 1;
    int ramble_y = 0;
   // std::vector<std::pair<int, int>> rambling_path;
    
    // game loop
    while (1) 
    {
        int KR; // row where Kirk is located.
        int KC; // column where Kirk is located.
        cin >> KR >> KC; cin.ignore();
        
        for (int i = 0; i < R; i++) {
            string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            cin >> ROW; cin.ignore();
            
            for (int j = 0; j < ROW.size(); j++)
            {
                field[i][j] = ROW[j];
            }
            
            cerr << ROW << endl;
        }

        int curr_y = KR;
        int curr_x = KC;

        if (!bControlReached)
        {
            
            if (!bControlFound && search_path<char>(field, R, C, KR, KC, 'C', path))
            {
                cerr << "Found!" << endl;
                
                bControlFound = true;

                path.pop_back();
            }
            
           
            if (bControlFound)
            {
                // next move to control
                
                cerr << "Move to Control" << endl;

                cerr << path.size() << endl;
                size_t next_idx = path.size() - 1;
                
                cerr << path[next_idx].first << " " << path[next_idx].second << endl;
                
                int dy = path[next_idx].first - curr_y;
                int dx = path[next_idx].second - curr_x;  
                                
                cout << getDir(dy, dx, KR, KC).c_str() << endl;
                
                path.pop_back();
                
                if (path.empty())
                {
                    cerr << "Control REACHED" << endl;
                    
                    bControlReached = true;
                    
                    search_path<char>(field, R, C, KR, KC, 'T', back_path);
                    
                    back_path.pop_back();
                }
            }
            else
            {
                if (search_path<char>(field, R, C, KR, KC, '?', rambling_path, "#"))
                {
                    rambling_path.pop_back();
                    
                    int dy = rambling_path[rambling_path.size() - 1].first - curr_y;
                    int dx = rambling_path[rambling_path.size() - 1].second - curr_x;  
                                        
                    cout << getDir(dy, dx, KR, KC).c_str() << endl;
                }
                else
                {
                    cerr << "RAMBLING" << endl;
                    cout << "RIGHT" << endl;   
                    
                }
            }
        }
        else
        {
            cerr << "GO BACK" << endl;
            
            int dy = back_path[back_path.size() - 1].first - curr_y;
            int dx = back_path[back_path.size() - 1].second - curr_x;  
                                        
            cout << getDir(dy, dx, KR, KC).c_str() << endl;
                        
              back_path.pop_back();
        }
    }
    
     
    
    for (int i = 0; i < C; i++) {
        delete field[i];
    }
    delete[] field;
}