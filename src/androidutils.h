#ifndef ANDROIDUTILS_H
#define ANDROIDUTILS_H

#include <QObject>
#include <QColor>
#include <QtAndroid>

class AndroidUtils : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor statusBarColor READ statusBarColor WRITE setStatusBarColor)
public:
    explicit AndroidUtils(QObject *parent = nullptr);

    Q_INVOKABLE static void showShortToastMessage(const QString &text);
    Q_INVOKABLE static void showLongToastMessage(const QString &text);

    static QColor statusBarColor();
    static void setStatusBarColor(const QColor &color);

    Q_INVOKABLE static void sharePlainText(const QString &text, const QString &title = "Share");

};

#endif // ANDROIDUTILS_H
