#pragma once

#include "../defexport.h"
#include <string>

namespace cie
{
    namespace cie_plot
    {
        class CIE_EXPORT IPlotImpl
        {
            public:
                virtual ~IPlotImpl() {}

                virtual bool Plot() = 0;
                virtual bool Save(const std::wstring &filename) = 0;

                virtual void GaussianBlur() = 0;
                virtual void Mask(const int *mask, size_t size, size_t sample_count) = 0;
        };
    }
}