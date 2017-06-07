
#include "cie_plot_impl.h"
#include "cie_plot.h"

namespace cie
{
    namespace cie_plot
    {
        CiePlot::CiePlot()
            : m_pImpl(new CiePlotImpl())
        {
        }

        CiePlot::~CiePlot()
        {
            delete m_pImpl;
        }

        bool CiePlot::Plot()
        {
            return m_pImpl->Plot();
        }

        bool CiePlot::Save(const std::wstring &path)
        {
            return m_pImpl->Save(path);
        }

        void CiePlot::Mask(const int *mask, size_t size, size_t samples_count)
        {
            m_pImpl->Mask(mask, size, samples_count);
        }

    }
}