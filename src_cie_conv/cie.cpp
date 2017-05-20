
#include "conv_impl.h"
#include "cie.h"

namespace junk
{
    namespace cie_conv
    {
        CiePlot::CiePlot()
            : m_pImpl(new CiePlotImpl())
        {
        }

        CiePlot::~CiePlot()
        {
            delete m_pImpl;
        }

        void CiePlot::Generate()
        {
            m_pImpl->Generate();
        }

        bool CiePlot::Save(const std::string &filename)
        {
            return m_pImpl->Save(filename);
        }
    }
}