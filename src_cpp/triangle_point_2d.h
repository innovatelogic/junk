#pragma once

namespace junk
{
    namespace triangle_point_2d_probe_a
    {
        struct Vector
        {
            float x, y, z;
        };

        template<typename>
        Vector Cross(const Vector &a, const Vector &b)
        {
            Vector out;

            out.x = a.x * b.y - a.y * b.x;
            out.y = a.z * b.x - a.x * b.z;
            out.z = a.y * b.z - a.z * b.y;

            return out;
        }

        // twice area of triangle
        template <typename>
        float TriangleArea2_2d(float x1, float y1, float x2, float y2, float x3, float y3)
        {
            return (x1 - x2) * (y2 - y3) - (x2 - x3) * (y1 - y2);
        }

        template <typename>
        bool TestPointInTriangle2d(float ax, float ay, float bx, float by, float cx, float cy, float px, float py)
        {
            const Vector a = {bx - ax, 0.f, by - ay};
            const Vector b = {cx - ax, 0.f, cy - ay};

            Vector c = Cross<void>(b, a);

            float absTriSq = fabs(c.y);

            float u = TriangleArea2_2d<void>(px, py, bx, by, cx, cy); // pbc double area (bp)x(cp)
            float v = TriangleArea2_2d<void>(px, py, cx, cy, ax, ay); // pca double area (ap)x(cp)

            float ood = 1.f / absTriSq; // one-over denominator of twice area of abc 

            // calc. relation between areas as barycentric coordinates
            u = u * ood;
            v = v * ood;
            float w = 1.f - u - v;

            return v >= 0 && w >= 0 && (1.f - u) <= 1.f;
        }
    }
}