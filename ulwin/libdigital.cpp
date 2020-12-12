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
