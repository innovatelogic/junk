#include "conv_impl.h"
#include "px_draw_helper.h"
#include "cie_model_helper.h"
#include <stdio.h>
#include <algorithm>

namespace junk
{
    namespace cie_conv
    {
        //----------------------------------------------------------------------------------------------
        CieConvertorImpl::CieConvertorImpl()
            : SIZE_ROWS(1024)
            , SIZE_COLS(1024)
        {
            pixels = new pixel*[SIZE_ROWS];
            for (size_t r = 0; r < SIZE_ROWS; r++) {
                pixels[r] = new pixel[SIZE_COLS];
            }
        }

        //----------------------------------------------------------------------------------------------
        CieConvertorImpl::~CieConvertorImpl()
        {
            for (size_t r = 0; r < SIZE_ROWS; r++) {
                delete[] pixels[r];
            }
            delete[] pixels;
        }

        //----------------------------------------------------------------------------------------------
        void CieConvertorImpl::makeAllBlack(pixel** const pixels,
            unsigned int const cols,
            unsigned int const rows)
        {
            unsigned int row;
            for (row = 0; row < rows; ++row) {
                unsigned int col;
                for (col = 0; col < cols; ++col)
                    PPM_ASSIGN(pixels[row][col], 0, 0, 0);
            }
        }

        //----------------------------------------------------------------------------------------------
        bool CieConvertorImpl::Save(const std::string &filename)
        {
            bool bResult = true;

            const int dimx = SIZE_COLS;
            const int dimy = SIZE_ROWS;

            FILE *fp = fopen(filename.c_str(), "wb"); 
            fprintf(fp, "P6\n%d %d\n255\n", SIZE_COLS, SIZE_ROWS);
            for (size_t row = 0; row < SIZE_ROWS; ++row)
            {
                for (size_t col = 0; col < SIZE_COLS; ++col)
                {
                    static unsigned char color[3];
                    color[0] = pixels[row][col].r;  //red 
                    color[1] = pixels[row][col].g;  // green
                    color[2] = pixels[row][col].b;  // blue 
                    fwrite(color, 1, 3, fp);
                }
            }
            fclose(fp);

            return bResult;
        }

        //----------------------------------------------------------------------------------------------
        void CieConvertorImpl::Generate()
        {
            makeAllBlack(pixels, SIZE_COLS, SIZE_ROWS);

            drawTongueOutline(pixels, SIZE_COLS, SIZE_ROWS, Maxval, false, 0, 0);

            fillInTongue(pixels, SIZE_COLS, SIZE_ROWS, Maxval, &CIEsystem, false, 0, 0, true);

            DrawPlackanLocus(pixels,
                SIZE_COLS,
                SIZE_ROWS,
                Maxval,
                &CIEsystem
            );
        }
        //----------------------------------------------------------------------------------------------
        static void
            findTongue(pixel ** const pixels,
                int      const pxcols,
                int      const xBias,
                int      const row,
                bool *   const presentP,
                int *    const leftEdgeP,
                int *    const rightEdgeP) {
            /*----------------------------------------------------------------------------
            Find out if there is any tongue on row 'row' of image 'pixels', and if
            so, where.

            We assume the image consists of all black except a white outline of the
            tongue.
            -----------------------------------------------------------------------------*/
            int i;

            for (i = 0;
                i < pxcols && PPM_GETR(pixels[row][i]) == 0;
                ++i);

            if (i >= pxcols)
                *presentP = false;
            else {
                int j;
                int const leftEdge = i;

                *presentP = true;

                for (j = pxcols - 1;
                    j >= leftEdge && PPM_GETR(pixels[row][j]) == 0;
                    --j);

                *rightEdgeP = j;
                *leftEdgeP = leftEdge;
            }
        }

        //----------------------------------------------------------------------------------------------

        void
            ppmd_linep(pixel **       const pixels,
                int            const cols,
                int            const rows,
                pixval         const maxval,
                ppmd_point     const p0,
                ppmd_point     const p1,
                const void *   const clientdata) {

            ppmd_point c0, c1;
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
                drawPoint(clientdata, pixels, cols, rows, maxval, c0);
            }
            else {
                /* Draw, using a simple DDA. */
                if (abs(c1.x - c0.x) > abs(c1.y - c0.y))
                    drawShallowLine(clientdata, pixels, cols, rows, maxval,
                        c0, c1);
                else
                    drawSteepLine(clientdata, pixels, cols, rows, maxval,
                        c0, c1);
            }
        }

        

        void
            ppmd_line(pixel ** const pixels,
                int           const cols,
                int           const rows,
                pixval        const maxval,
                int           const x0,
                int           const y0,
                int           const x1,
                int           const y1,
                const void *  const clientData) {

            ppmd_linep(pixels, cols, rows, maxval, { x0, y0 }, { x1, y1 }, clientData);
        }

