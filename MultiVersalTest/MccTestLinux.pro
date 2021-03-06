QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = UnitestLinux

CONFIG += c++11

VERSION = 0.7.0.0
DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"
DEFINES += RESOURCE_STRING=\\\":/win/splash/MvSplash.png\\\"

DISTFILES +=

DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "../ullinux/"
INCLUDEPATH += "../"

DEFINES += USES_PLOT
DEFINES += USE_AIN
#DEFINES += USE_AOUT
#DEFINES += USE_CFG
#DEFINES += USE_DIN
#DEFINES += USE_DOUT
#DEFINES += USE_CTR
#DEFINES += USE_MISC

SOURCES += \
    ../childwindow.cpp \
    ../errordialog.cpp \
    ../formdiscover.cpp \
    ../formmvdevice.cpp \
    ../main.cpp \
    ../mccdiscover.cpp \
    ../mvtest.cpp \
    ../ullinux/libdiscover.cpp \
    ../ullinux/libmisc.cpp \
    ../ullinux/libutilities.cpp \
    ../ullinux/libanalog.cpp \
    ../qcustomplot.cpp \
    ../queuedialog.cpp \
    formanalogin.cpp

HEADERS += \
    ../childwindow.h \
    ../errordialog.h \
    ../mvEnums.h \
    ../formdiscover.h \
    ../formmvdevice.h \
    ../mccdiscover.h \
    ../mvtest.h \
    ../ullinux/libTypes.h \
    ../ullinux/libdiscover.h \
    ../ullinux/libenum.h \
    ../ullinux/libmisc.h \
    ../ullinux/libutilities.h \
    ../ullinux/mvErrorMap.h \
    ../ullinux/libanalog.h \
    ../qcustomplot.h \
    ../queuedialog.h \
    formanalogin.h

FORMS += \
    ../errordialog.ui \
    ../formdiscover.ui \
    ../formmvdevice.ui \
    ../mvtest.ui \
    ../queuedialog.ui \
    formanalogin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix: LIBS += -luldaq

RESOURCES += \
    ../resource/UnitestWin.qrc
