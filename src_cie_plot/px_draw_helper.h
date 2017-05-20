#pragma once

#include "common.h"

namespace junk
{
    namespace cie_conv
    {
        void drawPoint(
            pixel** const pixels,
            const pos_point &p,
            const pixel &color);

        void drawShallowLine(
            pixel ** const pixels,
            const pos_point     &p0,
            const pos_point     &p1,
            const pixel &color);

        void drawSteepLine(
                pixel ** const pixels,
                const pos_point &p0,
                const pos_point &p1,
                const pixel &color);
    }
}