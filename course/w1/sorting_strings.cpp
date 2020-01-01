#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

class SortedStrings 
{
public:
    void AddString(const std::string &s)
    {
        m_strings.push_back(s);
    }
    
    std::vector<std::string> GetSortedStrings()
    {
        std::vector<std::string> out = m_strings;

        std::sort(begin(out), end(out));

        return out;
    }
private:
    std::vector<std::string> m_strings;
};

int main()
{
    return 0;
}