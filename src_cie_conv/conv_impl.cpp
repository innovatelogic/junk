
#include <stdio.h>
#include <algorithm>

#include "px_canvas.h"
#include "cie_model_helper.h"
#include "conv_impl.h"
#include "px_draw_helper.h"

#pragma warning (disable : 4996)

namespace junk
{
    namespace cie_conv
    {
        //----------------------------------------------------------------------------------------------
        CiePlotImpl::CiePlotImpl()
            : SIZE_ROWS(1024)
            , SIZE_COLS(1024)
        {
            m_canvas = new Canvas(SIZE_ROWS, SIZE_COLS);
        }

        //----------------------------------------------------------------------------------------------
        CiePlotImpl::~CiePlotImpl()
        {
            delete m_canvas;
        }

        //----------------------------------------------------------------------------------------------
        bool CiePlotImpl::Save(const std::string &filename)
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
                    color[0] = m_canvas->data()[row][col].r;  // red 
                    color[1] = m_canvas->data()[row][col].g;  // green
                    color[2] = m_canvas->data()[row][col].b;  // blue 
                    fwrite(color, 1, 3, fp);
                }
            }
            fclose(fp);

            return bResult;
        }

        //----------------------------------------------------------------------------------------------
        void CiePlotImpl::Generate()
        {
            if (m_canvas)
            {
                m_canvas->FeelColor({ 0, 0, 0 }); // feel canvas black

                m_canvas->PlotCIESpace(Maxval, &CIEsystem);

                m_canvas->DrawPlackanLocus(Maxval);
            }
        }
    }
}