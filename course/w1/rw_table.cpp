#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using TTable = std::vector<std::vector<int>>;


TTable ReadTable(const std::string &path)
{
    TTable table;

    std::ifstream in(path);

    if (in)
    {
        size_t n, m;

        std::string s_n;
        std::string s_m;

        getline(in, s_n, ' ');
        getline(in, s_m);

        n = std::stoi(s_n);
        m = std::stoi(s_m);

        //std::cout << n << " " << m << std::endl;

        for (int i = 0; i < n; i++)
        {
            std::vector<int> row(m);
            for (int j = 0; j < m; j++)
            {
                std::string value;
                if (j < m - 1){
                    getline(in, value, ',');
                }
                else {
                    getline(in, value);
                }
                
                row[j] = std::stoi(value);
            }
            table.push_back(row);
        }
    }


    return table;
}

void Print(const TTable &table)
{
    const size_t n = table.size();

    for (int i = 0; i < n; ++i)
    {
        const size_t w = table[i].size();

        for (int j = 0; j < w; ++j)
        {
            std::cout << std::setw(10) << table[i][j];
            
            if (j < w - 1) {
                std::cout << ' ';
            }
        }

        if (i < n - 1) {
            std::cout << std::endl;
        }
        
    }
}


int main()
{
    const std::string input = "input.txt";

    TTable table = ReadTable(input);

    Print(table);

    return 0;
}