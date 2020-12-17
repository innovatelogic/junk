#include "Common.h"

using namespace std;


class ShapeAlloc : public IShape
{
public:
    std::unique_ptr<IShape> Clone() const override
    {
        return nullptr;
    }

    void SetPosition(Point pos) override
    {
        m_pos = pos;
    }

    Point GetPosition() const override
    {
        return m_pos;
    }

    void SetSize(Size size)
    {
        m_size = size;
    }

    Size GetSize() const override
    {
        return m_size;
    }

   void SetTexture(std::shared_ptr<ITexture> texture) override
   {
       m_texture = texture;
   }

   ITexture* GetTexture() const
   {
       return m_texture.get();
   }

 
protected:
    Point m_pos;
    Size  m_size;

    std::shared_ptr<ITexture> m_texture;
};

bool is_overlap(const Point &p1, const Size &s1, const Point &p2, const Size &s2)
{
    return std::min(p1.x, p2.x) + std::max(p1.x + s1.width, p2.x + s2.width) < s1.width + s2.width ||
            std::min(p1.y, p2.y) + std::max(p1.y + s1.height, p2.y + s2.height) < s1.height + s2.height;
}

class ShapeRectangle : public ShapeAlloc
{
public:
 // Рисует фигуру на указанном изображении
   void Draw(Image &img) const override
   {
       if (img.empty()){
           return;
       }
       const size_t img_h = img.size();
       const size_t img_w = img[0].size();

       if (is_overlap(m_pos, m_size, {0, 0}, {img_w, img_h}))
       {
           for (size_t y = m_pos.y; y < m_size.height && y < img_h; ++y)
           {
               for (size_t x = m_pos.x; x < m_size && x < img_w; ++x)
               {
                   
               }
           }
       }
   }

};

class ShapeEllipse : public ShapeAlloc
{
public: 
 // Рисует фигуру на указанном изображении
   void Draw(Image&) const override
   {
       if (img.empty()){
           return;
       }
   }

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