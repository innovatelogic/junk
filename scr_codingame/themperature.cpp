#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


bool same_sign(int a, int b)
{
    return (a >= 0 && b >= 0) || (a < 0 && b < 0);     
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    getline(cin, temps);

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    int min = 0;
    
    if (n > 0)
    {  
        std::vector<int> i_temps;
        
        std::string::size_type prev_pos = 0, pos = 0;
        while ((pos = temps.find(' ', pos)) != std::string::npos)
        {
            std::string substr(temps.substr(prev_pos, pos - prev_pos));
                    
            i_temps.push_back(atoi(substr.c_str()));
            
            prev_pos = ++pos;    
        }
        
        i_temps.push_back(atoi(temps.substr(prev_pos, pos - prev_pos).c_str()));
        
        
        
        if (i_temps.size() > 0)
        {
            min = i_temps[0];
            for (int i = 1; i < n; i++)
            {
                if (std::abs(i_temps[i]) < std::abs(min) )
                {
                    min = i_temps[i];
                }
                else if (std::abs(min) == std::abs(i_temps[i]))
                {
                    min = (min > i_temps[i]) ? min : i_temps[i];
                }
            }
        }
    }
    cout << min << endl;
}