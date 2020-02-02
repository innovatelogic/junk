#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};
/*
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
};*/

void TestDefault()
{
    Rational r;
    AssertEqual(r.Numerator(), 0, "default numerator 0");
    AssertEqual(r.Denominator(), 1, "default denominator 1");
}

void TestReduction()
{
    {
        Rational r(5, 5);
        AssertEqual(r.Numerator(), 1, "r: (5, 5)");
        AssertEqual(r.Denominator(), 1, "r: (5, 5)");
    }

    {
        Rational r(9, 3);
        AssertEqual(r.Numerator(), 3, "r: (9, 3)");
        AssertEqual(r.Denominator(), 1, "r: (9, 3)");
    }

    {
        Rational r(3, 9);
        AssertEqual(r.Numerator(), 1, "r: (3, 9)");
        AssertEqual(r.Denominator(), 3, "r: (3, 9)");
    }

    {
        Rational r(27, 13);
        AssertEqual(r.Numerator(), 27, "r: (27, 13)");
        AssertEqual(r.Denominator(), 13, "r: (27, 13)");
    }

    {
        Rational r(13, 27);
        AssertEqual(r.Numerator(), 13, "r: (13, 27)");
        AssertEqual(r.Denominator(), 27, "r: (13, 27)");
    }
}

void TestZero()
{
    {
        Rational r(0, 27);
        AssertEqual(r.Numerator(), 0, "r: (0, 27)");
        AssertEqual(r.Denominator(), 1, "r: (0, 27)");
    }
}

void TestMinus()
{
    {
        Rational r(10, -27);
        AssertEqual(r.Numerator(), -10, "r: (10, -27)");
        AssertEqual(r.Denominator(), 27, "r: (10, -27)");
    }
    {
        Rational r(-10, -27);
        AssertEqual(r.Numerator(), 10, "r: (-10, -27)");
        AssertEqual(r.Denominator(), 27, "r: (-10, -27)");
    }
}

int main() 
{
    TestRunner runner;
    // Ð´Ð¾Ð±Ð°Ð²ÑŒÑ‚Ðµ ÑÑŽÐ´Ð° ÑÐ²Ð¾Ð¸ Ñ‚ÐµÑÑ‚Ñ‹
    runner.RunTest(TestDefault, "TestDefault");
    runner.RunTest(TestReduction, "TestReduction");
    runner.RunTest(TestZero, "TestZero");
    runner.RunTest(TestMinus, "TestMinus");
    return 0;
}