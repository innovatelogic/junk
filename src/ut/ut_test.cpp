
#include <iostream>
#include <gtest/gtest.h>
#include <set>

//----------------------------------------------------------------------------------------------
TEST(TestMath, DummyAddTwoDigit)
{
	int i = 1 + 2;
	EXPECT_EQ(i, 3);
}

//----------------------------------------------------------------------------------------------
TEST(TestMath, DummySubstractTwoDigit)
{
    int i = 1 - 2;
	EXPECT_EQ(i, -1);
}


namespace cpptest
{
    class A
    {
    public:
        A(int n = 2) : m_n(n) {}

    public:
        int get_n() const { return m_n; }
        void set_n(int n) { m_n = n; }

    private:
        int m_n;
    };

    class B
    {
    public:
        B(char c = 'a') : m_c(c) {}

    public:
        char get_c() const { return m_c; }
        void set_c(char c) { m_c = c; }

    private:
        char m_c;
    };

    class C
        : virtual public A
        , public B
    { };

    class D
        : virtual public A
        , public B
    { };

    class E
        : public C
        , public D
    { };

    //----------------------------------------------------------------------------------------------
    TEST(CppTest, VirtualClass)
    {
        E e;
        C &c = e;
        D &d = e;
        char  ch = c.get_c();
        int dg = d.get_n();

        c.set_n(3);
        d.set_c('b');
        ch = c.get_c(); 
        dg = d.get_n();
    }

    

    //----------------------------------------------------------------------------------------------
    TEST(CppTest, STLset)
    {
        struct C
        {
            bool operator()(const int &a, const int &b) const
            {
                return a % 10 < b % 10;
            }
        };

        std::set<int> x({ 4, 2, 7, 11, 12, 14, 17, 2 });
        int k = x.size();
        std::set<int, C> y(x.begin(), x.end());
        k = y.size();
    }
}