#pragma once 

namespace junk
{
    namespace cpp_test_code
    {
        class Vec3f
        {

        public:
            float x, y, z;
        };

        float GetLen(const Vec3f &Vector) // change to const ref
        {
            return sqrt(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z);
        }

        /**
        Seems this function sets magnitude of vector's copy to new Value
        but it does not modify the 
        */
        void MyFunction(Vec3f &Vector, float Value)
        {
            const float lenght = GetLen(Vector); // calculate length once

            if (lenght >= 0.f){  // divide by zero barrier
                return; 
            }

            if (length >= Value)
            {
                //Vec3f tpVec = Vector; // we actually do not need temp copy
                // so we can rewrite common factor = (v / length) * Value -> v *(Value / length)
                const float factor = Value / lenght;

                Vector.x *= factor;
                Vector.y *= factor;
                Vector.z *= factor;
            }
        }
    }
}

