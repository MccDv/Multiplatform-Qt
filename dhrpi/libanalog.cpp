#include "libanalog.h"
#include "../mvtest.h"

ErrorDialog *hatAnalogErrorDialog;

LibAnalog::LibAnalog()
{
    hatAnalogErrorDialog = MvTest::errDialogObj;
}

int LibAnalog::mccAIn(QString &params, DaqDeviceHandle deviceHandle,
                          int channel, int iMode, int aiFlags, int Gain, double &dataValue)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    int multiplier, prec, err;
    double data = 0.0;
    uint devType;
    uint8_t address;
    uint32_t options;
    bool ok;

    devType = 0;
    if (params.contains("0x"))
        devType = params.mid(params.indexOf("0x") + 2).toInt(&ok, 16);

    hatName = testUtils->getHatTypeName(devType);
    address = deviceHandle;
    if (iMode != mAiMode) {
        mAiMode = iMode;
        err = aInModeWrite(devType, address, mAiMode);
    }
    if (Gain != mRange) {
        mRange = Gain;
        aInRangeWrite(devType, address, mRange);
    }
    options = aiFlags;

    multiplier = 1;
    prec = 6;
    funcName = hatName.append(": AInRead");
    argString = "(mAddress, curChan, mScanOptions, &data)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc118_a_in_read(address, channel, options, &data);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        multiplier = 1000;
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc134_a_in_read(address, channel, options, &data);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_a_in_read(address, channel, options, &data);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    if(argVals == "")
        argVals = QStringLiteral("(%1, %2, %3, %4)")
                .arg(address)
                .arg(channel)
                .arg(options)
                .arg(data * multiplier, 0, 'f', prec);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if(err == RESULT_SUCCESS)
        dataValue = data * multiplier;
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
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    uint devType;
    bool ok;
    uint8_t address, chanMask;
    uint32_t samplesPerChan, scanOptions;
    int err;

    devType = 0;
    chanMask = lowChan;
    samplesPerChan = samples;
    scanOptions = options;
    if (params.contains("0x"))
        devType = params.mid(params.indexOf("0x") + 2).toInt(&ok, 16);

    address = deviceHandle;
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": AInScanStart");
    argString = "(mAddress, chanMask, mSamplesPerChan, &rate, mScanOptions)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        err = mcc118_a_in_scan_start(address, chanMask, samplesPerChan, rate, scanOptions);
        break;
#ifdef HAT_06
    case HAT_ID_MCC_128:
        err = mcc128_a_in_scan_start(address, chanMask, samplesPerChan, rate, scanOptions);
        break;
#endif //HAT_06
    default:
        argString = "(~)\n";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    argVals = QStringLiteral("(%1, %2, %3, %4, %5)")
            .arg(address)
            .arg(chanMask)
            .arg(samplesPerChan)
            .arg(rate)
            .arg(scanOptions);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
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
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    uint devType;
    bool ok;
    uint8_t address;
    int err;

    devType = 0;
    if (params.contains("0x"))
        devType = params.mid(params.indexOf("0x") + 2).toInt(&ok, 16);

    hatName = testUtils->getHatTypeName(devType);
    address = deviceHandle;
    funcName = hatName.append(": AInScanStop");
    argString = "(mAddress)\n";

    argVals = QString("(%1)").arg(address);
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc118_a_in_scan_stop(address);
        break;
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc172_a_in_scan_stop(address);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_a_in_scan_stop(address);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAInScanCleanup(QString &params, DaqDeviceHandle deviceHandle)
{
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    uint devType;
    bool ok;
    uint8_t address;
    int err;

    devType = 0;
    if (params.contains("0x"))
        devType = params.mid(params.indexOf("0x") + 2).toInt(&ok, 16);

    address = deviceHandle;
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": AInScanCleanup");
    argString = "(address)\n";
    argVals = QStringLiteral("(%1)").arg(address);
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc118_a_in_scan_cleanup(address);
        break;
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc172_a_in_scan_cleanup(address);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_a_in_scan_cleanup(address);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::mccAInScanStatus(QString &params, DaqDeviceHandle deviceHandle,
                                    int &status, long &curIndex, long &curCount)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    uint devType;
    uint8_t address;
    uint16_t statReturned;
    uint32_t numRead;
    int err;
    bool ok;

    status = statReturned;
    curCount = numRead;
    curIndex = 0;
    devType = 0;
    if (params.contains("0x"))
        devType = params.mid(params.indexOf("0x") + 2).toInt(&ok, 16);

    hatName = testUtils->getHatTypeName(devType);
    address = deviceHandle;
    funcName = hatName.append(": AInScanStatus");
    argString = "(mAddress, status, samplesAvailable)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc118_a_in_scan_status(address, &statReturned, &numRead);
        break;
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc172_a_in_scan_status(address, &statReturned, &numRead);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_a_in_scan_status(address, &statReturned, &numRead);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    if(argVals == "")
        argVals = QString("(%1, %2, %3)")
                .arg(address)
                .arg(statReturned)
                .arg(numRead);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if(err == RESULT_SUCCESS) {
        status = statReturned;
        curCount = numRead;
    }
    return err;
}

