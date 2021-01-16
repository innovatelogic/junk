#include "Common.h"
#include <algorithm>
#include <cmath>

using namespace std;


class ShapeAlloc : public IShape
{
public:
    ShapeAlloc() {}

    ShapeAlloc(const ShapeAlloc& other)
    : m_pos(other.m_pos)
    , m_size(other.m_size)
    , m_texture(other.m_texture)
    {}

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
    ShapeRectangle() {}

    ShapeRectangle(const ShapeRectangle &other)
    : ShapeAlloc(other){}

    std::unique_ptr<IShape> Clone() const override
    {
        return std::make_unique<ShapeRectangle>(*this);
    }

 // Рисует фигуру на указанном изображении
   void Draw(Image &img) const override
   {
        if (img.empty()){
           return;
        }
        const size_t img_h = img.size();
        const size_t img_w = img[0].size();

        Point point_start;
        point_start.x = point_start.y = 0;

        Size sz_canvas;
        sz_canvas.width = img_w;
        sz_canvas.height = img_h;

       if (is_overlap(m_pos, m_size, point_start, sz_canvas))
       {
           ITexture *tex = GetTexture();

           Size tex_size;
           
           if (tex){
                tex_size = tex->GetSize();
           }

           // draw border
           for (int y = m_pos.y; y < m_pos.y + m_size.height; ++y)
           {
               if (y >= 0 && y < img_h)
               {
                    for (size_t x = m_pos.x; x < m_pos.x + m_size.width; ++x)
                    {
                        if (x >= 0 && x < img_w)
                        {
                            size_t rel_x = x - m_pos.x;
                            size_t rel_y = y - m_pos.y;

                            img[y][x] = (!tex || 
                                        (tex && (rel_x >= tex_size.width || rel_y >= tex_size.height))) ? '.'
                                        : tex->GetImage()[rel_y][rel_x];
                        }
                    }
               }
           }
       }
   }
};

class ShapeEllipse : public ShapeAlloc
{
public:
    ShapeEllipse() {}

    ShapeEllipse(const ShapeEllipse &other)
    : ShapeAlloc(other){}

    std::unique_ptr<IShape> Clone() const override
    {
        return std::make_unique<ShapeEllipse>(*this);
    }

 // Рисует фигуру на указанном изображении
   void Draw(Image &img) const override
   {
       if (img.empty()){
           return;
       }

       if (img.empty()){
           return;
        }
        const size_t img_h = img.size();
        const size_t img_w = img[0].size();

        Point point_start;
        point_start.x = point_start.y = 0;

        Size sz_canvas;
        sz_canvas.width = img_w;
        sz_canvas.height = img_h;

       if (is_overlap(m_pos, m_size, point_start, sz_canvas))
       {
           ITexture *tex = GetTexture();

           Size tex_size;
           
           if (tex){
                tex_size = tex->GetSize();
           }

           // draw border
           for (int y = m_pos.y; y < m_pos.y + m_size.height; ++y)
           {
               if (y >= 0 && y < img_h)
               {
                    for (size_t x = m_pos.x; x < m_pos.x + m_size.width; ++x)
                    {
                        if (x >= 0 && x < img_w)
                        {
                            int rel_x = x - m_pos.x;
                            int rel_y = y - m_pos.y;

                            if (!IsPointInEllipse({rel_x, rel_y}, m_size)) 
                            {
                                continue;
                            }
                                

                                img[y][x] = (!tex || 
                                            (tex && (rel_x >= tex_size.width || rel_y >= tex_size.height))) ? '.'
                                            : tex->GetImage()[rel_y][rel_x];
                            
                        }
                    }
               }
           }
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
        return std::make_unique<ShapeEllipse>();
    break;
    case ShapeType::Rectangle:
        return std::make_unique<ShapeRectangle>();
    break;
    default:
        return nullptr;
    }

}