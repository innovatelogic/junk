#pragma once

#include "OEMBase.h"

#if (defined(ES_WINDOWS))
#ifdef STACK_LIB_COMPILE
#define STACK_EXPORT _declspec(dllexport)
#define EXTERN_STACK_EXPORT   extern STACK_EXPORT
#else
#define STACK_EXPORT
#endif
#endif