        //----------------------------------------------------------------------------------------------

        void CieConvertorImpl::drawTongueOutline(pixel ** const pixels,
                int    const pixcols,
                int    const pixrows,
                pixval const maxval,
                bool   const upvp,
                int    const xBias,
                int    const yBias) {

            int const pxcols = pixcols - xBias;
            int const pxrows = pixrows - yBias;

            pixel rgbcolor;
            int wavelength;
            int lx, ly;
            int fx, fy;

            PPM_ASSIGN(rgbcolor, maxval, maxval, maxval);

            for (wavelength = 380; wavelength <= 700; wavelength += 5) 
            {
                int icx, icy;

                computeMonochromeColorLocation(wavelength, pxcols, pxrows, upvp, &icx, &icy);

                if (wavelength > 380)
                {
                    ppmd_line(pixels, pixcols, pixrows, Maxval, B(lx, ly), B(icx, icy), (char *)&rgbcolor);
                }
                else {
                    fx = icx;
                    fy = icy;
                }
                lx = icx;
                ly = icy;
            }
            ppmd_line(pixels, pixcols, pixrows, maxval,
                B(lx, ly), B(fx, fy),
                (char *)&rgbcolor);
        }

        //----------------------------------------------------------------------------------------------
        void CieConvertorImpl::DrawPlackanLocus(pixel ** const pixels, 
            int    const pixcols,
            int    const pixrows,
            pixval const maxval,
            const struct colorSystem * const cs
        )
        {
            double lx = -1, ly = -1;
            double x, y;

            const double pow_10_9 = std::pow(10, 9);
            const double pow_10_6 = std::pow(10, 6);
            const double pow_10_3 = std::pow(10, 3);

            for (int T = 1500; T < 10000; T+=5) 
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
                else  {
                    y = 3.081758 * std::pow(x, 3) - 5.873386 * std::pow(x, 2) + 3.751129 * x - 0.37001483;
                }

                double cx =  ((double)x) * (pixcols - 1);
                double cy = pixrows - ((double)y) * (pixrows - 1);

                if (lx == -1 && ly == -1)
                {
                    lx = cx;
                    ly = cy;
                }
                else
                {
                    static const pixel rgbcolor = { 0, 0, 0 };
                    ppmd_line(pixels, pixcols, pixrows, maxval,
                        (int)lx, (int)ly, (int)cx, (int)cy,
                        (char *)&rgbcolor);
                    lx = cx;
                    ly = cy;
                }

                //pixels[(int)cy][(int)cx].r = 0; //= { maxval, maxval, maxval };
                //pixels[(int)cy][(int)cx].g = 0;
                //pixels[(int)cy][(int)cx].b = 0;
            }
        }
        
        //----------------------------------------------------------------------------------------------
        void CieConvertorImpl::fillInTongue(
            pixel **                       const pixels,
                int                        const pixcols,
                int                        const pixrows,
                pixval                     const maxval,
                const struct colorSystem * const cs,
                bool                       const upvp,
                int                        const xBias,
                int                        const yBias,
                bool                       const highlightGamut)
        {

            int const pxcols = pixcols;
            int const pxrows = pixrows;

            int y;

            /* Scan the image line by line and  fill  the  tongue  outline
            with the RGB values determined by the color system for the x-y
            co-ordinates within the tongue.
            */

            for (y = 0; y < pxrows; ++y) {
                bool present;  /* There is some tongue on this line */
                int leftEdge; /* x position of leftmost pixel in tongue on this line */
                int rightEdge; /* same, but rightmost */

                findTongue(pixels, pxcols, xBias, y, &present, &leftEdge, &rightEdge);

                if (present) {
                    int x;

                    for (x = leftEdge; x <= rightEdge; ++x) {
                        double cx, cy, cz, jr, jg, jb, jmax;
                        int r, g, b, mx;

                        
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
                            mx = highlightGamut ? Maxval : ((Maxval + 1) * 3) / 4;
                        }
                        /* Scale to max(rgb) = 1. */
                        jmax = std::max(jr, std::max(jg, jb));
                        if (jmax > 0) {
                            jr = jr / jmax;
                            jg = jg / jmax;
                            jb = jb / jmax;
                        }
                        /* gamma correct from linear rgb to nonlinear rgb. */
                        //gamma_correct_rgb(cs, &jr, &jg, &jb);
                        r = static_cast<int>(mx * jr);
                        g = static_cast<int>(mx * jg);
                        b = static_cast<int>(mx * jb);
                        PPM_ASSIGN(pixels[y][x], (pixval)r, (pixval)g, (pixval)b);
                    }
                }
            }
        }
    }
}