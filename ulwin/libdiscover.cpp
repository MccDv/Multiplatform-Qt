#include "libdiscover.h"
#include "../mvtest.h"

ErrorDialog *discoverErrorDialog;

LibDiscover::LibDiscover()
{
    discoverErrorDialog = MvTest::errDialogObj;
}

int LibDiscover::mccIgnoreInstacal(QString &params)
{
    int err;
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbIgnoreInstaCal";
    argString = "()\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbIgnoreInstaCal();
    argVals = QString("()");

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDiscover::mccGetInstacalDevs(QString &params, QHash<QString, DaqDeviceHandle> &iCalDevs)
{
    int err, configVal, boardNum;
    char chArr[BOARDNAMELEN];
    char* uID = chArr;
    QString funcName;
    QString argString, argVals;
    QString uniqueID;
    QTime t;
    QString sStartTime;

    iCalDevs.clear();
    for (boardNum = 0; boardNum < MAX_DEV_COUNT; boardNum++) {
        funcName = "cbGetConfig";
        argString = "(InfoType, boardNum, index, configItem, &configVal)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = cbGetConfig(BOARDINFO, boardNum, 0, BIBOARDTYPE, &configVal);
        argVals = QStringLiteral("(%1, %2, %3, %4, %5)")
                .arg(BOARDINFO)
                .arg(boardNum)
                .arg(0)
                .arg(BIBOARDTYPE)
                .arg(configVal);

        params = funcName + argString + funcName + argVals;
        discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
        if (err != MCC_NOERRORS)
            break;
        if (configVal > 0) {
            //  Add Instacal device
            int idLength = BOARDNAMELEN;
            funcName = "cbGetConfigString";
            argString = "(InfoType, boardNum, index, configItem, &configVal, &configLen)\n";
            sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
            err = cbGetConfigString(BOARDINFO, boardNum, 0, BIDEVUNIQUEID, uID, &idLength);
            argVals = QStringLiteral("(%1, %2, %3, %4, %5, %6)")
                    .arg(BOARDINFO)
                    .arg(boardNum)
                    .arg(0)
                    .arg(BIDEVUNIQUEID)
                    .arg(uID)
                    .arg(idLength);

            params = funcName + argString + funcName + argVals;
            discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
            if (err != MCC_NOERRORS)
                return err;
            uniqueID = QString("%1").arg(uID);
            iCalDevs.insert(uniqueID, boardNum);
        }
    }
    return err;
}

int LibDiscover::mccGetDaqDeviceInventory(QString &params, DaqDeviceInterface
        interfaceTypes, MccDaqDeviceDescriptor *mccDescriptors, UlNumDevs &numDescriptors)
{
    int err;
    DaqDeviceDescriptor daqDevDescriptors[MAX_DEV_COUNT];
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ulGetDaqDeviceInventory";
    argString = "(interfaceType, devDescriptors, &numDevs)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbGetDaqDeviceInventory(interfaceTypes, daqDevDescriptors, &numDescriptors);
    argVals = QStringLiteral("(%1, %2, %3)")
            .arg(interfaceTypes)
            .arg("devDescriptors")
            .arg(numDescriptors);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));

    for (UlNumDevs devIndex = 0; devIndex < numDescriptors; devIndex++) {
        strcpy(mccDescriptors[devIndex].mccUniqueId, daqDevDescriptors[devIndex].UniqueID);
        mccDescriptors[devIndex].devInterface = daqDevDescriptors[devIndex].InterfaceType;
        strcpy(mccDescriptors[devIndex].mccDevString, daqDevDescriptors[devIndex].DevString);
        mccDescriptors[devIndex].mccProductId = daqDevDescriptors[devIndex].ProductID;
        strcpy(mccDescriptors[devIndex].mccProductName, daqDevDescriptors[devIndex].ProductName);
    }
    return err;
}

DaqDeviceHandle LibDiscover::mccCreateDaqDevice(QString &params,
                        DaqDeviceHandle deviceHandle, MccDaqDeviceDescriptor mccDevDescriptor)
{
    int err;
    QString funcName, argString, argVals;
    DaqDeviceDescriptor devDescriptor;
    QString uID;
    bool ok;
    QTime t;
    QString sStartTime;

    strcpy(devDescriptor.UniqueID, mccDevDescriptor.mccUniqueId);
    devDescriptor.InterfaceType = mccDevDescriptor.devInterface;
    strcpy(devDescriptor.DevString, mccDevDescriptor.mccDevString);
    devDescriptor.ProductID = mccDevDescriptor.mccProductId;
    strcpy(devDescriptor.ProductName, mccDevDescriptor.mccProductName);

    QString tempID = mccDevDescriptor.mccUniqueId;
    uID = tempID.remove(":");
    unsigned long long nUID = uID.toULongLong(&ok, 16);
    if (ok)
        devDescriptor.NUID = nUID;

    funcName = "cbCreateDaqDevice";
    argString = "(boardNum, devDescriptor)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbCreateDaqDevice(deviceHandle, devDescriptor);
    argVals = QString("(%1, %2)")
            .arg(deviceHandle)
            .arg(devDescriptor.ProductName);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err != 0) {
        params.append("@Error: " + QString("%1").arg(err));
        return -1;
    }
    else
        return deviceHandle;
}

