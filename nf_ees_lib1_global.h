#ifndef NF_EES_LIB1_GLOBAL_H
#define NF_EES_LIB1_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NF_EES_LIB1_LIBRARY)
#  define NF_EES_LIB1SHARED_EXPORT extern "C" Q_DECL_EXPORT
#  define NF_CLASS_EXPORT Q_DECL_EXPORT
#else
#  define NF_EES_LIB1SHARED_EXPORT extern "C" Q_DECL_IMPORT
#  define NF_CLASS_EXPORT Q_DECL_IMPORT
#endif

#ifndef NF_CALLCODE
#define NF_CALLCODE __stdcall
#endif

#endif // NF_EES_LIB1_GLOBAL_H
