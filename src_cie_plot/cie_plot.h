#pragma once

#include "defexport.h"
#include <string>
#include <memory>

namespace cie
{
    namespace cie_plot
    {
        class CIE_EXPORT CiePlot
        {
            CiePlot(const CiePlot&) = delete;
            CiePlot& operator=(CiePlot&) = delete;
        
        public:
            CiePlot();
            virtual ~CiePlot();

            bool Plot();
            bool Save(const std::wstring &path);

            void Mask(const int *mask, size_t size, size_t samples_count);

        protected:
        private:
            //std::unique_ptr<class IPlotImpl> m_pImpl;
            class IPlotImpl *m_pImpl;
        };
    }
}