#include <iostream>
#include <algorithm>
#include <string>

class ReversibleString
{
public:
    ReversibleString() {}
    ReversibleString(const std::string &str)
    : m_str(str)
    {}

    std::string ToString() const{
        return m_str;
    }

    void Reverse()
    {
        std::reverse(begin(m_str), end(m_str));
    }
private:
    std::string m_str;
};

int main() 
{
    ReversibleString s("live");
    s.Reverse();
    std::cout << s.ToString() << std::endl;

    s.Reverse();
    const ReversibleString& s_ref = s;
    std::string tmp = s_ref.ToString();
    std::cout << tmp << std::endl;

    ReversibleString empty;
    std::cout << '"' << empty.ToString() << '"' << std::endl;

    return 0;
}