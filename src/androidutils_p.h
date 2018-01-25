#ifndef ANDROIDUTILS_P_H
#define ANDROIDUTILS_P_H

#include "androidutils.h"

class AndroidUtilsPrivate
{
public:
    static void showToastMessage(const QString &text, int duration);
    static void changeStatusBarColor(const QColor &color);

    static QColor statusBarColor;
};

#endif // ANDROIDUTILS_P_H
