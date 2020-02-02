#include <iostream>
#include <sstream>
#include <istream>
#include <type_traits>
#include <map>
#include <set>

using namespace std;

// cl /EHsc mycode.cpp

class Rational 
{
public:
    Rational() 
    : m_num(0)
    , m_den(1)
    {
    }

    Rational(int numerator, int denominator)
    {
        if (denominator == 0){
            throw std::invalid_argument("invalid argument");
        }

        bool sign_num = numerator >= 0;
        bool sign_den = denominator >= 0;

        numerator = std::abs(numerator);
        denominator = std::abs(denominator);

        const int n_gcd = gcd(numerator, denominator);

        m_num = numerator / n_gcd;
        m_den = denominator / n_gcd;

        if ((!sign_den && sign_num) || (!sign_num && sign_den))
        {
            m_num *= -1;
        }
    }

    int Numerator() const {
        return m_num;
    }

    int Denominator() const {
        return m_den;
    }

    static int gcd(int a, int b)
    {
        // пока оба числа положительны, будем их уменьшать, не меняя их НОД
        while (a > 0 && b > 0) 
        {
            // возьмём большее из чисел и заменим его остатком от деления на второе
            // действительно, если a и b делятся на x, то a - b и b делятся на x
            // тогда и a % b и b делятся на x, так что можно a заменить на a % b
            if (a > b) {
                a %= b;
            } else {
                b %= a;
            }
        }
        return a + b;
    }
public:
    int m_num;
    int m_den;
};

bool operator==(const Rational &lhs, const Rational &rhs)
{
    return rhs.m_num == lhs.m_num && rhs.m_den == lhs.m_den;
}

Rational operator+(const Rational &lhs, const Rational &rhs)
{
    return Rational((lhs.m_num * rhs.m_den) + (rhs.m_num * lhs.m_den) , lhs.m_den * rhs.m_den);
}

Rational operator-(const Rational &lhs, const Rational &rhs)
{
    Rational m_rhs = rhs;
    m_rhs.m_num *= -1;
    return Rational(((lhs.m_num * m_rhs.m_den) + (m_rhs.m_num * lhs.m_den)), lhs.m_den * m_rhs.m_den);
}

Rational operator/(const Rational &lhs, const Rational &rhs)
{
    int num = lhs.m_num * rhs.m_den;
    int den = lhs.m_den * rhs.m_num;

    if (den == 0) {
        throw std::domain_error("domain error");
    }

    return Rational(lhs.m_num * rhs.m_den, lhs.m_den * rhs.m_num);
}

Rational operator*(const Rational &lhs, const Rational &rhs)
{
    return Rational(lhs.m_num * rhs.m_num, lhs.m_den * rhs.m_den);
}

ostream& operator<<(ostream &stream, const Rational &r)
{
    stream << r.m_num << '/' << r.m_den;
    return stream;
}

istream& operator>>(istream &stream, Rational &r)
{
    int n = 0;
    int d = 0;
    char c;

    if (stream.peek() == EOF)
    {
        return stream;
    }

    stream >> n;
    stream >> c;
    stream >> d;

/*    std::string s;
    getline(stream, s, '/');
    if (s.empty()){
        return stream;
    }

    size_t startpos = s.find_first_not_of(" ");
    if (string::npos != startpos)
    {
        s = s.substr(startpos);
    }

    if (s.empty()){
        return stream;
    }

    std::cout << s << std::endl;
    n = stoi(s);
    stream >> s;
    std::cout << "AAA" << std::endl;
    s = s.erase(s.find_last_not_of(" ") + 1);
    std::cout << s << std::endl;

    d = stoi(s);*/
/*

    std::cout << s;

    size_t div_pos = s.find('/');
    if (div_pos == std::string::npos){
        return stream;
    }

    std::string s_n = s.substr(0, n);
    std::string s_d = s.substr(n + 1);

    if (s_n.empty() || s_d.empty()){
        return stream;
    }
    n = stoi(s_n);
    d = stoi(s_d);*/

    if (c == '/'){
        r = Rational(n, d);
    }
    

    /*std::string s;
    if (getline(stream, s))
    {
        std::cout << s << std::endl;
        std::size_t n = s.find('/');

        std::cout << s.substr(0, n) << " " << s.substr(n + 1) << std::endl;


        n = stoi(s.substr(0, n));
        d = stoi(s.substr(n + 1));

        r = Rational(n, d);
    }
    else 
    {
        std::cout << "cant get line" << std::endl;
    }*/

    return stream;
}

bool operator< (const Rational &lhs, const Rational &rhs)
{
    return double(lhs.m_num) / lhs.m_den < double(rhs.m_num) / rhs.m_den;
}

int main() 
{
    std::string str;
    
    try
    {
        if (getline(std::cin, str))
        {
            stringstream ss(str);

            std::string q1;
            std::string q2;
            char op;

            ss >> q1;
            ss >> op;
            ss >> q2;

            //std::cout << op << std::endl;
            if (!(op == '+' || op == '/' || op == '-' || op == '*')){
                throw std::invalid_argument("invalid argument");
            }
            

            stringstream ss_q1(q1);
            stringstream ss_q2(q2);

            Rational r1;
            Rational r2;

            ss_q1 >> r1;
            ss_q2 >> r2;

            if (q2 == "0"){
                throw std::domain_error("domain error");
            }

            if (op == '+')
            {
                std::cout << r1 + r2 << std::endl;
            }
            else if (op == '/')
            {
                std::cout << r1 / r2 << std::endl;
            }
            else if (op == '-')
            {
                std::cout << r1 - r2 << std::endl;
            }
            else if (op == '*')
            {
                std::cout << r1 * r2 << std::endl;
            }
            else {
                throw std::invalid_argument("invalid argument");
            }
        }   
    }
    catch(std::invalid_argument &e)
    {
        std::cout << "Invalid argument" << std::endl;
    }
    catch(std::domain_error &e)
    {
        std::cout << "Division by zero" << std::endl;
    }
    


    return 0;
}