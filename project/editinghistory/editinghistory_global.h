#ifndef EDITINGHISTORY_GLOBAL_H
#define EDITINGHISTORY_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtWidgets>
#include <QtGui>


#if defined(EDITINGHISTORY_LIBRARY)
#  define EDITINGHISTORY_EXPORT Q_DECL_EXPORT
#else
#  define EDITINGHISTORY_EXPORT Q_DECL_IMPORT
#endif

#endif // EDITINGHISTORY_GLOBAL_H
