#pragma once

#include "OEMBase.h"

#if (defined(ES_WINDOWS))
#ifdef TREES_LIB_COMPILE
#define TREES_EXPORT _declspec(dllexport)
#define EXTERN_TREES_EXPORT   extern JUNK_EXPORT
#else
#define DESIGN_EXPORT
#endif
#endif