#include "libanalog.h"

ErrorDialog *errorDialog;

LibAnalog::LibAnalog()
{
    errorDialog = MvTest::errDialogObj;
}

int LibAnalog::mccAIn(QString &params, DaqDeviceHandle deviceHandle,
                          int channel, int iMode, int aiFlags, int Gain, double &dataValue)
{
    int err;
    QString funcName, argString, argVals;
    double data;
    AiInputMode inputMode;
    Range range;
    AInFlag flags;
    QTime t;
    QString sStartTime;

    inputMode = (AiInputMode)iMode;
    range = (Range)Gain;
    flags = (AInFlag)aiFlags;
    funcName = "ulAIn";
    argString = "(boardNum, Chan, inputMode, range, flags, &DataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAIn(deviceHandle, channel, inputMode, range, flags, &data);
    argVals = QString("(%1, %2, %3, %4, %5, %6)")
            .arg(deviceHandle)
            .arg(channel)
            .arg(inputMode)
            .arg(range)
            .arg(flags)
            .arg(data);

    dataValue = data;
    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAIn32(QString &params, DaqDeviceHandle deviceHandle, int channel, int iMode, int aiFlags, int Gain, double &dataValue)
{
    int err;

    err = mccAIn(params, deviceHandle, channel, iMode, aiFlags, Gain, dataValue);
    return err;
}

int LibAnalog::mccAInScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                              int highChan, int inputMode, long samples, double &rate,
                              int range, int options, int flags, double *dblData)
{
    int err, sampsPerChan;
    QString funcName, argString, argVals;
    AiInputMode aiInputMode;
    Range aiRange;
    AInScanFlag aiflags;
    ScanOption scanOpts;
    QTime t;
    QString sStartTime;

    scanOpts = (ScanOption)options;
    aiflags = (AInScanFlag)flags;
    aiRange = (Range)range;
    sampsPerChan = (int)samples;
    aiInputMode = (AiInputMode)inputMode;
    funcName = "ulAInScan";
    argString = "(devHandle, lowChan, highChan, inputMode, range, samples, &rate, options, flags, data)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAInScan(deviceHandle, lowChan, highChan, aiInputMode, aiRange, sampsPerChan, &rate, scanOpts, aiflags, dblData);
    argVals = QString("(%1, %2, %3, %4, %5, %6, %7, %8, %9, %10)")
            .arg(deviceHandle)
            .arg(lowChan)
            .arg(highChan)
            .arg(aiInputMode)
            .arg(aiRange)
            .arg(sampsPerChan)
            .arg(rate)
            .arg(scanOpts)
            .arg(aiflags)
            .arg(dblData[0]);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAInScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                              int highChan, int inputMode, long samples, double &rate,
                              int range, int options, int flags, HGLOBAL intHandle)
{
    //stub for Windows call
    (void) deviceHandle;
    (void) lowChan;
    (void) highChan;
    (void) inputMode;
    (void) samples;
    (void) range;
    (void) options;
    (void) flags;
    (void)intHandle;
    params = "Not valid for Linux";
    rate = 0;
    return MCC_BADBOARD;
}

int LibAnalog::mccAInScanStop(QString &params, DaqDeviceHandle deviceHandle)
{
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ulAInScanStop";
    argString = "(deviceHandle)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAInScanStop(deviceHandle);
    argVals = QString("(%1)")
            .arg(deviceHandle);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAInScanStatus(QString &params, DaqDeviceHandle deviceHandle,
                                    int &status, long &curIndex, long &curCount)
{
    int err;
    ScanStatus scanStatus;
    QString funcName, argString, argVals;
    TransferStatus xferStatus;
    QTime t;
    QString sStartTime;

    funcName = "ulAInScanStatus";
    argString = "(deviceHandle, status, curIndex, curCount)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAInScanStatus(deviceHandle, &scanStatus, &xferStatus);
    curIndex = xferStatus.currentIndex;
    curCount = xferStatus.currentTotalCount;

    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(scanStatus)
            .arg(curCount)
            .arg(curIndex);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    status = (int)scanStatus;
    return err;
}

int LibAnalog::mccAInScanCleanup(QString &params, DaqDeviceHandle deviceHandle)
{
    params = "";
    (void)deviceHandle;
    return MCC_NOERRORS;
}

int LibAnalog::mccTIn(QString &params, DaqDeviceHandle deviceHandle,
                          int channel, TempScale scale, TInFlag flags, double &dataValue)
{
    int err;
    QString funcName, argString, argVals;
    double data;
    QTime t;
    QString sStartTime;

    funcName = "ulTIn";
    argString = "(deviceHandle, channel, scale, flags, &data)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulTIn(deviceHandle, channel, scale, flags, &data);
    argVals = QString("(%1, %2, %3, %4, %5)")
            .arg(deviceHandle)
            .arg(channel)
            .arg(scale)
            .arg(flags)
            .arg(data);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err != MCC_NOERRORS) {
        if (err != MCC_OPENCONNECTION)
            return err;
    }
    dataValue = data;
    err = MCC_NOERRORS;
    return err;
}

