from sympy import symbols
from sympy.plotting import plot3d

x, y = symbols('x y')
f = 2*x + 3*y
p = plot3d(f, (x, -5, 5), (y, -5, 5), show=False)
p.save("plot.png")