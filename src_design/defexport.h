#pragma once

#include "OEMBase.h"

#if (defined(ES_WINDOWS))
#ifdef DESIGN_LIB_COMPILE
#define DESIGN_EXPORT _declspec(dllexport)
#define EXTERN_DESIGN_EXPORT   extern JUNK_EXPORT
#else
#define DESIGN_EXPORT
#endif
#endif