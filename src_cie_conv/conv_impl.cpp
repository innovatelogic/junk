#include "conv_impl.h"
#include "mathlib.h"
#include <stdio.h>

namespace junk
{
    namespace cie_conv
    {
        CieConvertorImpl::CieConvertorImpl()
            : SIZE_ROWS(1024)
            , SIZE_COLS(1024)
        {
            pixels = new pixel*[SIZE_ROWS];
            for (size_t r = 0; r < SIZE_ROWS; r++) {
                pixels[r] = new pixel[SIZE_COLS];
            }
        }

        CieConvertorImpl::~CieConvertorImpl()
        {

        }

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

        void CieConvertorImpl::Generate()
        {
            makeAllBlack(pixels, SIZE_COLS, SIZE_ROWS);

           /* for (size_t i = 0; i < SIZE_X; i++)
            {
                for (size_t j = 0; j < SIZE_Y; j++)
                {

                }
            }*/
        }
    }
}