#ifndef LIBTYPES_H
#define LIBTYPES_H

#define LIB_PLATFORM    1	//MV_WIN
#include <QString>
#include <QHash>

#define MCC_BAD_BOARD   BADBOARD

#define ON_WINDOWS
#include "..\..\DAQ\C\cbw.h"
typedef int DaqDeviceHandle;
typedef int UlNumDevs;

#define MAX_DEV_COUNT  10

struct MccDaqDeviceDescriptor
{
    char mccProductName[64];
    unsigned int mccProductId;
    DaqDeviceInterface devInterface;
    char mccDevString[64];
    char mccUniqueId[64];
    char reserved[512];
};

typedef enum
{
    InfoTypeGlobal      = 1,
    InfoTypeBoard       = 2,
    InfoTypeDigital     = 3,
    InfoTypeCounter     = 4,
    InfoTypeExpansion   = 5,
    InfoTypeMisc        = 6,
    InfoTypeExpArray	= 7,
    InfoTypeMemory      = 8
}MccCfgType;

#endif // LIBTYPES_H
