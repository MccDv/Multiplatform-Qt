#include "libdiscover.h"
#include "mvtest.h"

ErrorDialog *discoverErrorDialog;

LibDiscover::LibDiscover()
{
    discoverErrorDialog = MvTest::errDialogObj;
}

int LibDiscover::mccIgnoreInstacal(QString &params)
{
    params = "";
    return MCC_NOERRORS;
}

int LibDiscover::mccGetInstacalDevs(QString &params, QHash<QString, DaqDeviceHandle> &iCalDevs)
{
    params = "";
    iCalDevs.clear();
    return 0;
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
    err = ulGetDaqDeviceInventory(interfaceTypes, daqDevDescriptors, &numDescriptors);
    argVals = QStringLiteral("(%1, %2, %3)")
            .arg(interfaceTypes)
            .arg("devDescriptors")
            .arg(numDescriptors);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    for (UlNumDevs devIndex = 0; devIndex < numDescriptors; devIndex++) {
        strcpy(mccDescriptors[devIndex].mccUniqueId, daqDevDescriptors[devIndex].uniqueId);
        mccDescriptors[devIndex].devInterface = daqDevDescriptors[devIndex].devInterface;
        strcpy(mccDescriptors[devIndex].mccDevString, daqDevDescriptors[devIndex].devString);
        mccDescriptors[devIndex].mccProductId = daqDevDescriptors[devIndex].productId;
        strcpy(mccDescriptors[devIndex].mccProductName, daqDevDescriptors[devIndex].productName);
    }
    return err;
}

DaqDeviceHandle LibDiscover::mccCreateDaqDevice(QString &params,
                    DaqDeviceHandle deviceHandle, MccDaqDeviceDescriptor mccDevDescriptor)
{
    QString funcName, argString, argVals;
    DaqDeviceDescriptor devDescriptor;
    QTime t;
    QString sStartTime;

    strcpy(devDescriptor.uniqueId, mccDevDescriptor.mccUniqueId);
    devDescriptor.devInterface = mccDevDescriptor.devInterface;
    strcpy(devDescriptor.devString, mccDevDescriptor.mccDevString);
    devDescriptor.productId = mccDevDescriptor.mccProductId;
    strcpy(devDescriptor.productName, mccDevDescriptor.mccProductName);
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    deviceHandle = ulCreateDaqDevice(devDescriptor);
    funcName = "ulCreateDaqDevice";
    argString = "({devInterface, devString, productId, uniqueId})\n";

    argVals = QStringLiteral("({%1, %2, %3, %4})")
            .arg(devDescriptor.devInterface)
            .arg(devDescriptor.devString)
            .arg(devDescriptor.productId)
            .arg(devDescriptor.uniqueId);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(0));
    return deviceHandle;
}

int LibDiscover::mccIsDaqDeviceConnected(QString &params,
                    DaqDeviceHandle deviceHandle, QString devUID, int &connected)
{
    (void)deviceHandle;
    (void)devUID;
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ulIsDaqDeviceConnected";
    argString = "(mDaqDeviceHandle, connected)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulIsDaqDeviceConnected(deviceHandle, &connected);
    argVals = QString("(%1, %2)")
            .arg(deviceHandle)
            .arg(connected);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDiscover::mccConnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle, QString devUID)
{
    (void)devUID;
    UlError err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ulConnectDaqDevice";
    argString = "(deviceHandle)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulConnectDaqDevice(deviceHandle);
    argVals = QStringLiteral("(%1)")
            .arg(deviceHandle);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDiscover::mccDisconnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle)
{
    UlError err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ulDisconnectDaqDevice";
    argString = "(mDaqDeviceHandle)\n";
    argVals = QString("(%1)").arg(deviceHandle);
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDisconnectDaqDevice(deviceHandle);

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
    err = ulReleaseDaqDevice(deviceHandle);
    argVals = QString("(%1)")
            .arg(deviceHandle);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}
