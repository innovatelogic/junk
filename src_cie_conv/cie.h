#pragma once

#include "defexport.h"
#include "conv_impl.h"
#include <string>
#include <memory>

namespace junk
{
    namespace cie_conv
    {
        class CIE_EXPORT CieConvertor
        {
            CieConvertor(const CieConvertor&) = delete;
            CieConvertor& operator=(CieConvertor&) = delete;
        
        public:
            CieConvertor();
            virtual ~CieConvertor();

            void Generate();

            bool Save(const std::string &filename);

        protected:
        private:
           // std::unique_ptr<CieConvertorImpl> m_pImpl;
            CieConvertorImpl *m_pImpl;
        };
    }
}