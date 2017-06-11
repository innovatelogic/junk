#pragma once

#include "OEMBase.h"

#if (defined(ES_WINDOWS))
#ifdef SORT_LIB_COMPILE
#define SORT_LIB_EXPORT _declspec(dllexport)
#define EXTERN_SORT_LIB_EXPORT   extern JUNK_EXPORT

#else
#define SORT_LIB_EXPORT
#endif
#endif