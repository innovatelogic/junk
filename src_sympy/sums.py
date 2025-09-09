from sympy import *

i, n = symbols('i n')

suma = Sum(2 * i, (i, 1, n))

sum_to_5 = suma.subs(n, 5) # 1 + 2 + 3 + 4 + 5

print(sum_to_5.doit())