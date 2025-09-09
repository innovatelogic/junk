from sympy import symbols
from sympy.plotting import plot

x = symbols('x')
f = x**2 + 1
p = plot(f, (x, -5, 5), show=False)
p.save("plot2d.png")