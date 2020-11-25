#include "libanalog.h"

ErrorDialog *errorDialog;

LibAnalog::LibAnalog()
{
    errorDialog = MvTest::errDialogObj;
}

int LibAnalog::mccAIn(QString &params, DaqDeviceHandle deviceHandle, int channel,
                            int iMode, int aiFlags, int Gain, double &dataValue)
{
    int err;
    QString funcName, argString, argVals;
    USHORT data;
    QTime t;
    QString sStartTime;

    err = setInputMode(params, deviceHandle, iMode);

    funcName = "cbAIn";
    argString = "(boardNum, Chan, Gain, &DataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbAIn(deviceHandle, channel, Gain, &data);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(channel)
            .arg(Gain)
            .arg(data);
    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err != MCC_NOERRORS) {
        dataValue = (double)data;
        return err;
    }

    if (aiFlags != AInFlag::AIN_FF_NOSCALEDATA) {
        //  return engineering units
        float engUnits;
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = cbToEngUnits(deviceHandle, Gain, data, &engUnits);
        if (err != MCC_NOERRORS) {
            funcName = "cbToEngUnits";
            argString = "(deviceHandle, Gain, data, &engUnits)\n";
            argVals = QString("(%1, %2, %3, %4)")
                    .arg(deviceHandle)
                    .arg(Gain)
                    .arg(data)
                    .arg(engUnits);
            params = funcName + argString + funcName + argVals;
            errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
            return err;
        }
        dataValue = engUnits;
    } else
        dataValue = (double)data;
    return err;
}

HGLOBAL LibAnalog::mccGetScaledBuf(QString &params, long numPoints)
{
    QString funcName, argString, argVals;
    HGLOBAL handle;
    QTime t;
    QString sStartTime;

    funcName = "cbScaledWinBufAlloc";
    argString = "(numPoints)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    handle = cbScaledWinBufAlloc(numPoints);
    argVals = QString("(%1)")
            .arg(numPoints);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + "0");
    return handle;
}

int LibAnalog::mccFreeBuf(QString &params, HGLOBAL handle)
{
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbWinBufFree";
    argString = "(handle)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbWinBufFree(handle);
    argVals = QString("(%1)").arg("handle");

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAInScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                                int highChan, int inputMode, long samples, double &rate,
                                int range, int options, int flags, HGLOBAL intHandle)
{
    int err;
    QString funcName, argString, argVals;
    long scanRate;
    QTime t;
    QString sStartTime;
    (void)flags;

    err = setInputMode(params, deviceHandle, inputMode);
    if (err != MCC_NOERRORS)
        return err;

    scanRate = (long)rate;
    funcName = "cbAInScan";
    argString = "(devHandle, lowChan, highChan, samples, &rate, range, data, options)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbAInScan(deviceHandle, lowChan, highChan, samples, &scanRate, range, intHandle, options);
    argVals = QString("(%1, %2, %3, %4, %5, %6, %7, %8)")
            .arg(deviceHandle)
            .arg(lowChan)
            .arg(highChan)
            .arg(samples)
            .arg(rate)
            .arg(range)
            .arg("intHandle")
            .arg(options);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAInScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                                int highChan, int inputMode, long samples, double &rate,
                                int range, int options, int flags, double *dblData)
{
    //stub for Linux call
    (void) deviceHandle;
    (void) lowChan;
    (void) highChan;
    (void) inputMode;
    (void) samples;
    (void) range;
    (void) options;
    (void) flags;
    (void) dblData;
    rate = 0;
    params = "Not valid for Windows";
    return BADBOARD;
}

int LibAnalog::mccAInScanStatus(QString &params, DaqDeviceHandle deviceHandle,
                                      int &status, long &curIndex, long &curCount)
{
    int err;
    SHORT stat;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbGetStatus";
    argString = "(boardNum, status, curCount, curIndex, function)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbGetStatus(deviceHandle, &stat, &curCount, &curIndex, AIFUNCTION);
    argVals = QString("(%1, %2, %3, %4, %5)")
            .arg(deviceHandle)
            .arg(stat)
            .arg(curCount)
            .arg(curIndex)
            .arg(AIFUNCTION);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    status = stat;
    return err;
}

int LibAnalog::mccAInScanStop(QString &params, DaqDeviceHandle deviceHandle)
{
    int err;
    QString funcName, argString, argVals;
    QString sStartTime;
    QTime t;

    funcName = "cbStopBackground";
    argString = "(boardNum, function)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbStopBackground(deviceHandle, AIFUNCTION);
    argVals = QString("(%1, %2)")
            .arg(deviceHandle)
            .arg(AIFUNCTION);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccTIn(QString &params, DaqDeviceHandle deviceHandle,
                            int channel, TempScale scale, TInFlag flags, double &dataValue)
{
    int err;
    QString funcName, argString, argVals;
    float data;
    QTime t;
    QString sStartTime;

    funcName = "cbTIn";
    argString = "(boardNum, Chan, scale, &data, flags)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbTIn(deviceHandle, channel, scale, &data, flags);
    argVals = QString("(%1, %2, %3, %4, %5)")
            .arg(deviceHandle)
            .arg(channel)
            .arg(scale)
            .arg(data)
            .arg(flags);

    params = funcName + argString + funcName + argVals;
    if (err != MCC_NOERRORS) {
        if (err != MCC_OPENCONNECTION)
            return err;
    }

    if (flags == TIN_FF_WAIT_FOR_NEW_DATA) {
    }
    dataValue = (double)data;
    err = MCC_NOERRORS;
    return err;
}

int LibAnalog::mccTInArray(QString &params, DaqDeviceHandle deviceHandle,
                            int lowChan, int highChan, TempScale scale, TInArrayFlag flags, double *dataValue)
{
    int err, options, numChans;
    QString funcName, argString, argVals;
    float *data;
    QTime t;
    QString sStartTime;

    numChans = (highChan - lowChan) + 1;
    data = new float[numChans];
    options = (int)flags;
    funcName = "cbTInScan";
    argString = "(deviceHandle, lowChan, highChan, scale, flags, &data)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbTInScan(deviceHandle, lowChan, highChan, scale, data, options);
    argVals = QString("(%1, %2, %3, %4, %5, %6)")
            .arg(deviceHandle)
            .arg(lowChan)
            .arg(highChan)
            .arg(scale)
            .arg("data")
            .arg(options);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err != MCC_NOERRORS) {
        if (err != MCC_OPENCONNECTION)
            return err;
    }

    for (int i = 0; i < numChans; i++) {
        dataValue[i] = (double)data[i];
    }
    delete[] data;
    err = MCC_NOERRORS;
    return err;
}

