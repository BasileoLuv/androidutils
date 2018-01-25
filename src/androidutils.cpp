#include "androidutils.h"
#include "androidutils_p.h"

#define LENGTH_SHORT 0x00000000
#define LENGTH_LONG 0x00000001
#define FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS 0x80000000
#define FLAG_TRANSLUCENT_STATUS 0x04000000
#define ACTION_SEND "android.intent.action.SEND"
#define EXTRA_TEXT "android.intent.extra.TEXT"

#define TO_JSTRING(X) QAndroidJniObject::fromString(X).object<jstring>()

QColor AndroidUtilsPrivate::statusBarColor;

AndroidUtils::AndroidUtils(QObject *parent) : QObject(parent)
{
}

void AndroidUtils::showShortToastMessage(const QString &text)
{
    AndroidUtilsPrivate::showToastMessage(text, LENGTH_SHORT);
}

void AndroidUtils::showLongToastMessage(const QString &text)
{
    AndroidUtilsPrivate::showToastMessage(text, LENGTH_LONG);
}

QColor AndroidUtils::statusBarColor()
{
    return AndroidUtilsPrivate::statusBarColor;
}

void AndroidUtils::setStatusBarColor(const QColor &color)
{
    AndroidUtilsPrivate::statusBarColor = color;
    AndroidUtilsPrivate::changeStatusBarColor(color);
}

void AndroidUtils::sharePlainText(const QString &text, const QString &title)
{
    QtAndroid::runOnAndroidThread([=]() {
        QAndroidJniObject sendIntent("android/content/Intent");

        sendIntent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", TO_JSTRING(ACTION_SEND));
        sendIntent.callObjectMethod("putExtra", "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                                    TO_JSTRING(EXTRA_TEXT), TO_JSTRING(text));
        sendIntent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", TO_JSTRING("text/plain"));

        auto chooser = QAndroidJniObject::callStaticObjectMethod("android/content/Intent", "createChooser",
                                                                 "(Landroid/content/Intent;Ljava/lang/CharSequence;)"
                                                                 "Landroid/content/Intent;",
                                                                 sendIntent.object(), TO_JSTRING(title));

        QtAndroid::androidContext().callMethod<void>("startActivity", "(Landroid/content/Intent;)V", chooser.object());
    });
}

void AndroidUtilsPrivate::showToastMessage(const QString &text, int duration)
{
    if (duration != LENGTH_SHORT and duration != LENGTH_LONG)
        return;

    QtAndroid::runOnAndroidThread([=]() {
        auto context = QtAndroid::androidContext();
        auto jtext = QAndroidJniObject::fromString(text);

        auto toast = QAndroidJniObject::callStaticObjectMethod("android/widget/Toast", "makeText",
                                                               "(Landroid/content/Context;Ljava/lang/CharSequence;I)"
                                                               "Landroid/widget/Toast;",
                                                               context.object(), TO_JSTRING(text), duration);
        toast.callMethod<void>("show");
    });
}

void AndroidUtilsPrivate::changeStatusBarColor(const QColor &color)
{
    if (QtAndroid::androidSdkVersion() < 21)
        return;

    QtAndroid::runOnAndroidThread([=]() {
       auto window = QtAndroid::androidActivity().callObjectMethod("getWindow", "()Landroid/view/Window;");

       window.callMethod<void>("clearFlags", "(I)V", FLAG_TRANSLUCENT_STATUS);
       window.callMethod<void>("addFlags", "(I)V", FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);

       window.callMethod<void>("setStatusBarColor", "(I)V", color.rgba());
    });
}
