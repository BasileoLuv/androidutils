INCLUDEPATH += $$PWD
CONFIG += c++17

HEADERS += $$PWD/androidutils.h

android {
    QT += androidextras
    SOURCES += $$PWD/androidutils.cpp
} else {
    SOURCES += $$PWD/androidutils_empty.cpp
}