int LibAnalog::mccLoadQueue(QString &params, DaqDeviceHandle deviceHandle,
                                  QHash<int, int> chanList, QHash<int, int> gainList, QHash <int, int> modeList, int numElements)
{
    (void)modeList;
    int err;
    QString funcName, argString, argVals;
    short chanArray[numElements];
    short gainArray[numElements];
    QTime t;
    QString sStartTime;

    for (int key = 0; key < numElements; key++) {
        chanArray[key] = chanList.value(key);
        gainArray[key] = gainList.value(key);
    }

    funcName = "cbALoadQueue";
    argString = "(deviceHandle, chanArray, gainArray, numElements)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbALoadQueue(deviceHandle, chanArray, gainArray, numElements);
    argVals = QString("%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(chanArray[0])
            .arg(gainArray[0])
            .arg(numElements);
    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAOut(QString &params, DaqDeviceHandle deviceHandle, int channel, int aoFlags, int Gain, double dataValue)
{
    int err;
    QString funcName, argString, argVals;
    USHORT shortVal;
    QTime t;
    QString sStartTime;
    float floatVal;
    (void)aoFlags;

    floatVal = (float)dataValue;
    //if (aoFlags & AOUT_FF_NOSCALEDATA)
    funcName = "ulAOut";
    argString = "(boardNum, Chan, range, dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbFromEngUnits(deviceHandle, Gain, floatVal, &shortVal);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(Gain)
            .arg(floatVal)
            .arg(shortVal);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err != MCC_NOERRORS)
        return err;

    funcName = "ulAOut";
    argString = "(boardNum, Chan, range, dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbAOut(deviceHandle, channel, Gain, shortVal) ;
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(channel)
            .arg(Gain)
            .arg(shortVal);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAOutScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan, int highChan,
                                 long samples, double &rate, int range, int options, int flags, HGLOBAL intHandle)
{
    int err;
    long scanRate;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    /*
     * to do
     * implement flags
    */
    (void)flags;

    scanRate = (long)rate;
    funcName = "cbAOutScan";
    argString = "(devHandle, lowChan, highChan, samples, &rate, range, memHandle, options)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";

    err = cbAOutScan(deviceHandle, lowChan, highChan, samples, &scanRate, range, intHandle, options);
    argVals = QString("(%1, %2, %3, %4, %5, %6, %7, %8)")
            .arg(deviceHandle)
            .arg(lowChan)
            .arg(highChan)
            .arg(samples)
            .arg(scanRate)
            .arg(range)
            .arg("Handle")
            .arg(options);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAOutScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan, int highChan,
                                 long samples, double &rate, int range, int options, int flags, double *dblData)
{
    params = "";
    rate = 0;
    (void)deviceHandle;
    (void)lowChan;
    (void)highChan;
    (void)samples;
    (void)range;
    (void)options;
    (void)flags;
    (void)dblData;
    return 0;
}

int LibAnalog::mccAOutScanStop(QString &params, DaqDeviceHandle deviceHandle)
{
    int err;
    QString funcName, argString, argVals;
    QString sStartTime;
    QTime t;

    funcName = "cbStopBackground";
    argString = "(boardNum, function)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbStopBackground(deviceHandle, AOFUNCTION);
    argVals = QString("(%1, %2)")
            .arg(deviceHandle)
            .arg(AOFUNCTION);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAOutScanStatus(QString &params, DaqDeviceHandle deviceHandle, int &status, long &curIndex, long &curCount)
{
    int err;
    SHORT stat;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbGetStatus";
    argString = "(boardNum, status, curCount, curIndex, function)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbGetStatus(deviceHandle, &stat, &curCount, &curIndex, AOFUNCTION);
    argVals = QString("(%1, %2, %3, %4, %5)")
            .arg(deviceHandle)
            .arg(stat)
            .arg(curCount)
            .arg(curIndex)
            .arg(AOFUNCTION);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    status = stat;
    return err;
}

int LibAnalog::setInputMode(QString &params, DaqDeviceHandle deviceHandle, int iMode)
{
    int err, inputMode;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    inputMode = AI_DIFFERENTIAL;
    if (iMode == AI_SINGLE_ENDED)
        inputMode = SINGLE_ENDED;

    funcName = "cbAInputMode";
    argString = "(boardNum, inputMode)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbAInputMode(deviceHandle, inputMode);
    argVals = QString("(%1, %2)")
            .arg(deviceHandle)
            .arg(inputMode);
    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}
