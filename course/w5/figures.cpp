#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <vector>
#include <sstream>
#include <iomanip>

class Figure
{
public:
    virtual std::string Name() const = 0;
    virtual float Perimeter() const = 0;
    virtual float Area() const = 0;    
};

class Triangle : public Figure
{
public:
    Triangle(int a, int b, int c) : a(a), b(b), c(c) {}

    float Perimeter() const override { return a + b + c; }

    std::string Name() const override { return "TRIANGLE"; } 

    float Area() const override
    {
        float s = Perimeter() / 2.f;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
private:
    int a, b, c;
};

class Rect : public Figure
{
public:
    Rect(int a, int b) : a(a), b(b) {}

    std::string Name() const override { return "RECT"; } 

    float Perimeter() const override { return 2 * (a + b); }

    float Area() const override
    {
        return a * b;
    }
private:
    int a, b;
};

class Circle : public Figure
{
public:
    Circle(int r) : r(r) {}

    std::string Name() const override { return "CIRCLE"; } 

    float Perimeter() const override { return 2.f * 3.14f * r; }

    float Area() const override
    {
        return 3.14 * r * r;
    }
private:
    int r;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream &is)
{
    std::string figure;

    is >> figure;

    if (figure == "TRIANGLE")
    {
        int a, b, c;
        is >> a >> b >> c;

        return std::make_shared<Triangle>(a, b, c);
    }
    else if (figure == "RECT")
    {
        int a, b;
        is >> a >> b;

        return std::make_shared<Rect>(a, b);
    }
    else if (figure == "CIRCLE")
    {
        int r;
        is >> r;

        return std::make_shared<Circle>(r);
    }

    return nullptr;
}
/*
int main()
{
    std::vector<std::shared_ptr<Figure>> figures;
    for (std::string line; getline(std::cin, line); ) 
    {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
            std::cout << std::fixed << std::setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << std::endl;
            }
        }
    }
    return 0;
}
*/