#ifndef LIBDIGITAL_H
#define LIBDIGITAL_H

#include <QString>
#include "libTypes.h"
#include "libenum.h"
#include "mvErrorMap.h"
#include "libutilities.h"
#include "mvtest.h"
#include "../errordialog.h"

class LibDigital
{
public:
    LibDigital();

            enum {
        DIR_INPUT   = DIGITALIN,
        DIR_OUTPUT  = DIGITALOUT
    };

    int mccDOut(QString &params, DaqDeviceHandle deviceHandle, int portType, unsigned long long dataValue);
    int mccDOutArray(QString &params, DaqDeviceHandle deviceHandle, int portLow, int portHigh, unsigned long long dataValue[]);
    int mccDIn(QString &params, DaqDeviceHandle deviceHandle, int portType, unsigned long long &dataValue);
    int mccDInArray(QString &params, DaqDeviceHandle deviceHandle, int portLow, int portHigh, unsigned long long dataValue[]);
    int mccDBitOut(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, unsigned long long dataValue);
    int mccDBitIn(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, unsigned long long &dataValue);
    int mccDConfigPort(QString &params, DaqDeviceHandle deviceHandle, int portType, int direction);
    int mccDConfigBit(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, int direction);

};

#endif // LIBDIGITAL_H
