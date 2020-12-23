#include "libdigital.h"

ErrorDialog *dIOErrorDialog;

LibDigital::LibDigital()
{
    dIOErrorDialog = MvTest::errDialogObj;
}

int LibDigital::mccDOut(QString &params, DaqDeviceHandle deviceHandle, int portType, unsigned long long dataValue)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    uint devType;
    int err;
    (void)portType;
    uint8_t portValue;
    bool ok;

    devType = 0;
    portValue = dataValue;
    if (params.contains("0x"))
        devType = params.mid(params.indexOf("0x") + 2).toInt(&ok, 16);

    switch (devType) {
    case HAT_ID_MCC_152:
        hatName = testUtils->getHatTypeName(devType);
#ifdef HAT_05
        funcName = hatName.append(": dioOutputWriteAll");
        argString = "(mAddress, value)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc152_dio_output_write_port(deviceHandle, portValue);
#endif  //HAT_05
        break;
    default:
        argString = "(~) = dioChans\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~) = ~0";
        break;
    }

    if(argVals == "")
        argVals = QString("%1, %2")
                .arg(deviceHandle)
                .arg(portValue);

    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDigital::mccDBitOut(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, unsigned long long dataValue)
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)portType;
    (void)bitNum;
    (void)dataValue;
    /*    unsigned int bitValue;
    QString funcName, argString, argVals;
    DigitalPortType port;
    QTime t;
    QString sStartTime;

    port = (DigitalPortType)portType;
    bitValue = dataValue;
    funcName = "ulDBitOut";
    argString = "(deviceHandle, portType, bitNum, dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDBitOut(deviceHandle, port, bitNum, bitValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(port)
            .arg(bitNum)
            .arg(dataValue);
    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    */
    err = RESULT_SUCCESS;
    return err;
}

int LibDigital::mccDOutArray(QString &params, DaqDeviceHandle deviceHandle, int portLow, int portHigh, unsigned long long dataValue[])
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)portLow;
    (void)portHigh;
    (void)dataValue;
/*
    err = 0;
    params = "";
    (void)deviceHandle;
    (void)portLow;
    (void)portHigh;
    (void)dataValue;
    //  TO DO
    QString funcName, argString, argVals;
    USHORT digValue;
    QTime t;
    QString sStartTime;

    digValue = dataValue;
    funcName = "cbDOutArray";
    argString = "(boardNum, portLow, portHigh, dataValue[])\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbDOutArray(deviceHandle, portLow, portHigh, digValue);
    argVals = QString("(%1, %2, %3)")
            .arg(deviceHandle)
            .arg(portType)
            .arg(digValue);
    params = funcName + argString + funcName + argVals;

    dataValue = digValue;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    */
    err = RESULT_SUCCESS;
    return err;
}

int LibDigital::mccDIn(QString &params, DaqDeviceHandle deviceHandle,
                           int portType, unsigned long long &dataValue)
{
    int err;
    params = "";
    (void)deviceHandle;
    (void)portType;
    (void)dataValue;

    /*    QString funcName, argString, argVals;
    DigitalPortType port;
    QTime t;
    QString sStartTime;

    port = (DigitalPortType)portType;
    funcName = "ulDIn";
    argString = "(deviceHandle, portType, &dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDIn(deviceHandle, port, &dataValue);
    argVals = QString("(%1, %2, %3)")
            .arg(deviceHandle)
            .arg(port)
            .arg(dataValue);
    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDigital::mccDBitIn(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, unsigned long long &dataValue)
{
    int err;
    unsigned int bitValue;
    QString funcName, argString, argVals;
    DigitalPortType port;
    QTime t;
    QString sStartTime;

    port = (DigitalPortType)portType;
    bitValue = dataValue;
    funcName = "ulDBitIn";
    argString = "(deviceHandle, portType, bitNum, dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDBitIn(deviceHandle, port, bitNum, &bitValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(port)
            .arg(bitNum)
            .arg(dataValue);
    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    dataValue = bitValue;
    */
    err = RESULT_SUCCESS;
    return err;
}

int LibDigital::mccDInArray(QString &params, DaqDeviceHandle deviceHandle, int portLow, int portHigh, unsigned long long dataValue[])
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)portLow;
    (void)portHigh;
    (void)dataValue;
/*    err = 0;
    params = "";
    (void)deviceHandle;
    (void)portLow;
    (void)portHigh;
    (void)dataValue;
    //  TO DO
    QString funcName, argString, argVals;
    USHORT digValue;
    QTime t;
    QString sStartTime;

    digValue = dataValue;
    funcName = "cbDInArray";
    argString = "(boardNum, portLow, portHigh, dataValue[])\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbDOutArray(deviceHandle, portLow, portHigh, digValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(portType)
            .arg(digValue);
    params = funcName + argString + funcName + argVals;

    dataValue = digValue;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    */
    err = RESULT_SUCCESS;
    return err;
}

int LibDigital::mccDConfigPort(QString &params, DaqDeviceHandle deviceHandle,
                                   int portType, int direction)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    uint devType;
    uint8_t configItem;
    int err;
    bool ok;

    configItem = portType;
    devType = 0;
    if (params.contains("0x"))
        devType = params.mid(params.indexOf("0x") + 2).toInt(&ok, 16);

    switch (devType) {
#ifdef HAT_05
    case HAT_ID_MCC_152:
        hatName = testUtils->getHatTypeName(devType);
        switch (configItem) {
        case DIO_DIRECTION:
            funcName = hatName.append(": dioOutputWriteAll");
            argString = "(mAddress, value)\n";
            sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
            err = mcc152_dio_config_write_port(deviceHandle, configItem, direction);
            break;
        default:
            break;
        }
        break;
#endif
    default:
        argString = "(~) = dioChans\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~) = ~0";
        break;
    }

    if(argVals == "")
        argVals = QString("%1, %2")
                .arg(deviceHandle)
                .arg(direction);

    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDigital::mccDConfigBit(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, int direction)
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)portType;
    (void)bitNum;
    (void)direction;
    /*    QString funcName, argString, argVals;
    DigitalPortType port;
    DigitalDirection direc;
    QTime t;
    QString sStartTime;

    port = (DigitalPortType)portType;
    direc = (DigitalDirection)direction;
    funcName = "ulDConfigBit";
    argString = "(deviceHandle, portType, bitNum, direction)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDConfigBit(deviceHandle, port, bitNum, direc);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(port)
            .arg(bitNum)
            .arg(direc);
    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
*/
    err = RESULT_SUCCESS;
    return err;
}
