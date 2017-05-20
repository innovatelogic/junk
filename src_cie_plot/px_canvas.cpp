#include "px_canvas.h"
#include "px_draw_helper.h"
#include "cie_model_helper.h"
#include "common.h"
#include <algorithm>
#include <assert.h>

namespace junk
{
    namespace cie_conv
    {
        void Canvas::Allocate()
        {
            m_pixels = new pixel*[m_rows];
            for (size_t r = 0; r < m_rows; r++) {
                m_pixels[r] = new pixel[m_cols];
            }
        }

        void Canvas::Free()
        {
            for (size_t r = 0; r < m_rows; r++) {
                delete[] m_pixels[r];
            }
            delete[] m_pixels;
        }

        void Canvas::FillColor(pixel color)
        {
            for (size_t row = 0; row < m_rows; ++row) {
                for (size_t col = 0; col < m_cols; ++col) {
                    m_pixels[row][col] = color;
                }
            }
        }

        void Canvas::DrawCIEPlotOutline(pixval maxval)
        {
            if (m_pixels)
            {
                int const pxcols = m_rows;
                int const pxrows = m_cols;

                pixel rgbcolor = { maxval , maxval , maxval };
                int wavelength;
                int lx, ly;
                int fx, fy;

                for (wavelength = 380; wavelength <= 700; wavelength += 5)
                {
                    int icx, icy;

                    computeMonochromeColorLocation(wavelength, pxcols, pxrows, &icx, &icy);

                    if (wavelength > 380)
                    {
                        line(Maxval, { lx, ly }, { icx, icy }, (char *)&rgbcolor);
                    }
                    else {
                        fx = icx;
                        fy = icy;
                    }
                    lx = icx;
                    ly = icy;
                }
                line(Maxval, { lx, ly }, { fx, fy }, (char *)&rgbcolor);
            }
        }

        void Canvas::DrawPlackanLocus(pixval const maxval)
        {
            double lx = -1, ly = -1;
            double x, y;

            const double pow_10_9 = std::pow(10, 9);
            const double pow_10_6 = std::pow(10, 6);
            const double pow_10_3 = std::pow(10, 3);

            for (int T = 1500; T < 10000; T += 5)
            {
                double T_pow_3 = std::pow(T, 3);
                double T_pow_2 = std::pow(T, 2);

                double M1 = pow_10_9 / T_pow_3;
                double M2 = pow_10_6 / T_pow_2;
                double M3 = pow_10_3 / T;

                if (T <= 4000) {
                    x = -0.2661239f * M1 - 0.23435f * M2 + 0.8776756f * M3 + 0.179910;
                }
                else {
                    x = -3.0258469 * M1 + 2.10703f * M2 + 0.22263 * M3 + 0.2403;
                }

                if (T <= 2222) {
                    y = -1.10638 * std::pow(x, 3) - 1.3481102 * std::pow(x, 2) + 2.18555 * x - 0.202196;
                }
                else if (T > 2222 && T <= 4000) {
                    y = -0.9549476 * std::pow(x, 3) - 1.374185 * std::pow(x, 2) + 2.09137015 * x - 0.16748867;
                }
                else {
                    y = 3.081758 * std::pow(x, 3) - 5.873386 * std::pow(x, 2) + 3.751129 * x - 0.37001483;
                }

                double cx = ((double)x) * (m_cols - 1);
                double cy = m_rows - ((double)y) * (m_rows - 1);

                if (lx == -1 && ly == -1)
                {
                    lx = cx;
                    ly = cy;
                }
                else
                {
                    static const pixel rgbcolor = { 0, 0, 0 };
                    line(maxval, { (int)lx, (int)ly }, { (int)cx, (int)cy }, (char *)&rgbcolor);
                    lx = cx;
                    ly = cy;
                }
            }
        }

        void Canvas::line(
                pixval         const maxval,
                pos_point     const p0,
                pos_point     const p1,
                const void *   const clientdata) 
        {

            pos_point c0, c1;
            bool noLine;  /* There's no line left after clipping */

                          //ppmd_validateCoord(cols);
                          //ppmd_validateCoord(rows);
                          //ppmd_validatePoint(p0);
                          //ppmd_validatePoint(p1);

                          //if (lineclip) {
                          //    clipLine(p0, p1, cols, rows, &c0, &c1, &noLine);
                          //}
                          //else {
            c0 = p0;
            c1 = p1;
            noLine = false;
            //}

            if (noLine) {
                /* Nothing to draw */
            }
            else if (pointsEqual(c0, c1)) {
                /* This line is just a point.  Because there aren't two
                distinct endpoints, we have a special case.
                */
                drawPoint(clientdata, m_pixels, m_cols, m_rows, maxval, c0);
            }
            else {
                /* Draw, using a simple DDA. */
                if (abs(c1.x - c0.x) > abs(c1.y - c0.y))
                    drawShallowLine(clientdata, m_pixels, m_cols, m_rows, maxval, c0, c1);
                else
                    drawSteepLine(clientdata, m_pixels, m_cols, m_rows, maxval, c0, c1);
            }
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::PlotCIESpace(pixval const maxval, const struct colorSystem * const cs)
        {
            DrawCIEPlotOutline(Maxval);
            FillCIE(maxval, cs);
        }

        //----------------------------------------------------------------------------------------------
        void Canvas::FillCIE(
            pixval                     const maxval,
            const struct colorSystem * const cs)
        {

            int const pxcols = m_cols;
            int const pxrows = m_rows;

            /* Scan the image line by line and  fill  the  tongue  outline
            with the RGB values determined by the color system for the x-y
            co-ordinates within the tongue.
            */

            for (int y = 0; y < pxrows; ++y)
            {
                bool present;  /* There is some tongue on this line */
                int leftEdge; /* x position of leftmost pixel in tongue on this line */
                int rightEdge; /* same, but rightmost */

                findTongue(m_pixels, pxcols, y, &present, &leftEdge, &rightEdge);

                if (present) {
                    int x;

                    for (x = leftEdge; x <= rightEdge; ++x) {
                        double cx, cy, cz, jr, jg, jb, jmax;
                        int mx;


                        cx = ((double)x) / (pxcols - 1);
                        cy = 1.0 - ((double)y) / (pxrows - 1);
                        cz = 1.0 - (cx + cy);

                        xyz_to_rgb(cs, cx, cy, cz, &jr, &jg, &jb);

                        mx = Maxval;

                        /* Check whether the requested color  is  within  the
                        gamut  achievable with the given color system.  If
                        not, draw it in a reduced  intensity,  interpolated
                        by desaturation to the closest within-gamut color. */

                        if (constrain_rgb(&jr, &jg, &jb)) {
                            mx = Maxval;
                        }
                        /* Scale to max(rgb) = 1. */
                        jmax = std::max(jr, std::max(jg, jb));
                        if (jmax > 0) {
                            jr = jr / jmax;
                            jg = jg / jmax;
                            jb = jb / jmax;
                        }
                        
                        m_pixels[y][x].r = static_cast<int>(mx * jr);
                        m_pixels[y][x].g = static_cast<int>(mx * jg);
                        m_pixels[y][x].b = static_cast<int>(mx * jb);
                    }
                }
            }
        }
    }
}