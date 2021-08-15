QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/floppymediaplayer.cpp \
    src/utility/windowsutil.cpp

HEADERS += \
    mainwindow.h \
    src/floppymediaplayer.h \
    src/utility/windowsutil.h

FORMS += \
    floppymediaplayer.ui \
    mainwindow.ui

LIBS  += -luser32

TRANSLATIONS += \
    FloppyWallpaper_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
