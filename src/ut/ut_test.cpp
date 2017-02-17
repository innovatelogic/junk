
#include <iostream>
#include <gtest/gtest.h>
#include <set>
#include <memory>
#include <functional>

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

    //----------------------------------------------------------------------------------------------
    namespace class_size
    {
        class A
        {
        public:
            A() : m_size(sizeof(A)) { }

        public:
            virtual void f() const { std::cout << 1; }
            virtual ~A() { }

        public:
            static bool compare(const A *a, const A *b)
            {
                assert(a != nullptr);
                assert(b != nullptr);
                return a->m_size < b->m_size;
            }

        protected:
            size_t m_size;
        };

        class B
            : public A
        {
        public:
            B() : m_b(nullptr) { m_size = sizeof(B); }

        public:
            virtual void f() const { std::cout << 2; }

        private:
            char *m_b;
        };

        class C
            : public A
        {
        public:
            C() { m_size = sizeof(C); }

        public:
            virtual void f() const { std::cout << 3; }

        private:
            static int *m_c;
        };

        int *C::m_c = nullptr;

        TEST(CppTest, ClassSize)
        {
            std::vector<A*> v({ new C, new B, new A });
            std::stable_sort(v.begin(), v.end(), A::compare);
            std::for_each(v.begin(), v.end(), std::mem_fn(&A::f));
            std::cout << std::endl;
            std::for_each(v.begin(), v.end(), std::default_delete<A>());
        }
    }
    
    //----------------------------------------------------------------------------------------------
    namespace init_order
    {
        class A
        {
        public:
            A(int n = 0) 
                : m_i(n) 
            { 
                std::cout << m_i; 
            }

        protected:
            int m_i;
        };

        class B
            : public A
        {
        public:
            B(int n) 
                : m_j(n), 
                m_a(--m_j),
                m_b() 
            {
                std::cout << m_j;
            }

        private:
            int m_j;
            A m_a;
            A m_b;
            static A m_c;
        };

        A B::m_c(3);

        TEST(CppTest, InitOrder)
        {
            B b(2);
        }
    }

    //----------------------------------------------------------------------------------------------
    namespace std_unique
    {
        bool compare(int a, int b)
        {
            return a % 2 == b % 2;
        }

        TEST(CppTest, StdUnique)
        {
            int a[] = { 3, 1, 4, 6, 1, 3 };
            auto b = std::begin(a);
            auto e = std::end(a);


            e = std::unique(b, e, compare);
            std::copy(b, e, std::ostream_iterator<int>(std::cout));

            std::cout << std::endl;
        }
    }

    //----------------------------------------------------------------------------------------------
    namespace throw_alloc
    {
        class A
        {
        public:
            A(int n)
            {
                if (0 == n) {
                    throw std::logic_error("0");
                }
            }
        };

        //----------------------------------------------------------------------------------------------

        TEST(CppTest, ThrowAlloc)
        {
            A *p0 = nullptr, *p1 = nullptr, *p2 = nullptr;
            try {
                p1 = new A(1);
                p0 = new A(0);
                p2 = new A(2);
            }
            catch (const std::exception &) {
                std::cout << 3;
            }

            std::cout << ((0 != p1) ? 1 : 0);
            std::cout << ((0 != p0) ? 1 : 0);
            std::cout << ((0 != p2) ? 1 : 0) << std::endl;

            delete p1;
            delete p0;
            delete p2;
        }
    }

    //----------------------------------------------------------------------------------------------
    namespace template_template
    {
        /*struct A {};
        struct B {};

        template<typename T = A>
        struct X;

        template<>
        struct X<A> {
            static void f() { std::cout << 1 << std::endl; }
        };

        template<>
        struct X<B> {
            static void f() { std::cout << 2 << std::endl; }
        };

        template< template<typename T = B> class C>
        void g() {
            C<>::f();
        }*/

        template <template <typename> class>
        struct X {
            X() { std::cout << "1"; }
        };

        template <typename>
        struct Y {};

        template <typename T>
        using Z = Y<T>;

        template <>
        struct X<Y> {
            X() { std::cout << "2"; }
        };

        TEST(CppTest, TemplateTemplate)
        {
            X<Y> x1;
            X<Z> x2;
        }
    }

    //----------------------------------------------------------------------------------------------
    namespace sizeof_array
    {
        size_t get_size_1(int* arr)
        {
            return sizeof arr;
        }

        size_t get_size_2(int arr[])
        {
            return sizeof arr;
        }

        size_t get_size_3(int(&arr)[10])
        {
            return sizeof arr;
        }

        TEST(CppTest, SizeofArray)
        {
            int array[10];

            size_t _a = sizeof(array);
            size_t _b = get_size_1(array);
            size_t _c = get_size_2(array);
            size_t _d = get_size_3(array);
        }
    }

    //----------------------------------------------------------------------------------------------
    namespace comma_innit
    {
        TEST(CppTest, CommaInitInt)
        {
            int x;
            x = (0, 1, 2, 3, 4, 5);

            EXPECT_EQ(x, 5);
        }
    }

    //----------------------------------------------------------------------------------------------
    namespace switch_do_while
    {
        TEST(CppTest, SwitchDoWhile)
        {
            int n = 3;
            int i = 0;

            switch (n % 2) {
            case 0:
                do {
                    ++i;
            case 1: ++i;
                } while (--n > 0);
            }
            EXPECT_EQ(i, 5);
        }
    }
}