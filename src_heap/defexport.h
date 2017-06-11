#pragma once

#include "OEMBase.h"

#if (defined(ES_WINDOWS))
#ifdef HEAP_LIB_COMPILE
#define HEAP_EXPORT _declspec(dllexport)
#define EXTERN_HEAP_EXPORT   extern JUNK_EXPORT
#else
#define HEAP_EXPORT
#endif
#endif