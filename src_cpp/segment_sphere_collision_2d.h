#pragma once

#include <iostream>
#include <conio.h>
#include <math.h>

#define m_eps 0.000001f
namespace junk
{
    namespace segment_sphere_colision_2d
    {

        //----------------------------------------------------------------------------------
        /** define simple vector class for representation 3D points*/
        class Vector
        {
        public:
            Vector() : x(0.f), y(0.f), z(0.f) {}
            Vector(const float& _x, const float& _y, const float& _z) : x(_x), y(_y), z(_z) {}
            Vector(const Vector& vOther)
            {
                if (this != &vOther)
                {
                    x = vOther.x;
                    y = vOther.y;
                    z = vOther.z;
                }
            }

            Vector operator+(const Vector& v)const
            {
                Vector out;
                out.x = x + v.x;
                out.y = y + v.y;
                out.z = z + v.z;
                return out;
            }

            Vector operator-(const Vector& v)const
            {
                Vector out;
                out.x = x - v.x;
                out.y = y - v.y;
                out.z = z - v.z;
                return out;
            }

            float Dot(const Vector& _vector_other) const
            {
                return x * _vector_other.x + y * _vector_other.y + z * _vector_other.z;
            }

            Vector Vector::operator*(float f)const
            {
                Vector out;
                out.x = x * f;
                out.y = y * f;
                out.z = z * f;
                return out;
            }

        public:
            union  // data
            {
                struct {
                    float x, y, z;
                };
                float vec_array[3];     // array access
            };
        };

        // define helper function for segment-sphere intersection
        template<typename T>
        bool SegmentSphereIntersection(
            const Vector &s_start,
            const Vector &s_end,
            const Vector &center,
            float radius,
            float *mu1,
            float *mu2)
        {
            float a, b, c, square;

            Vector localSpherePos = s_start - center;
            Vector lineDir = s_end - s_start;

            a = lineDir.Dot(lineDir);
            b = 2.0f * localSpherePos.Dot(lineDir);
            c = localSpherePos.Dot(localSpherePos) - (radius * radius);

            square = b * b - (4 * a * c);

            if (square <= m_eps) {
                return false;
            }

            float sqr = (float)sqrt(square);

            *mu1 = (-b + sqr) / (2 * a);
            *mu2 = (-b - sqr) / (2 * a);

            if (*mu1 < 0.f && *mu2 < 0.f || *mu1 > 1.f && *mu2 > 1.f) {
                return false;
            }

            if (*mu1 < 0.f && *mu2 > 1.f || *mu1 > 1.f && *mu2 < 0.f) {
                return false;
            }

            if (*mu1 > *mu2) {
                std::swap(*mu1, *mu2);
            }
            return true;
        }

    }
}