int LibDiscover::mccIsDaqDeviceConnected(QString &params, DaqDeviceHandle deviceHandle,
                                QString devUID, int &connected)
{
    (void)deviceHandle;
    int boardNum, err, numDescriptors;
    QString funcName, argString, argVals;
    QString testID;
    DaqDeviceDescriptor devDescriptor, daqDevDescriptors[MAX_DEV_COUNT];
    DaqDeviceInterface interfaceTypes;
    bool idFound = false;
    QTime t;
    QString sStartTime;

    memset(daqDevDescriptors, 0, sizeof(daqDevDescriptors));

    funcName = "cbGetDaqDeviceInventory";
    argString = "(interfaceTypes, daqDevDescriptors, &numDescriptors)\n";

    interfaceTypes = ANY_IFC;
    numDescriptors = MAX_DEV_COUNT;
    connected = 0;
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbGetDaqDeviceInventory(interfaceTypes, daqDevDescriptors, &numDescriptors);
    argVals = QString("(%1, %2, %3)")
            .arg(interfaceTypes)
            .arg("daqDevDescriptors")
            .arg(numDescriptors);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err != MCC_NOERRORS) {
        return 0;
    }
    for (int devIndex = 0; devIndex < numDescriptors; devIndex++) {
        testID = daqDevDescriptors[devIndex].UniqueID;
        if (testID == devUID) {
            devDescriptor = daqDevDescriptors[devIndex];
            idFound = true;
            break;
        }
    }
    if (!idFound)
        return 0;

    funcName = "cbGetBoardNumber";
    argString = "(devDescriptor)\n";

    boardNum = -1;
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    boardNum = cbGetBoardNumber(devDescriptor);
    argVals = QString("(%1) = %2 (connected = %3)")
            .arg(devDescriptor.ProductName)
            .arg(boardNum)
            .arg(boardNum != -1);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (boardNum != -1)
        connected = 1;

    return 0;
}

int LibDiscover::mccConnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle, QString devUID)
{
    /*  This is a fake implementation of the Linux connect function.
     *  It should only be used after an explicit disconnect of an
     *  existing (previously connected) device using the fake
     *  disconnect function below. These paired functions
     *  actually release and re-create the device.          */

    int err, numDescriptors;
    QString funcName, argString, argVals;
    QString testID;
    DaqDeviceDescriptor devDescriptor, daqDevDescriptors[MAX_DEV_COUNT];
    DaqDeviceInterface interfaceTypes;
    bool idFound = false;
    QTime t;
    QString sStartTime;

    memset(daqDevDescriptors, 0, sizeof(daqDevDescriptors));

    funcName = "cbGetDaqDeviceInventory";
    argString = "(interfaceTypes, daqDevDescriptors, &numDescriptors)\n";
    interfaceTypes = ANY_IFC;
    numDescriptors = MAX_DEV_COUNT;
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbGetDaqDeviceInventory(interfaceTypes, daqDevDescriptors, &numDescriptors);
    argVals = QString("(%1, %2, %3)")
            .arg(interfaceTypes)
            .arg("daqDevDescriptors")
            .arg(numDescriptors);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err != MCC_NOERRORS)
        return err;

    for (int devIndex = 0; devIndex < numDescriptors; devIndex++) {
        testID = daqDevDescriptors[devIndex].UniqueID;
        if (testID == devUID) {
            devDescriptor = daqDevDescriptors[devIndex];
            idFound = true;
            break;
        }
    }
    if (!idFound)
        return MCC_BAD_BOARD;

    funcName = "cbCreateDaqDevice";
    argString = "(boardNum, devDescriptor)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbCreateDaqDevice(deviceHandle, devDescriptor);
    argVals = QString("(%1, %2)")
            .arg(deviceHandle)
            .arg(devDescriptor.ProductName);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err != 0)
        return err;

    return 0;
}

int LibDiscover::mccDisconnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle)
{
    /*  Only exists in Windows for compatibility with Linux (see
     *  cbReleaseDaqDevice). Used with the fake connect function
     *  above to emmulate Linux connect/disconnect. These paired
     *  functions actually release and re-create the device.    */

    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbReleaseDaqDevice";
    argString = "(boardNum)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbReleaseDaqDevice(deviceHandle);
    argVals = QString("(%1)")
            .arg(deviceHandle);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDiscover::mccReleaseDaqDevice(QString &params, DaqDeviceHandle deviceHandle)
{
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbReleaseDaqDevice";
    argString = "(boardNum)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbReleaseDaqDevice(deviceHandle);
    argVals = QString("(%1)")
            .arg(deviceHandle);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;

}
