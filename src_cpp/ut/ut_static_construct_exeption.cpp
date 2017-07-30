#include <gtest/gtest.h>

namespace junk
{
    /*
    Static local variables are initialized the first time control passes through their declaration.
    The first time foo() is called, b is attempted initialized. Its constructor is called,
    which first constructs all member variables. This means A::A() is called, 
    printing a. A::A() then throws an exception, the constructor is aborted, 
    and neither b or B::a are actually considered constructed. In the catch-block,
    c is printed, and then foo() is called again. Since b was never initialized the first time,
    it tries again, this time succeeding, printing ab. When main() exits, the static variable b is destroyed,
    first calling the destructor printing B, and then destroying member variables, printing A.
    */
    namespace static_contstruct_exeption
    {
        int x = 0;
        std::string out;

        class A {
        public:
            A() {
                out += 'a';
                if (x++ == 0) {
                    throw std::exception();
                }
            }
            ~A()
            {
                out += 'A';
            }
        };

        class B {
        public:
            B()
            {
                out += 'b';
            }

            ~B()
            {
                out += 'B';
            }
            A a;
        };

        void foo() { static B b; }

        TEST(Cpp, StaticConstructException)
        {
            try {
                foo();
            }
            catch (std::exception &) {
                out += 'c';
                foo();
            }

            // EXPECT_EQ(out, std::string("acabBA"));
        }
    }
}
