#pragma once

#include "defexport.h"
#include "conv_impl.h"
#include <string>
#include <memory>

namespace junk
{
    namespace cie_conv
    {
        class CIE_EXPORT CiePlot
        {
            CiePlot(const CiePlot&) = delete;
            CiePlot& operator=(CiePlot&) = delete;
        
        public:
            CiePlot();
            virtual ~CiePlot();

            void Generate();

            bool Save(const std::string &filename);

        protected:
        private:
           // std::unique_ptr<CieConvertorImpl> m_pImpl;
            CiePlotImpl *m_pImpl;
        };
    }
}