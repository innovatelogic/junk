#include <gtest/gtest.h>

namespace junk
{
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

        TEST(CppTest, StaticConstructException)
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