int LibAnalog::mccTIn(QString &params, DaqDeviceHandle deviceHandle,
                          int channel, TempScale scale, TInFlag flags, double &dataValue)
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)channel;
    (void)scale;
    (void)flags;
    (void)dataValue;
    err = RESULT_SUCCESS;
    return err;
}

int LibAnalog::mccTInArray(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                               int highChan, TempScale scale, TInArrayFlag flags, double *dataValue)
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)lowChan;
    (void)highChan;
    (void)scale;
    (void)flags;
    (void)dataValue;
    err = RESULT_SUCCESS;
    return err;
}

int LibAnalog::mccLoadQueue(QString &params, DaqDeviceHandle deviceHandle, QHash<int, int> chanList,
                                QHash<int, int> gainList, QHash<int, int> modeList, int numElements)
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)chanList;
    (void)gainList;
    (void)modeList;
    (void)numElements;
    err = RESULT_SUCCESS;
    return err;
}

int LibAnalog::mccAOut(QString &params, DaqDeviceHandle deviceHandle, int channel, int aoFlags, int Gain, double dataValue)
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)channel;
    (void)aoFlags;
    (void)Gain;
    (void)dataValue;
    err = RESULT_SUCCESS;
    return err;
}

int LibAnalog::mccAOutScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan, int highChan,
                               long samples, double &rate, int range, int options, int flags, double *dblData)
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)lowChan;
    (void)highChan;
    (void)samples;
    (void)range;
    (void)options;
    (void)flags;
    (void)dblData;
    rate = 0;
    err = RESULT_SUCCESS;
    return err;
}

int LibAnalog::mccAOutScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan, int highChan,
                               long samples, double &rate, int range, int options, int flags, long intHandle)
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

    params = "";
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibAnalog::mccAOutScanStatus(QString &params, DaqDeviceHandle deviceHandle, int &status, long &curIndex, long &curCount)
{
    int err;

    params = "";
    (void)deviceHandle;
    status = 0;
    curIndex = 0;
    curCount = 0;
    err = RESULT_SUCCESS;
    return err;
}

int LibAnalog::getNumAInChans(QString &params, uint16_t devType, int mode)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    int numChans;
    QString hatName;

#ifndef HAT_06
    (void) mode;
#endif
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": numAIChans");
    argString = "() = numChans\n";
    argVals = "()";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        numChans = mcc118_info()->NUM_AI_CHANNELS;
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        numChans = mcc134_info()->NUM_AI_CHANNELS;
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        numChans = mcc172_info()->NUM_AI_CHANNELS;
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        numChans = mcc128_info()->NUM_AI_CHANNELS[mode];
        argVals = QString("(%1)")
                .arg(mode);
        break;
#endif
    default:
        argString = "()";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        numChans = 0;
        break;
    }
    argVals.append(QString(" = %1").arg(numChans));

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return numChans;
}

int32_t LibAnalog::getAInCodeMax(QString &params, uint16_t devType)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    int32_t maxCode;
    QString hatName;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": aInMaxCode");
    argString = "() = maxCode\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxCode = mcc118_info()->AI_MAX_CODE;
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxCode = mcc134_info()->AI_MAX_CODE;
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxCode = mcc172_info()->AI_MAX_CODE;
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxCode = mcc128_info()->AI_MAX_CODE;
        break;
#endif
    default:
        argString = "(~) = 0\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxCode = 0;
        break;
    }
    argVals = QString("() = %1").arg(maxCode);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return maxCode;
}

int32_t LibAnalog::getAInCodeMin(QString &params, uint16_t devType)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    int32_t minCode;
    QString hatName;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": aInMinCode");
    argString = "() = minCode\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minCode = mcc118_info()->AI_MIN_CODE;
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minCode = mcc134_info()->AI_MIN_CODE;
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minCode = mcc172_info()->AI_MIN_CODE;
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minCode = mcc128_info()->AI_MIN_CODE;
        break;
#endif
    default:
        argString = "(~) = 0\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minCode = 0;
        break;
    }
    argVals = QString("() = %1").arg(minCode);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return minCode;
}

double LibAnalog::getAInRangeMax(QString &params, uint16_t devType, uint8_t index)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    double maxRange;
    QString hatName;

    (void)index;
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": aInMaxRange");
    argString = "() = maxRange\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxRange = mcc118_info()->AI_MAX_RANGE;
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxRange = (mcc134_info()->AI_MAX_RANGE) * 1000;
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxRange = mcc172_info()->AI_MAX_RANGE;
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxRange = mcc128_info()->AI_MAX_RANGE[index];
        break;
