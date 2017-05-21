
#include "cie_plot_impl.h"
#include "cie_plot.h"

namespace junk
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

        void CiePlot::Plot()
        {
            m_pImpl->Plot();
        }

        bool CiePlot::Save(const std::wstring &path)
        {
            return m_pImpl->Save(path);
        }
    }
}