#ifndef ANDROIDUTILS_P_H
#define ANDROIDUTILS_P_H

#include "androidutils.h"

class AndroidUtilsPrivate
{
public:
    static void showToastMessage(const QString &text, int duration);

    static QColor statusBarColor;
};

#endif // ANDROIDUTILS_P_H
