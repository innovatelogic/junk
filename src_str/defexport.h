#pragma once

#include "OEMBase.h"

#if (defined(ES_WINDOWS))
#ifdef LIB_COMPILE
#define STR_EXPORT _declspec(dllexport)
#define EXTERN_STR_EXPORT   extern STR_EXPORT

#else
#define STR_EXPORT
#endif
#endif