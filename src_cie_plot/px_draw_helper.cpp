#include "px_draw_helper.h"
#include <math.h>

namespace junk
{
    namespace cie_conv
    {
        //----------------------------------------------------------------------------------------------
        void drawPoint(
            const void *   const clientdata,
            pixel **       const pixels,
            int            const cols,
            int            const rows,
            pixval         const maxval,
            pos_point      const p) {
            /*----------------------------------------------------------------------------
            Draw a single point, assuming that it is within the bounds of the
            image.
            -----------------------------------------------------------------------------*/

            const pixel * const pixelP = (pixel *)clientdata;

            pixels[p.y][p.x] = *pixelP;
        }

        //----------------------------------------------------------------------------------------------
        void drawShallowLine(
                const void *   const clientdata,
                pixel **       const pixels,
                int            const cols,
                int            const rows,
                pixval         const maxval,
                pos_point     const p0,
                pos_point     const p1) {
            /*----------------------------------------------------------------------------
            Draw a line that is more horizontal than vertical.

            Don't clip.

            Assume the line has distinct start and end points (i.e. it's at least
            two points).
            -----------------------------------------------------------------------------*/
            /* Loop over X domain. */
            long dy, srow;
            int dx, col, row, prevrow;

            if (p1.x > p0.x)
                dx = 1;
            else
                dx = -1;
            dy = (p1.y - p0.y) * DDA_SCALE / abs(p1.x - p0.x);
            prevrow = row = p0.y;
            srow = row * DDA_SCALE + DDA_SCALE / 2;
            col = p0.x;
            for (; ; ) {
                if (row != prevrow) {
                    drawPoint(clientdata,
                        pixels, cols, rows, maxval, { col, prevrow });
                    prevrow = row;
                }
                drawPoint(clientdata, pixels, cols, rows, maxval,
                { col, row });
                if (col == p1.x)
                    break;
                srow += dy;
                row = srow / DDA_SCALE;
                col += dx;
            }
        }

        //----------------------------------------------------------------------------------------------
        void drawSteepLine(
                const void *   const clientdata,
                pixel **       const pixels,
                int            const cols,
                int            const rows,
                pixval         const maxval,
                pos_point      const p0,
                pos_point      const p1) {
            /*----------------------------------------------------------------------------
            Draw a line that is more vertical than horizontal.

            Don't clip.

            Assume the line has distinct start and end points (i.e. it's at least
            two points).
            -----------------------------------------------------------------------------*/
            /* Loop over Y domain. */

            long dx, scol;
            int dy, col, row, prevcol;

            if (p1.y > p0.y)
                dy = 1;
            else
                dy = -1;
            dx = (p1.x - p0.x) * DDA_SCALE / abs(p1.y - p0.y);
            row = p0.y;
            prevcol = col = p0.x;
            scol = col * DDA_SCALE + DDA_SCALE / 2;
            for (; ; ) {
                if (col != prevcol) {
                    drawPoint(clientdata,
                        pixels, cols, rows, maxval, { prevcol, row });
                    prevcol = col;
                }
                drawPoint(clientdata, pixels, cols, rows, maxval, { col, row });
                if (row == p1.y)
                    break;
                row += dy;
                scol += dx;
                col = scol / DDA_SCALE;
            }
        }
    }
}