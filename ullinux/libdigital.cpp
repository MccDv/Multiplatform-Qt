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
    DigitalPortType port;
    QTime t;
    QString sStartTime;

    port = (DigitalPortType)portType;
    funcName = "ulDOut";
    argString = "(deviceHandle, portType, dataValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDOut(deviceHandle, port, dataValue);
    argVals = QString("(%1, %2, %3)")
            .arg(deviceHandle)
            .arg(port)
            .arg(dataValue);
    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDigital::mccDBitOut(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, unsigned long long dataValue)
{
    int err;
    unsigned int bitValue;
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
    return err;
}

int LibDigital::mccDOutArray(QString &params, DaqDeviceHandle deviceHandle, int portLow, int portHigh, unsigned long long dataValue[])
{
    int err;

    err = 0;
    params = "";
    (void)deviceHandle;
    (void)portLow;
    (void)portHigh;
    (void)dataValue;
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

int LibDigital::mccDIn(QString &params, DaqDeviceHandle deviceHandle,
                           int portType, unsigned long long &dataValue)
{
    int err;
    QString funcName, argString, argVals;
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
    return err;
}

int LibDigital::mccDInArray(QString &params, DaqDeviceHandle deviceHandle, int portLow, int portHigh, unsigned long long dataValue[])
{
    int err;

    err = 0;
    params = "";
    (void)deviceHandle;
    (void)portLow;
    (void)portHigh;
    (void)dataValue;
    /*  TO DO
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
    return err;
}

int LibDigital::mccDConfigPort(QString &params, DaqDeviceHandle deviceHandle,
                                   int portType, int direction)
{
    int err;
    QString funcName, argString, argVals;
    DigitalPortType port;
    DigitalDirection direc;
    QTime t;
    QString sStartTime;

    port = (DigitalPortType)portType;
    direc = (DigitalDirection)direction;
    funcName = "ulDConfigPort";
    argString = "(deviceHandle, portType, direction)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDConfigPort(deviceHandle, port, direc);
    argVals = QString("(%1, %2, %3)")
            .arg(deviceHandle)
            .arg(port)
            .arg(direc);
    params = funcName + argString + funcName + argVals;
    dIOErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));

    return err;
}

int LibDigital::mccDConfigBit(QString &params, DaqDeviceHandle deviceHandle, int portType, int bitNum, int direction)
{

}
