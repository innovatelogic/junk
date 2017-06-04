#pragma once

#include "OEMBase.h"

#if (defined(ES_WINDOWS))
#ifdef LIB_BITS_COMPILE
#define BITS_EXPORT _declspec(dllexport)
#define EXTERN_BITS_EXPORT   extern JUNK_EXPORT

#else
#define BITS_EXPORT
#endif
#endif