#endif
    default:
        argString = "(~) = 0\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxRange = 0;
        break;
    }
    argVals = QString("() = %1").arg(maxRange);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return maxRange;
}

double LibAnalog::getAInRangeMin(QString &params, uint16_t devType, uint8_t index)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    double minRange;
    QString hatName;

    (void)index;
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": aInMinRange");
    argString = "() = minRange\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minRange = mcc118_info()->AI_MIN_RANGE;
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minRange = (mcc134_info()->AI_MIN_RANGE) * 1000;
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minRange = mcc172_info()->AI_MIN_RANGE;
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minRange = mcc128_info()->AI_MIN_RANGE[index];
        break;
#endif
    default:
        argString = "(~) = 0\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minRange = 0;
        break;
    }
    argVals = QString("() = %1").arg(minRange);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return minRange;
}

double LibAnalog::getAInVoltsMax(QString &params, uint16_t devType, uint8_t index)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    double maxVolts;

    (void)index;
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": aInMaxVolts");
    argString = "() = maxVolts\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxVolts = mcc118_info()->AI_MAX_VOLTAGE;
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxVolts = (mcc134_info()->AI_MAX_VOLTAGE) * 1000;
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxVolts = mcc172_info()->AI_MAX_VOLTAGE;
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxVolts = mcc128_info()->AI_MAX_VOLTAGE[index];
        break;
#endif
    default:
        argString = "(~) = 0\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        maxVolts = 0;
        break;
    }
    argVals = "()";

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return maxVolts;
}

double LibAnalog::getAInVoltsMin(QString &params, uint16_t devType, uint8_t index)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    double minVolts;

    (void)index;
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": aInMinVolts");
    argString = "() = minVolts\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minVolts = mcc118_info()->AI_MIN_VOLTAGE;
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minVolts = (mcc134_info()->AI_MIN_VOLTAGE) * 1000;
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minVolts = mcc172_info()->AI_MIN_VOLTAGE;
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minVolts = mcc128_info()->AI_MIN_VOLTAGE[index];
        break;
#endif
    default:
        argString = "(~) = 0\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        minVolts = 0;
        break;
    }
    argVals = "()";

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return minVolts;
}

int LibAnalog::getNumAOutChans(QString &params, uint16_t devType)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    int numChans;
    QString hatName;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": numAOChans");
    argString = "() = numChans\n";
    switch (devType) {
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        numChans = mcc152_info()->NUM_AO_CHANNELS;
        break;
    default:
        argString = "(~) = numChans\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        numChans = 0;
        argVals = "(~) = ~0";
        break;
    }

    if(argVals == "")
        argVals = QString("() = %1").arg(numChans);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return numChans;
}

int LibAnalog::getAOutCodeMax(QString &params, uint16_t devType)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    int codeMax;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": AOutCodeMax");
    argString = "() = AoCode\n";
    switch (devType) {
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        codeMax = mcc152_info()->AO_MAX_CODE;
        break;
    default:
        argString = "(~) = AoCode\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        codeMax = 0;
        argVals = "(~) = ~0";
        break;
    }
    if(argVals == "")
        argVals = QString("() = %1").arg(codeMax);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return codeMax;
}

int LibAnalog::getAOutCodeMin(QString &params, uint16_t devType)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    int codeMin;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": AOutCodeMin");
    argString = "() = AoMinCode\n";
    switch (devType) {
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        codeMin = mcc152_info()->AO_MIN_CODE;
        break;
    default:
        argString = "(~) = AoMinCode\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        codeMin = 0;
        argVals = "(~) = ~0";
        break;
    }

    if(argVals == "")
        argVals = QString("() = %1").arg(codeMin);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return codeMin;
}

double LibAnalog::getAOutVoltsMin(QString &params, uint16_t devType)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    double voltsMin;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": AOutVoltsMin");
    argString = "() = AoMinVolts\n";
    switch (devType) {
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        voltsMin = mcc152_info()->AO_MIN_VOLTAGE;
        break;
    default:
        argString = "(~) = AoMinVolts\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        voltsMin = 0;
        argVals = "(~) = ~0";
        break;
    }
    if(argVals == "")
        argVals = QString("() = %1").arg(voltsMin);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return voltsMin;
}

double LibAnalog::getAOutVoltsMax(QString &params, uint16_t devType)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    double voltsMax;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": AOutVoltsMax");
    argString = "() = AoMaxVolts\n";
    switch (devType) {
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        voltsMax = mcc152_info()->AO_MAX_VOLTAGE;
        break;
    default:
        argString = "(~) = AoMaxVolts\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        voltsMax = 0;
        argVals = "(~) = ~0";
        break;
    }

    if(argVals == "")
        argVals = QString("() = %1").arg(voltsMax);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return voltsMax;
}

