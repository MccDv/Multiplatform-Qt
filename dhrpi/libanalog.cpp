#include "libanalog.h"
#include "mvtest.h"

ErrorDialog *hatAnalogErrorDialog;

LibAnalog::LibAnalog()
{
    hatAnalogErrorDialog = MvTest::errDialogObj;
}

int LibAnalog::mccAIn(QString &params, DaqDeviceHandle deviceHandle,
                          int channel, int iMode, int aiFlags, int Gain, double &dataValue)
{
    return 0;
}

int LibAnalog::mccAInScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                              int highChan, int inputMode, long samples, double &rate,
                              int range, int options, int flags, double *dblData)
{
    return 0;
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
    return err;
}

int LibAnalog::mccAInScanStatus(QString &params, DaqDeviceHandle deviceHandle,
                                    int &status, long &curIndex, long &curCount)
{
    int err;
    return err;
}

int LibAnalog::mccTIn(QString &params, DaqDeviceHandle deviceHandle,
                          int channel, TempScale scale, TInFlag flags, double &dataValue)
{
    int err;
    return err;
}

int LibAnalog::mccTInArray(QString &params, DaqDeviceHandle deviceHandle, int lowChan,
                               int highChan, TempScale scale, TInArrayFlag flags, double *dataValue)
{
    int err;
    return err;
}

int LibAnalog::mccLoadQueue(QString &params, DaqDeviceHandle deviceHandle, QHash<int, int> chanList,
                                QHash<int, int> gainList, QHash<int, int> modeList, int numElements)
{
    int err;
    return err;
}

int LibAnalog::mccAOut(QString &params, DaqDeviceHandle deviceHandle, int channel, int aoFlags, int Gain, double dataValue)
{
    int err;
    return err;
}

int LibAnalog::mccAOutScan(QString &params, DaqDeviceHandle deviceHandle, int lowChan, int highChan,
                               long samples, double &rate, int range, int options, int flags, double *dblData)
{
    int err, sampsPerChan;
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
    return err;
}

int LibAnalog::mccAOutScanStatus(QString &params, DaqDeviceHandle deviceHandle, int &status, long &curIndex, long &curCount)
{
    int err;
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
    int prec;
    double maxVolts;

    (void)index;
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": aInMaxVolts");
    argString = "() = maxVolts\n";
    prec = 6;
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        maxVolts = mcc118_info()->AI_MAX_VOLTAGE;
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        prec = 9;
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        maxVolts = (mcc134_info()->AI_MAX_VOLTAGE) * 1000;
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        prec = 12;
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        maxVolts = mcc172_info()->AI_MAX_VOLTAGE;
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        prec = 12;
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        maxVolts = mcc128_info()->AI_MAX_VOLTAGE[index];
        break;
#endif
    default:
        argString = "(~) = 0\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
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
    int prec;
    double minVolts;

    (void)index;
    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": aInMinVolts");
    argString = "() = minVolts\n";
    prec = 6;
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        minVolts = mcc118_info()->AI_MIN_VOLTAGE;
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        prec = 9;
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        minVolts = (mcc134_info()->AI_MIN_VOLTAGE) * 1000;
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        prec = 12;
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        minVolts = mcc172_info()->AI_MIN_VOLTAGE;
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        prec = 12;
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        minVolts = mcc128_info()->AI_MIN_VOLTAGE[index];
        break;
#endif
    default:
        argString = "(~) = 0\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
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
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc134_a_in_read(address, chan, options, &data);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc128_a_in_read(address, chan, options, &data);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
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
    hatAnalogErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    if(err == RESULT_SUCCESS)
        value = data * multiplier;
    return err;
}
