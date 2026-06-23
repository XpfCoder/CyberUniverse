#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COREPLUGIN_LIB)
#  define COREPLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define COREPLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define COREPLUGIN_EXPORT
#endif
