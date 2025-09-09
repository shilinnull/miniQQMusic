QT       += core gui multimedia sql

#DEFINES += QT_NO_DEBUG_OUTPUT

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
## 不检查SDK版本
#CONFIG += sdk_no_version_check
## 降低SDK版本
#QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    btform.cpp \
    commonpage.cpp \
    listitembox.cpp \
    lrcpage.cpp \
    main.cpp \
    miniqqmusic.cpp \
    music.cpp \
    musiclist.cpp \
    musicslider.cpp \
    recbox.cpp \
    recboxitem.cpp \
    volumetool.cpp

HEADERS += \
    btform.h \
    commonpage.h \
    listitembox.h \
    lrcpage.h \
    miniqqmusic.h \
    music.h \
    musiclist.h \
    musicslider.h \
    recbox.h \
    recboxitem.h \
    volumetool.h

FORMS += \
    btform.ui \
    commonpage.ui \
    listitembox.ui \
    lrcpage.ui \
    miniqqmusic.ui \
    musicslider.ui \
    recbox.ui \
    recboxitem.ui \
    volumetool.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

DISTFILES += \
    musics/alan/Alan Walker - Alone.mp3 \
    musics/alan/Alan Walker - Fade.mp3 \
    musics/alan/Alan Walker - Faded.mp3 \
    musics/alan/Alan Walker - The Spectre.mp3 \
    musics/alan/Alan Walker&Sabrina Carpenter&Farruko - On My Way(Explicit).mp3 \
    musics/alan/Alan Walker,AuRa,Tomine Harket - Darkside.mp3 \
    musics/alan/Alan Walker,Coldplay - Hymn For The Weekend [Remix].mp3 \
    musics/alan/Alan Walker,Iselin Solheim - Sing Me to Sleep.mp3 \
    musics/alan/Alan Walker,Noah Cyrus,Digital Farm Animals - All Falls Down.mp3 \
    musics/alan/Alan Walker,Sabrina Carpenter,Farruko - On My Way.mp3 \
    musics/alan/Alan Walker,Sorana - Lost Control.mp3
