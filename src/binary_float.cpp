

#include "binary_float.h"
#include <vector>

namespace junk
{
    namespace binary_float
    {
        std::string floatToStrBin(float value)
        {
            if (value < 0.f || value > 1.f){
                return std::string("ERR");
            }

            //std::vector<double> ts;

            std::string out;
            int n_count = 0;
            while (value)
            {
                if (n_count == 32) {
                    //out = "ERR";
                    break;
                }
                float r = value * 2;

                if ((int)r >= 1)
                {
                    out += '1';
                    value = r - 1;
                }
                else
                {
                    out += '0';
                    value = r;
                }
                //ts.push_back(value);
                n_count++;
            }
            return out;
        }
    }
}