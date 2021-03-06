QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = UnitestWin

CONFIG += c++11

VERSION = 0.7.0.0
DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"
DEFINES += RESOURCE_STRING=\\\":/win/splash/MvSplash.png\\\"

DISTFILES +=

DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "../ulwin/"
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
    ../ulwin/libdiscover.cpp \
    ../ulwin/libmisc.cpp \
    ../ulwin/libutilities.cpp \
    ../ulwin/libdigital.cpp \
    ../ulwin/libanalog.cpp \
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
    ../ulwin/libTypes.h \
    ../ulwin/libdiscover.h \
    ../ulwin/libenum.h \
    ../ulwin/libmisc.h \
    ../ulwin/libutilities.h \
    ../ulwin/mvErrorMap.h \
    ../ulwin/libdigital.h \
    ../ulwin/libanalog.h \
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

INCLUDEPATH += $$PWD/../../DAQ/C
DEPENDPATH += $$PWD/../../DAQ/C

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/../../DAQ/C/ -lcbw32

RESOURCES += \
    ../resource/UnitestWin.qrc
