
#include <gtest/gtest.h>


namespace junk
{
    /*
    §3.6.2¶4 in the standard:
    "It is implementation-defined whether the dynamic initialization of a non-local variable
    with static storage duration is done before the first statement of main.
    If the initialization is deferred to some point in time after the first statement of main,
    it shall occur before the first odr-use (3.2) of any function or variable defined in the same
    translation unit as the variable to be initialized."

    Since A() is not constexpr, the initialization of a is dynamic. There are two possibilities:
    - a is initialized before main() is called, i.e. before b is initialized.
    - a is not initialized before main(). It is however guaranteed to be initialized before the the use
    of any function defined in the same translation unit, 
    i.e. before the constructor of b is called.

    When execution reaches B b, it is initialized as normal.
    Static local variables are initialized the first time control passes through their declaration,
    so c is initialized next. As main() is exited, its local variable b goes out of scope, 
    and is destroyed. 
    Finally, all static variables are destroyed in reverse order of their initialization, first c, then a.
    */
    namespace static_global_local_init
    {
        class A {
        public:
            A() 
            { 
                std::cout << "a";
            }
            ~A() 
            { 
                std::cout << "A"; 
            }
        };

        class B {
        public:
            B() 
            { 
                std::cout << "b"; 
            }
            ~B() 
            { 
                std::cout << "B"; 
            }
        };

        class C {
        public:
            C() 
            { 
                std::cout << "c"; 
            }
            ~C() 
            { 
                std::cout << "C";
            }
        };

        A a;

        void foo() { static C c; }

        TEST(CppTest, StaticGlobalLocalInit)
        {
            B b;
            foo();
        }
    }

    //----------------------------------------------------------------------------------------------
    namespace friend_in_class_def
    {
        class A;

        class B 
        {
        public:
            B() { std::cout << "B"; }

            // friend B A::createB(); // ERROR
/*            
             There is a compilation error when attempting to declare A::createB() 
             a friend of B.To declare A::createB() a friend of B, 
             the compiler needs to know that that function exists.
             Since it has only seen the declaration of A so far,
             not the full definition, it cannot know this.
*/
        };

        class A 
        {
        public:
            A() { std::cout << "A"; }

            B createB() { return B(); }
        };

        TEST(CppTest, FriendinClassDef)
        {
            A a;
            B b = a.createB();
        }
    }
}