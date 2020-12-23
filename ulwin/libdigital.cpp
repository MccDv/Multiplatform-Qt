#include "libdigital.h"

ErrorDialog *dIOErrorDialog;

LibDigital::LibDigital()
{
    dIOErrorDialog = MvTest::errDialogObj;
}

int LibDigital::mccDOut(QString &params, DaqDeviceHandle deviceHandle, int portType, unsigned long long dataValue)
{
    int err;
    QString funcName, argString, argVals;
    USHORT digValue;
    QTime t;
    QString sStartTime;

    digValue = dataValue;
    funcName = "cbDOut";
    argString = "(boardNum, portType, dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbDOut(deviceHandle, portType, digValue);
    argVals = QString("(%1, %2, %3)")
            .arg(deviceHandle)
            .arg(portType)
            .arg(digValue);
    params = funcName + argString + funcName + argVals;

    dataValue = digValue;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
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
    err = MCC_NOERRORS;
    /*  TO DO
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
    return err;
}

int LibDigital::mccDBitOut(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, unsigned long long dataValue)
{
    int err;
    QString funcName, argString, argVals;
    USHORT digValue;
    QTime t;
    QString sStartTime;

    digValue = dataValue;
    funcName = "cbDBitOut";
    argString = "(boardNum, portType, bitNum, dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbDBitOut(deviceHandle, portType, bitNum, digValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(portType)
            .arg(bitNum)
            .arg(digValue);
    params = funcName + argString + funcName + argVals;

    dataValue = digValue;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDigital::mccDIn(QString &params, DaqDeviceHandle deviceHandle, int portType, unsigned long long &dataValue)
{
    int err;
    QString funcName, argString, argVals;
    USHORT digValue;
    QTime t;
    QString sStartTime;

    funcName = "cbDIn";
    argString = "(boardNum, portType, &dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbDIn(deviceHandle, portType, &digValue);
    argVals = QString("(%1, %2, %3)")
            .arg(deviceHandle)
            .arg(portType)
            .arg(digValue);
    params = funcName + argString + funcName + argVals;

    dataValue = digValue;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
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
    err = MCC_NOERRORS;
    /*  TO DO
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
    return err;
}

int LibDigital::mccDBitIn(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, unsigned long long &dataValue)
{
    int err;
    QString funcName, argString, argVals;
    USHORT digValue;
    QTime t;
    QString sStartTime;

    digValue = dataValue;
    funcName = "cbDBitIn";
    argString = "(boardNum, portType, bitNum, &dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbDBitIn(deviceHandle, portType, bitNum, &digValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(portType)
            .arg(bitNum)
            .arg(digValue);
    params = funcName + argString + funcName + argVals;

    dataValue = digValue;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDigital::mccDConfigPort(QString &params, DaqDeviceHandle deviceHandle, int portType, int direction)
{
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbDConfigPort";
    argString = "(boardNum, portType, direction)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbDConfigPort(deviceHandle, portType, direction);
    argVals = QString("(%1, %2, %3)")
            .arg(deviceHandle)
            .arg(portType)
            .arg(direction);
    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDigital::mccDConfigBit(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, int direction)
{
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbDConfigBit";
    argString = "(boardNum, portType, bitNum, direction)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbDConfigBit(deviceHandle, portType, bitNum, direction);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(portType)
            .arg(bitNum)
            .arg(direction);
    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}
