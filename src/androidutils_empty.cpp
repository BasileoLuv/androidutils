#include "androidutils.h"
#include "androidutils_p.h"

#include <QtDebug>

AndroidUtils::AndroidUtils(QObject *parent) : QObject(parent)
{
}

void AndroidUtils::showShortToastMessage(const QString &text)
{
    qDebug() << "Toast message not supported on this platform";
    Q_UNUSED(text)
}

void AndroidUtils::showLongToastMessage(const QString &text)
{
    qDebug() << "Toast message not supported on this platform";
    Q_UNUSED(text)
}

QColor AndroidUtils::statusBarColor()
{
    qDebug() << "Status bar color not supported on this platform";
    return QColor();
}

void AndroidUtils::setStatusBarColor(const QColor &color)
{
    qDebug() << "Status bar color not supported on this platform";
    Q_UNUSED(color)
}

void AndroidUtils::sharePlainText(const QString &text, const QString &title)
{
    qDebug() << "Share is not supported on this platform";
    Q_UNUSED(text)
    Q_UNUSED(title)
}

void AndroidUtilsPrivate::showToastMessage(const QString &text, int duration)
{
    Q_UNUSED(text)
    Q_UNUSED(duration)
}

bool AndroidUtils::statusBarColorAvailable()
{
    return false;
}

bool AndroidUtils::available()
{
    return false;
}
