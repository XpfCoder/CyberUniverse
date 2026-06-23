#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SCENEEDITPLUGIN_LIB)
#  define SCENEEDITPLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define SCENEEDITPLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define SCENEEDITPLUGIN_EXPORT
#endif
