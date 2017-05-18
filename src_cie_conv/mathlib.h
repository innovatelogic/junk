
#pragma once

namespace junk
{
    namespace cie_conv
    {
        struct RGB
        {
            int r;
            int g;
            int b;
        };

        // normalized 0-1.f
        struct fRGB
        {
            float r;
            float g;
            float b;
        };

       // float get_

        typedef unsigned char pixval;
        typedef struct {
            pixval r, g, b;
        } pixel;

#define PPM_ASSIGN(p,red,grn,blu) \
    do { (p).r = (red); (p).g = (grn); (p).b = (blu); } while (0)
    }
}