
#include "px_canvas.h"
#include "cie_model_helper.h"
#include "cie_plot_impl.h"
#include "px_draw_helper.h"
#include <string>

#pragma warning (disable : 4996)

namespace junk
{
    namespace cie_conv
    {
        //----------------------------------------------------------------------------------------------
        CiePlotImpl::CiePlotImpl()
            : SIZE_ROWS(1024)
            , SIZE_COLS(1024)
            , m_canvas(new Canvas(SIZE_ROWS, SIZE_COLS))
        {
        }

        //----------------------------------------------------------------------------------------------
        CiePlotImpl::~CiePlotImpl()
        {
        }

        //----------------------------------------------------------------------------------------------
        void CiePlotImpl::Plot()
        {
            if (m_canvas)
            {
                m_canvas->FillColor({ 0, 0, 0 }); // feel canvas black

                m_canvas->PlotCIESpace(&CIEsystem);

                m_canvas->DrawPlackanLocus();
            }
        }

        //----------------------------------------------------------------------------------------------
        bool CiePlotImpl::Save(const std::wstring &path)
        {
            bool bResult = false;

            if (m_canvas)
            {
                FILE *fp = _wfopen(path.c_str(), L"wb");
                if (!fp) {
                    return false;
                }

                const size_t n_rows = m_canvas->rows();
                const size_t n_cols = m_canvas->cols();

                fprintf(fp, "P6\n%d %d\n255\n", n_cols, n_rows);
                for (size_t row = 0; row < n_rows; ++row)
                {
                    for (size_t col = 0; col < n_cols; ++col)
                    {
                        static unsigned char color[3];
                        color[0] = m_canvas->data()[row][col].r;  // red 
                        color[1] = m_canvas->data()[row][col].g;  // green
                        color[2] = m_canvas->data()[row][col].b;  // blue 
                        fwrite(color, 1, 3, fp);
                    }
                }
                fclose(fp);
                bResult = true;
            }
            return bResult;
        }
    }
}