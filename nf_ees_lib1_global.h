#ifndef NF_EES_LIB1_GLOBAL_H
#define NF_EES_LIB1_GLOBAL_H

#include <Windows.h>

#if defined(NF_EES_LIB1_LIBRARY)
// for functions that will be listed in the module definition file
#  define NF_EES_LIB1SHARED_EXPORT extern "C" __declspec(dllexport)
// for functions that will be exported via linker argument (or pragma)
#  define NF_CLASS_EXPORT __declspec(dllexport)
#else
// for functions that will be listed in the module definition file
#  define NF_EES_LIB1SHARED_EXPORT extern "C" __declspec(dllimport)
// for functions that will be exported via linker argument (or pragma)
#  define NF_CLASS_EXPORT __declspec(dllimport)
#endif

#ifndef NF_CALLCODE
#define NF_CALLCODE __stdcall
#endif

#endif // NF_EES_LIB1_GLOBAL_H
