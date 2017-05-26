#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

std::string trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

std::string convert_bits(std::stack<int> &stk)
{
    std::string out;
    if (!stk.empty())
    {
        out = (stk.top() == 0) ? "00 " : "0 ";
        
        //stk.pop();
        
        while(!stk.empty())
        {
            out += "0";
            stk.pop();
        }
        
        out = std::string(" ") + out;
        
        cerr << out.c_str() << endl;
    }
    return out;
}

std::string convert_word(const std::string &str)
{
    std::string out;
    
    if (!str.empty())
    {
        std::stack<int> stk; 
    
        for (int i = str.size() - 1; i >= 0; i--)
        {
            char chr = str[i];
            
            for (int k = 0; k < 7; k++)
            {
                int bit = (chr >> k) & 1;
                
                cerr << bit << endl;
                if (stk.empty() || (!stk.empty() && stk.top() == bit) )
                {
                    stk.push(bit);
                }
                else
                {
                    out = convert_bits(stk) + out;
                    //cerr << out.c_str() << endl;
                    //cerr << "clear stk:" << stk.empty() << " " << bit << endl;
                    stk.push(bit);
                }
            }
        }
        //if (!stk.empty()){
        out = convert_bits(stk) + out;
        //}
    }
    return out;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string MESSAGE;
    getline(cin, MESSAGE);

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    std::string out;
    /*
    size_t pos_prev = 0, pos = 0;
    
    while((pos = MESSAGE.find(' ', pos)) != std::string::npos)
    {
        std::string substring = MESSAGE.substr(pos_prev, pos - pos_prev);
        
        out = convert_word(substring) + out;
        cerr << substring.c_str() << endl;
        
        pos_prev = ++pos;
    }

    std::string substring = MESSAGE.substr(pos_prev, pos - pos_prev);
    cerr << substring.c_str() << endl;*/
    out = convert_word(MESSAGE);
    
    cout << trim(out).c_str() << endl;
}