#ifndef CGUTILS_GLOBAL_H
#define CGUTILS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CGUTILS_LIBRARY)
#  define CGUTILSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CGUTILSSHARED_EXPORT Q_DECL_IMPORT
#endif

#define CGUTILS_NAMESPACE_BEGIN namespace cgutils {
#define CGUTILS_NAMESPACE_END }

#endif // CGUTILS_GLOBAL_H
