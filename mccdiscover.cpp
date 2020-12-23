#include "mccdiscover.h"

MccDiscover::MccDiscover()
{
    callClassConstructors();
}

int MccDiscover::ignoreInstacal(QString &params)
{
    int err;

    err = libDiscFunctions->mccIgnoreInstacal(params);
    return err;
}

int MccDiscover::updateInventory(QString &params, DaqDeviceInterface interfaceType, UlNumDevs &numFound)
{
    int exDev, connected, err, tempHandle;
    bool uniqueHandle;
    QString uidKey, discoverParams;
    QList<DaqDeviceHandle> devHandles;
    QHash<QString, DaqDeviceHandle> newList, icalDevs;

    devHandles.clear();
    /*  If Windows, check Instacal installed devices.
     *  Add to devList if not there already             */

    devList.clear();
    newList.clear();
    err = libDiscFunctions->mccGetInstacalDevs(params, icalDevs);
    if (err == MCC_NOERRORS) {
        foreach (QString iD, icalDevs.keys()) {
            if (!devList.contains(iD))
                devList.insert(iD, icalDevs.value(iD));
        }
    }

    /*  Disconnect all previously listed devices
     *  (required because of DT implementation)
     *  and preserve their handles in newList      */

    foreach (QString exDevId, devList.keys()) {
        exDev = devList.value(exDevId);
        err = libDiscFunctions->mccIsDaqDeviceConnected(params, exDev, exDevId, connected);
        if (connected) {
            err = libDiscFunctions->mccDisconnectDaqDevice(params, exDev);
            newList.insert(exDevId, exDev);
            devHandles.append(exDev);
        } else {
            // in Instacal, but not attached
            devList.remove(exDevId);
            err = libDiscFunctions->mccReleaseDaqDevice(params, exDev);
        }
    }

    numFound = MAX_DEV_COUNT;
    memset(devDescriptors, 0, sizeof(devDescriptors));

    err = libDiscFunctions->mccGetDaqDeviceInventory(params, interfaceType, devDescriptors, numFound);
    discoverParams = params;
    if (err != MCC_NOERRORS)
        return err;

    /*  Go through discovered devices and, if in Instacal list, reconnect
     *  with existing number. If not, create it with a free handle.
     *  If Linux, connect it also (Windows connects on create)
     *
     *  First, find number of unique devices between Instacal and discovery   */

    for (uint discDev = 0; discDev < (uint)numFound; discDev++) {
        uidKey = devDescriptors[discDev].mccUniqueId;
        if (!devList.contains(uidKey)) {
            /*  Not an Instacal device - try to create and connect it
             *  Find an unused handle (linux doesn't use 0) */
            tempHandle = 0;
            if (LIB_PLATFORM == MV_LINUX)
                tempHandle = 1;
            uniqueHandle = false;
            while (!uniqueHandle) {
                uniqueHandle = true;
                foreach (int curHandle, devHandles) {
                    if (curHandle == tempHandle) {
                        uniqueHandle = false;
                        tempHandle++;
                    }
                }
            }
            if (LIB_PLATFORM == MV_LINUX) {
                int requestedHandle = tempHandle;
                tempHandle = libDiscFunctions->mccCreateDaqDevice(params, requestedHandle, devDescriptors[discDev]);
                if (tempHandle != requestedHandle)
                    continue;
                devHandles.append(tempHandle);
            } else {
                devHandles.append(tempHandle);
            }
            err = libDiscFunctions->mccConnectDaqDevice(params, tempHandle, uidKey);
            if (err == MCC_NOERRORS) {
                // add if connect success
                devList.insert(uidKey, tempHandle);
            }
        } else {
            err = libDiscFunctions->mccIsDaqDeviceConnected(params, tempHandle, uidKey, connected);
            if (!connected) {
                tempHandle = newList.value(uidKey);
                err = libDiscFunctions->mccConnectDaqDevice(params, tempHandle, uidKey);
            }
        }
    }

    mnNumListed = devList.count();
    params = discoverParams;
    return mnNumListed;
}

QString MccDiscover::getBoardName(QString uniqueID)
{
    UlNumDevs i;
    QString uidKey, bdName;

    if (devList.contains(uniqueID)) {
        for (i = 0; i < mnNumListed; i++) {
            uidKey = devDescriptors[i].mccUniqueId;
            if (uidKey == uniqueID) {
                bdName = devDescriptors[i].mccProductName;
                return bdName;
            }
        }
    }
    return "";
}

QString MccDiscover::getDevString(QString uniqueID)
{
    UlNumDevs i;
    QString uidKey, bdName;

    if (devList.contains(uniqueID)) {
        for (i = 0; i < mnNumListed; i++) {
            uidKey = devDescriptors[i].mccUniqueId;
            if (uidKey == uniqueID) {
                return bdName = devDescriptors[i].mccDevString;
            }
        }
    }
    return "";
}

UlNumDevs MccDiscover::getProductID(QString uniqueID)
{
    UlNumDevs i, pID;
    QString uidKey;

    if (devList.contains(uniqueID)) {
        for (i = 0; i < mnNumListed; i++) {
            uidKey = devDescriptors[i].mccUniqueId;
            if (uidKey == uniqueID) {
                pID = devDescriptors[i].mccProductId;
                return pID;
            }
        }
    }
    return 0;
}

DaqDeviceInterface MccDiscover::getDevInterface(QString uniqueID)
{
    UlNumDevs i;
    QString uidKey;

    if (devList.contains(uniqueID)) {
        for (i = 0; i < mnNumListed; i++) {
            uidKey = devDescriptors[i].mccUniqueId;
            if (uidKey == uniqueID) {
                return devDescriptors[i].devInterface;
            }
        }
    }
    return (DaqDeviceInterface)0;
}

QHash<QString, DaqDeviceHandle> MccDiscover::getListedDevices()
{
    return devList;
}

MccDaqDeviceDescriptor MccDiscover::getDescriptor(QString uniqueId)
{
    QString testId;
    MccDaqDeviceDescriptor descriptor;

    descriptor = devDescriptors[0];
    for (uint i = 0; i < (uint)mnNumListed; i++) {
        testId = QString("%1").arg(devDescriptors[i].mccUniqueId);
        if (testId == uniqueId) {
            descriptor = devDescriptors[i];
        }
    }
    return descriptor;
}

DaqDeviceHandle MccDiscover::createDevice(QString &params, DaqDeviceHandle &deviceHandle, MccDaqDeviceDescriptor mccDevDescriptor)
{
    DaqDeviceHandle devHandle;

    devHandle = libDiscFunctions->mccCreateDaqDevice(params, deviceHandle, mccDevDescriptor);
    return devHandle;
}

int MccDiscover::connectDevice(QString &params, DaqDeviceHandle devHandle, QString uniqueIDStr)
{
    int err;

    err = libDiscFunctions->mccConnectDaqDevice(params, devHandle, uniqueIDStr);
    return err;
}

int MccDiscover::isDeviceConnected(QString &params, DaqDeviceHandle devHandle, QString uniqueIDStr, int &connected)
{
    int err;

    err = libDiscFunctions->mccIsDaqDeviceConnected(params, devHandle, uniqueIDStr, connected);
    return err;
}

int MccDiscover::disconnectDevice(QString &params, DaqDeviceHandle devHandle)
{
    int err;

    err = libDiscFunctions->mccDisconnectDaqDevice(params, devHandle);
    return err;
}

void MccDiscover::callClassConstructors()
{
    libDiscFunctions = new LibDiscover;
}
