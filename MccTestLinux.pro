QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "ullinux/"

SOURCES += \
    childwindow.cpp \
    errordialog.cpp \
    formdiscover.cpp \
    formmvdevice.cpp \
    main.cpp \
    mccdiscover.cpp \
    mvtest.cpp \
    qcustomplot.cpp \
    ullinux/libdiscover.cpp \
    ullinux/libmisc.cpp \
    ullinux/libutilities.cpp

HEADERS += \
    childwindow.h \
    errordialog.h \
    formdiscover.h \
    formmvdevice.h \
    mccdiscover.h \
    mvtest.h \
    qcustomplot.h \
    ullinux/libdiscover.h \
    ullinux/libmisc.h \
    ullinux/libutilities.h \
    ullinux/ulenum.h

FORMS += \
    errordialog.ui \
    formdiscover.ui \
    formmvdevice.ui \
    mvtest.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix: LIBS += -luldaq
