#ifndef LIBDIGITAL_H
#define LIBDIGITAL_H

#include <QString>
#include "libTypes.h"
#include "libenum.h"
#include "MvErrorMap.h"
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
    int mccDIn(QString &params, DaqDeviceHandle deviceHandle, int portType, unsigned long long &dataValue);
    int mccDConfigPort(QString &params, DaqDeviceHandle deviceHandle, int portType, int direction);

};

#endif // LIBDIGITAL_H
