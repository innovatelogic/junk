
#include "conv_impl.h"
#include "cie.h"

namespace junk
{
    namespace cie_conv
    {
        CieConvertor::CieConvertor()
            : m_pImpl(new CieConvertorImpl())
        {
        }

        CieConvertor::~CieConvertor()
        {
            delete m_pImpl;
        }

        void CieConvertor::Generate()
        {
            m_pImpl->Generate();
        }

        bool CieConvertor::Save(const std::string &filename)
        {
            return m_pImpl->Save(filename);
        }
    }
}