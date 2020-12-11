#ifndef LIBANALOG_H
#define LIBANALOG_H

#include <QString>
#include <QTime>
#include "libTypes.h"
#include "libenum.h"
#include "mvErrorMap.h"
#include "../mvtest.h"
#include "../errordialog.h"

typedef void *HGLOBAL ;

class LibAnalog
{

public:
    LibAnalog();

    int mccAIn(QString &params, DaqDeviceHandle deviceHandle, int channel,
               int iMode, int aiFlags, int Gain, double &dataValue);
    int mccAInScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                   int highChan, int inputMode, long samples, double &rate,
                   int range, int options, int flags, double *dblData);
    int mccAInScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                   int highChan, int inputMode, long samples, double &rate,
                   int range, int options, int flags, HGLOBAL intHandle);
    int mccAInScanStop(QString &params, DaqDeviceHandle deviceHandle);
    int mccAInScanStatus(QString &params, DaqDeviceHandle deviceHandle,
                         int &status, long &curIndex, long &curCount);

    int mccTIn(QString &params, DaqDeviceHandle deviceHandle, int channel,
               TempScale scale, TInFlag flags, double &dataValue);
    int mccTInArray(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
               int highChan, TempScale scale, TInArrayFlag flags, double *dataValue);
    int mccLoadQueue(QString &params, DaqDeviceHandle deviceHandle, QHash<int, int> chanList,
                     QHash<int, int> gainList, QHash<int, int> modeList, int numElements);

    int mccAOut(QString &params, DaqDeviceHandle deviceHandle, int channel,
               int aoFlags, int Gain, double dataValue);
    int mccAOutScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                   int highChan, long samples, double &rate,
                   int range, int options, int flags, double *dblData);
    int mccAOutScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                   int highChan, long samples, double &rate,
                   int range, int options, int flags, HGLOBAL intHandle);
    int mccAOutScanStop(QString &params, DaqDeviceHandle deviceHandle);
    int mccAOutScanStatus(QString &params, DaqDeviceHandle deviceHandle,
                         int &status, long &curIndex, long &curCount);

private:

};

#endif // LIBANALOG_H