double LibAnalog::getAOutRangeMax(QString &params, uint16_t devType)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    double voltsMax;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": AOutRangeMax");
    argString = "() = AoMaxRange\n";
    switch (devType) {
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        voltsMax = mcc152_info()->AO_MAX_RANGE;
        break;
    default:
        argString = "(~) = AoMaxRange\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        voltsMax = 0;
        argVals = "(~) = ~0";
        break;
    }

    if(argVals == "")
        argVals = QString("() = %1").arg(voltsMax);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return voltsMax;
}

double LibAnalog::getAOutRangeMin(QString &params, uint16_t devType)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    double voltsMin;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": AOutRangeMin");
    argString = "() = AoMinRange\n";
    switch (devType) {
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        voltsMin = mcc152_info()->AO_MIN_RANGE;
        break;
    default:
        argString = "(~) = AoMinRange\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        voltsMin = 0;
        argVals = "(~) = ~0";
        break;
    }

    if(argVals == "")
        argVals = QString("() = %1").arg(voltsMin);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return voltsMin;
}

int LibAnalog::aInRead(QString &params, uint16_t devType, uint8_t address, uint8_t chan, uint32_t options, double &value)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    int multiplier, prec, err;
    double data = 0.0;

    value = 0.0;
    multiplier = 1;
    prec = 6;
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": AInRead");
    argString = "(mAddress, curChan, mScanOptions, &data)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc118_a_in_read(address, chan, options, &data);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        multiplier = 1000;
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc134_a_in_read(address, chan, options, &data);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_a_in_read(address, chan, options, &data);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    if(argVals == "")
        argVals = QStringLiteral("(%1, %2, %3, %4)")
                .arg(address)
                .arg(chan)
                .arg(options)
                .arg(data * multiplier, 0, 'f', prec);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if(err == RESULT_SUCCESS)
        value = data * multiplier;
    return err;
}

#ifdef HAT_06

int LibAnalog::aInModeRead(uint16_t devType, uint8_t address, uint8_t &mode)
{
    int err;
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName, params;

    hatName = testUtils->getHatTypeName(devType);

    funcName = hatName.append(": modeRead");
    argString = "(mAddress, mode)\n";
    switch (devType) {
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_a_in_mode_read(address, &mode);
        break;
    default:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        break;
    }
    argVals = QStringLiteral("(%1, %2)")
            .arg(address)
            .arg(mode);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::aInModeWrite(uint16_t devType, uint8_t address, uint8_t mode)
{
    int err;
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName, params;

    hatName = testUtils->getHatTypeName(devType);

    funcName = hatName.append(": modeWrite");
    argString = "(mAddress, mode)\n";
    switch (devType) {
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_a_in_mode_write(address, mode);
        break;
    default:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        break;
    }
    argVals = QStringLiteral("(%1, %2)")
            .arg(address)
            .arg(mode);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::aInRangeRead(uint16_t devType, uint8_t address, uint8_t &range)
{
    int err;
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName, params;

    hatName = testUtils->getHatTypeName(devType);

    funcName = hatName.append(": rangeRead");
    argString = "(mAddress, &range)\n";
    switch (devType) {
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_a_in_range_read(address, &range);
        break;
    default:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        break;
    }
    argVals = QStringLiteral("(%1, %2)")
            .arg(address)
            .arg(range);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibAnalog::aInRangeWrite(uint16_t devType, uint8_t address, uint8_t range)
{
    int err;
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName, params;

    hatName = testUtils->getHatTypeName(devType);

    funcName = hatName.append(": rangeWrite");
    argString = "(mAddress, range)\n";
    switch (devType) {
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_a_in_range_write(address, range);
        break;
    default:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        break;
    }
    argVals = QStringLiteral("(%1, %2)")
            .arg(address)
            .arg(range);

    params = funcName + argString + funcName + argVals;
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

#else

int LibAnalog::aInModeRead(uint16_t devType, uint8_t address, uint8_t &value)
{
    (void)devType;
    (void)address;
    (void)value;
    return RESULT_INVALID_DEVICE;
}

int LibAnalog::aInModeWrite(uint16_t devType, uint8_t address, uint8_t value)
{
    (void)devType;
    (void)address;
    (void)value;
    return RESULT_INVALID_DEVICE;
}

int LibAnalog::aInRangeRead(uint16_t devType, uint8_t address, uint8_t &value)
{
    (void)devType;
    (void)address;
    (void)value;
    return RESULT_INVALID_DEVICE;
}

int LibAnalog::aInRangeWrite(uint16_t devType, uint8_t address, uint8_t value)
{
    (void)devType;
    (void)address;
    (void)value;
    return RESULT_INVALID_DEVICE;
}

#endif
