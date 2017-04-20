#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace str_equation_analise
    {
        TEST(Array, StrEquationAnalise)
        {
            {
                char *str_eq = "3y-4x+(3-(2x-3y))=10y";
                Equation eq(str_eq);

                std::string eqs = eq.get_eq_by({ 'y' });
                EXPECT_EQ(eqs, std::string("y=0.75-1.5x"));
            }

            {
                char *str_eq = "3y-4x-(3-(2x-3y))=10y";
                Equation eq(str_eq);

                std::string eqs = eq.get_eq_by({ 'y' });
                EXPECT_EQ(eqs, std::string("y=-0.3-0.2x"));
            }

            {
                char *str_eq = "(x+x)-(2y-(10x-7y))=15y";
                Equation eq(str_eq);

                std::string eqs = eq.get_eq_by({ 'y' });
                EXPECT_EQ(eqs, std::string("y=0.5x"));
            }
        }
    }
}