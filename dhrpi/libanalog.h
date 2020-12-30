#ifndef LIBANALOG_H
#define LIBANALOG_H

#include "../errordialog.h"
#include "libutilities.h"

typedef void *HGLOBAL ;

class LibAnalog
{
public:
    LibAnalog();

    int mccAIn(QString &params, DaqDeviceHandle deviceHandle, int channel,
               int iMode, int aiFlags, int Gain, double &dataValue);
    int mccAIn32(QString &params, DaqDeviceHandle deviceHandle, int channel,
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
    int mccAInScanCleanup(QString &params, DaqDeviceHandle deviceHandle);

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
                   int range, int options, int flags, long intHandle);
    int mccAOutScanStop(QString &params, DaqDeviceHandle deviceHandle);
    int mccAOutScanStatus(QString &params, DaqDeviceHandle deviceHandle,
                         int &status, long &curIndex, long &curCount);



    int getNumAInChans(QString &params, uint16_t devType, int mode);
    double getAInVoltsMax(QString &params, uint16_t devType, uint8_t index);
    double getAInVoltsMin(QString &params, uint16_t devType, uint8_t index);
    double getAInRangeMax(QString &params, uint16_t devType, uint8_t index);
    double getAInRangeMin(QString &params, uint16_t devType, uint8_t index);
    int32_t getAInCodeMax(QString &params, uint16_t devType);
    int32_t getAInCodeMin(QString &params, uint16_t devType);

    double getAOutVoltsMax(QString &params, uint16_t devType);
    double getAOutVoltsMin(QString &params, uint16_t devType);
    double getAOutRangeMax(QString &params, uint16_t devType);
    double getAOutRangeMin(QString &params, uint16_t devType);
    int getAOutCodeMax(QString &params, uint16_t devType);
    int getAOutCodeMin(QString &params, uint16_t devType);
    int getNumAOutChans(QString &params, uint16_t devType);

    int aInRead(QString &params, uint16_t devType, uint8_t address, uint8_t chan, uint32_t options, double &value);

private:
    LibUtilities *testUtils;
    int mAiMode = 0;
    int mRange = -1;

    int aInModeRead(uint16_t devType, uint8_t address, uint8_t &mode);
    int aInRangeRead(uint16_t devType, uint8_t address, uint8_t &range);
    int aInModeWrite(uint16_t devType, uint8_t address, uint8_t mode);
    int aInRangeWrite(uint16_t devType, uint8_t address, uint8_t range);
};

#endif // LIBANALOG_H
