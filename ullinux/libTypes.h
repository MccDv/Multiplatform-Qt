#ifndef LIBTYPES_H
#define LIBTYPES_H

#include <QString>
#include <QHash>
#include "uldaq.h"

#define LIB_PLATFORM    2	//MV_LINUX
#define MCC_BAD_BOARD   ERR_BAD_DEV_HANDLE
#define ON_WINDOWS false
typedef unsigned int UlNumDevs;

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
