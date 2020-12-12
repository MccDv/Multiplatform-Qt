QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = UnitestRpi

CONFIG += c++11

VERSION = 0.7.0.0
DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"
DEFINES += RESOURCE_STRING=\\\":/win/splash/MvSplash.png\\\"

DISTFILES +=

DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "../dhrpi/"
INCLUDEPATH += "../"

# MCC 128 development: HAT_06
# MCC 172 development: HAT_05
# MCC 152 development: HAT_04
# MCC 134 development: HAT_03

DEFINES += HAT_03
DEFINES += HAT_04
DEFINES += HAT_05
DEFINES += HAT_06

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
    ../dhrpi/libdiscover.cpp \
    ../dhrpi/libmisc.cpp \
    ../dhrpi/libutilities.cpp \
    ../dhrpi/libanalog.cpp \
    ../qcustomplot.cpp \
    ../queuedialog.cpp \
    formanalogin.cpp

HEADERS += \
    ../childwindow.h \
    ../errordialog.h \
    ../formdiscover.h \
    ../formmvdevice.h \
    ../mccdiscover.h \
    ../mvtest.h \
    ../dhrpi/libdiscover.h \
    ../dhrpi/libmisc.h \
    ../dhrpi/libutilities.h \
    ../dhrpi/mvErrorMap.h \
    ../dhrpi/libTypes.h \
    ../dhrpi/libenum.h \
    ../dhrpi/libanalog.h \
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

target.path = /home/pi
INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../../../../opt/qtrpi/raspbian/sysroot-minimal/usr/lib/ -ldaqhats

INCLUDEPATH += $$PWD/../../../../opt/qtrpi/raspbian/sysroot-minimal/usr/include/daqhats
DEPENDPATH += $$PWD/../../../../opt/qtrpi/raspbian/sysroot-minimal/usr/include/daqhats

RESOURCES += \
    ../resource/UnitestWin.qrc