int LibAnalog::mccTInArray(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                               int highChan, TempScale scale, TInArrayFlag flags, double *dataValue)
{
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ulTInArray";
    argString = "(deviceHandle, lowChan, highChan, scale, flags, &data)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulTInArray(deviceHandle, lowChan, highChan, scale, flags, dataValue);
    argVals = QString("(%1, %2, %3, %4, %5, %6)")
            .arg(deviceHandle)
            .arg(lowChan)
            .arg(highChan)
            .arg(scale)
            .arg(flags)
            .arg("data");

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err != MCC_NOERRORS) {
        if (err != MCC_OPENCONNECTION)
            return err;
    }
    err = MCC_NOERRORS;
    return err;
}

int LibAnalog::mccLoadQueue(QString &params, DaqDeviceHandle deviceHandle, QHash<int, int> chanList,
                                QHash<int, int> gainList, QHash<int, int> modeList, int numElements)
{
    int err;
    QString funcName, argString, argVals;
    unsigned int numInQueue = numElements;
    QTime t;
    QString sStartTime;

    struct AiQueueElement queue[numElements];
    foreach (int key, chanList.keys()) {
        queue[key].channel = chanList.value(key);
        queue[key].inputMode = (AiInputMode)modeList.value(key);
        queue[key].range = (Range)gainList.value(key);
    }

    funcName = "ulAInLoadQueue";
    argString = "(mDaqDeviceHandle, {channel, mode, range}, numElements)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAInLoadQueue(deviceHandle, queue, numInQueue);
    argVals = QStringLiteral("(%1, {%2, %3, %4}, %5)")
            .arg(deviceHandle)
            .arg(queue[0].channel)
            .arg(queue[0].inputMode)
            .arg(queue[0].range)
            .arg(numInQueue);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAOut(QString &params, DaqDeviceHandle deviceHandle, int channel, int aoFlags, int Gain, double dataValue)
{
    int err;
    QString funcName, argString, argVals;
    Range range;
    AOutFlag flags;
    QTime t;
    QString sStartTime;

    range = (Range)Gain;
    flags = (AOutFlag)aoFlags;
    funcName = "ulAOut";
    argString = "(boardNum, Chan, range, flags, dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAOut(deviceHandle, channel, range, flags, dataValue);
    argVals = QString("(%1, %2, %3, %4, %5)")
            .arg(deviceHandle)
            .arg(channel)
            .arg(range)
            .arg(flags)
            .arg(dataValue);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAOutScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan, int highChan,
                               long samples, double &rate, int range, int options, int flags, double *dblData)
{
    int err, sampsPerChan;
    QString funcName, argString, argVals;
    Range aoRange;
    AOutScanFlag aoflags;
    ScanOption scanOpts;
    QTime t;
    QString sStartTime;
    //double rateReturned;

    scanOpts = (ScanOption)options;
    aoRange = (Range)range;
    sampsPerChan = (int)samples;
    aoflags = (AOutScanFlag)flags;
    funcName = "ulAOutScan";
    argString = "(devHandle, lowChan, highChan, range, samples, &rate, options, flags, data)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";

    err = ulAOutScan(deviceHandle, lowChan, highChan, aoRange, sampsPerChan, &rate, scanOpts, aoflags, dblData);
    argVals = QString("(%1, %2, %3, %4, %5, %6, %7, %8, %9)")
            .arg(deviceHandle)
            .arg(lowChan)
            .arg(highChan)
            .arg(aoRange)
            .arg(sampsPerChan)
            .arg(rate)
            .arg(scanOpts)
            .arg(aoflags)
            .arg(dblData[0]);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAOutScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan, int highChan,
                               long samples, double &rate, int range, int options, int flags, HGLOBAL intHandle)
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
    (void)intHandle;
    return 0;
}

int LibAnalog::mccAOutScanStop(QString &params, DaqDeviceHandle deviceHandle)
{
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ulAOutScanStop";
    argString = "(deviceHandle)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAOutScanStop(deviceHandle);
    argVals = QString("(%1)")
            .arg(deviceHandle);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAOutScanStatus(QString &params, DaqDeviceHandle deviceHandle, int &status, long &curIndex, long &curCount)
{
    int err;
    ScanStatus scanStatus;
    QString funcName, argString, argVals;
    TransferStatus xferStatus;
    QTime t;
    QString sStartTime;

    funcName = "ulAOutScanStatus";
    argString = "(deviceHandle, status, curIndex, curCount)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAOutScanStatus(deviceHandle, &scanStatus, &xferStatus);
    curIndex = xferStatus.currentIndex;
    curCount = xferStatus.currentTotalCount;

    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(scanStatus)
            .arg(curCount)
            .arg(curIndex);

    params = funcName + argString + funcName + argVals;
    errorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    status = (int)scanStatus;
    return err;
}
