#include "Common.h"

using namespace std;

class ShapeRectangle : public IShape
{
public:
};

class ShapeEllipse : public IShape
{
public: 
};

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type)
{
    switch (shape_type)
    {
    case ShapeType::Ellipse:
        return std::make_shared<ShapeEllipse>();
    break;
    case ShapeType::Rectangle:
        return std::make_unique<ShapeRectangle>();
    break;
    default:
        return nullptr;
    }

}