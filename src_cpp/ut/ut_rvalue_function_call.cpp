#include <gtest/gtest.h>
#include <utility>

namespace junk
{
    /*
        The T&& in the the templated functions do not necessarily denote an rvalue reference,
        it depends on the type that is used to instantiate the template.
        If instantiated with an lvalue,
        it collapses to an lvalue reference, if instantiated with an rvalue,
        it collapses to an rvalue reference.
        See note[1].

        Scott Meyers has written a very good article about this, 
        where he introduces the concept of "universal references" 
        (note that this is not C++ standard wording) 
        http://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers

        In this example, all three functions are called once with an lvalue and 
        once with an rvalue.
        In all cases, calling with an lvalue(i)
        collapses T&& x to T& x(an lvalue reference), 
        and calling with an rvalue(20)
        collapses T&& x to T&& x(an rvalue reference).
        Inside the functions,
        x itself is always an lvalue, no matter if its type is an rvalue reference or an lvalue reference.

        - For the first example, y(int&) is called for both cases. Output : 11.
        - For the second example, move(x) obtains an rvalue reference, and y(int&&)is called for both cases.Output : 22.
        - For the third example, forward<T>(x) obtains an lvalue reference when x is an lvalue reference,
        and an rvalue reference when x is an rvalue reference,
        resulting in first a call to y(int&) and then a call to y(int&&). Output : 12.

        Note[1] : �8.3.2�6 in the standard : "If a (...) type template-parameter (�14.3.1) 
        (...) denotes a type TR that is a reference to a type T, 
        an attempt to create the type �lvalue reference to cv TR� creates the type
        �lvalue reference to T�, while an attempt to create the type �rvalue reference to cv TR� 
        creates the type TR." The example at the end of that paragraph is is worth a look.

        Note from the contributor : This demonstrates Scott Meyers's advice that use
        std::forward for universal references, and std::move for rvalue references.
    */

    namespace rvalue_function_call
    {
        std::string out;

        void y(int &) { out += '1'; }
        void y(int &&) { out += '2'; }

        template <class T> void f(T &&x) { y(x); }
        template <class T> void g(T &&x) { y(std::move(x)); }
        template <class T> void h(T &&x) { y(std::forward<T>(x)); }

        TEST(Cpp, RValueFunctionCall)
        {
            int i = 10;

            f(i);   
            f(20);
            
            g(i);
            g(20);
            
            h(i);
            h(20);

            EXPECT_EQ(out, "112212");
        }
    }
}