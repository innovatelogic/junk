#include "conv_impl.h"
#include "mathlib.h"
#include "px_draw_helper.h"
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
        static void
            upvp_to_xy(double   const up,
                double   const vp,
                double * const xc,
                double * const yc) {
            /*----------------------------------------------------------------------------
            Given 1976 coordinates u', v', determine 1931 chromaticities x, y
            -----------------------------------------------------------------------------*/
            *xc = 9 * up / (6 * up - 16 * vp + 12);
            *yc = 4 * vp / (6 * up - 16 * vp + 12);
        }

        static void
            xyz_to_rgb(const struct colorSystem * const cs,
                double                      const xc,
                double                      const yc,
                double                      const zc,
                double *                    const r,
                double *                    const g,
                double *                    const b) {
            /*----------------------------------------------------------------------------
            Given  an additive tricolor system CS, defined by the CIE x and y
            chromaticities of its three primaries (z is derived  trivially  as
            1-(x+y)),  and  a  desired chromaticity (XC, YC, ZC) in CIE space,
            determine the contribution of each primary in a linear combination
            which   sums  to  the  desired  chromaticity.   If  the  requested
            chromaticity falls outside the  Maxwell  triangle  (color  gamut)
            formed  by the three primaries, one of the r, g, or b weights will
            be negative.

            Caller can use constrain_rgb() to desaturate an outside-gamut
            color to the closest representation within the available
            gamut.
            -----------------------------------------------------------------------------*/
            double xr, yr, zr, xg, yg, zg, xb, yb, zb;
            double xw, yw, zw;
            double rx, ry, rz, gx, gy, gz, bx, by, bz;
            double rw, gw, bw;

            xr = cs->xRed;    yr = cs->yRed;    zr = 1 - (xr + yr);
            xg = cs->xGreen;  yg = cs->yGreen;  zg = 1 - (xg + yg);
            xb = cs->xBlue;   yb = cs->yBlue;   zb = 1 - (xb + yb);

            xw = cs->xWhite;  yw = cs->yWhite;  zw = 1 - (xw + yw);

            /* xyz -> rgb matrix, before scaling to white. */
            rx = yg*zb - yb*zg;  ry = xb*zg - xg*zb;  rz = xg*yb - xb*yg;
            gx = yb*zr - yr*zb;  gy = xr*zb - xb*zr;  gz = xb*yr - xr*yb;
            bx = yr*zg - yg*zr;  by = xg*zr - xr*zg;  bz = xr*yg - xg*yr;

            /* White scaling factors.
            Dividing by yw scales the white luminance to unity, as conventional. */
            rw = (rx*xw + ry*yw + rz*zw) / yw;
            gw = (gx*xw + gy*yw + gz*zw) / yw;
            bw = (bx*xw + by*yw + bz*zw) / yw;

            /* xyz -> rgb matrix, correctly scaled to white. */
            rx = rx / rw;  ry = ry / rw;  rz = rz / rw;
            gx = gx / gw;  gy = gy / gw;  gz = gz / gw;
            bx = bx / bw;  by = by / bw;  bz = bz / bw;

            /* rgb of the desired point */
            *r = rx*xc + ry*yc + rz*zc;
            *g = gx*xc + gy*yc + gz*zc;
            *b = bx*xc + by*yc + bz*zc;
        }

        static int
            constrain_rgb(double * const r,
                double * const g,
                double * const b) {
            /*----------------------------------------------------------------------------
            If  the  requested RGB shade contains a negative weight for one of
            the primaries, it lies outside the color  gamut  accessible  from
            the  given  triple  of  primaries.  Desaturate it by adding white,
            equal quantities of R, G, and B, enough to make RGB all positive.
            -----------------------------------------------------------------------------*/
            double w;

            /* Amount of white needed is w = - min(0, *r, *g, *b) */
            w = (0 < *r) ? 0 : *r;
            w = (w < *g) ? w : *g;
            w = (w < *b) ? w : *b;
            w = -w;

            /* Add just enough white to make r, g, b all positive. */
            if (w > 0) {
                *r += w;  *g += w; *b += w;

                return 1;                     /* Color modified to fit RGB gamut */
            }

            return 0;                         /* Color within RGB gamut */
        }

        static void
            gamma_correct(const struct colorSystem * const cs,
                double *                   const c) {
            /*----------------------------------------------------------------------------
            Transform linear RGB values to nonlinear RGB values.

            Rec. 709 is ITU-R Recommendation BT. 709 (1990)
            ``Basic Parameter Values for the HDTV Standard for the Studio and for
            International Programme Exchange'', formerly CCIR Rec. 709.

            For details see
            http://www.inforamp.net/~poynton/ColorFAQ.html
            http://www.inforamp.net/~poynton/GammaFAQ.html
            -----------------------------------------------------------------------------*/
            double gamma;

            gamma = cs->gamma;

            if (gamma == 0.) {
                /* Rec. 709 gamma correction. */
                double cc = 0.018;
                if (*c < cc) {
                    *c *= (1.099 * pow(cc, 0.45) - 0.099) / cc;
                }
                else {
                    *c = 1.099 * pow(*c, 0.45) - 0.099;
                }
            }
            else {
                /* Nonlinear color = (Linear color)^(1/gamma) */
                *c = pow(*c, 1. / gamma);
            }
        }

        //----------------------------------------------------------------------------------------------

        static void
            gamma_correct_rgb(const struct colorSystem * const cs,
                double * const r,
                double * const g,
                double * const b) {
            gamma_correct(cs, r);
            gamma_correct(cs, g);
            gamma_correct(cs, b);
        }

        //----------------------------------------------------------------------------------------------

        static void
            xy_to_upvp(double   const xc,
                double   const yc,
                double * const up,
                double * const vp) {
            /*----------------------------------------------------------------------------
            Given 1931 chromaticities x, y, determine 1976 coordinates u', v'
            -----------------------------------------------------------------------------*/
            *up = 4 * xc / (-2 * xc + 12 * yc + 3);
            *vp = 9 * yc / (-2 * xc + 12 * yc + 3);
        }

        //----------------------------------------------------------------------------------------------

        

       // static ppmd_drawproc average_drawproc;
       

        static bool
            pointsEqual(ppmd_point const a,
                ppmd_point const b) {

            return a.x == b.x && a.y == b.y;
        }

        static ppmd_point
            makePoint(unsigned int const x,
                unsigned int const y) {

            ppmd_point p;

            p.x = x;
            p.y = y;

            return p;
        }

        

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

            ppmd_linep(pixels, cols, rows, maxval,
                makePoint(x0, y0), makePoint(x1, y1), clientData);
        }

        //----------------------------------------------------------------------------------------------

        static void
            computeMonochromeColorLocation(
                double                     const waveLength,
                int                        const pxcols,
                int                        const pxrows,
                bool                       const upvp,
                int *                      const xP,
                int *                      const yP) {

            int const ix = (int)((waveLength - 380) / 5);
            double const px = spectral_chromaticity[ix][0];
            double const py = spectral_chromaticity[ix][1];

            *xP = (int)(px * (pxcols - 1));
            *yP = (int)((pxrows - 1) - py * (pxrows - 1));

        }

        //----------------------------------------------------------------------------------------------

        void
            CieConvertorImpl::drawTongueOutline(pixel ** const pixels,
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
                    ppmd_line(pixels, pixcols, pixrows, Maxval,
                        B(lx, ly), B(icx, icy),
                        (char *)&rgbcolor);
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
        void CieConvertorImpl::fillInTongue(
            pixel **                   const pixels,
                int                        const pixcols,
                int                        const pixrows,
                pixval                     const maxval,
                const struct colorSystem * const cs,
                bool                       const upvp,
                int                        const xBias,
                int                        const yBias,
                bool                       const highlightGamut) {

            int const pxcols = pixcols - xBias;
            int const pxrows = pixrows - yBias;

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
                        PPM_ASSIGN(Bixels(y, x), (pixval)r, (pixval)g, (pixval)b);
                    }
                }
            }
        }
    }
}