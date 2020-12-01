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
    UlNumDevs numDevs;

    DaqDeviceHandle deviceHandle, newHandle;
    int err;
    QString uidKey, discoverParams;
    QList<DaqDeviceHandle> devHandles;
    QHash<QString, DaqDeviceHandle> newList, icalDevs;

    devHandles.clear();
    /*  If Windows, check Instacal installed devices.
     *  Add to devList if not there already             */

    err = libDiscFunctions->mccGetInstacalDevs(params, icalDevs);
    if (err == MCC_NOERRORS) {
        foreach (QString iD, icalDevs.keys()) {
            devHandles.append(icalDevs.value(iD));
            if (!devList.contains(iD))
                devList.insert(iD, icalDevs.value(iD));
        }
    }

    /*  Disconnect all previously listed devices
     *  (required because of DT implementation)
     *  and preserve their handles in a list      */

    foreach (DaqDeviceHandle exDev, devList.values()) {
        err = libDiscFunctions->mccDisconnectDaqDevice(params, exDev);
        devHandles.append(exDev);
    }

    numDevs = MAX_DEV_COUNT;
    memset(devDescriptors, 0, sizeof(devDescriptors));

    err = libDiscFunctions->mccGetDaqDeviceInventory(params, interfaceType, devDescriptors, numDevs);
    numFound = numDevs;
    discoverParams = params;

    if(err != 0)
        return err;

    /*  Go through discovered devices and, if in old list,
     *  reconnect with existing number and add to new list.
     *  If not, create it with a free handle.
     *  If Linux, connect it also (Windows connects on create)  */

    uidKey = "";
    for (UlNumDevs i = 0; i < numDevs; i++) {
        deviceHandle = -1;
        uidKey = devDescriptors[i].mccUniqueId;
        if (devList.contains(uidKey)) {
            //  previously connected - use old number
            deviceHandle = devList.value(uidKey);
            err = libDiscFunctions->mccConnectDaqDevice(params, deviceHandle, uidKey);
            if (err != MCC_NOERRORS)
                return err;
            newList.insert(uidKey, deviceHandle);
        } else {
            //  find an unused handle (linux doesn't use 0)
            newHandle = 1;
            while (devHandles.contains(newHandle)) {
                newHandle++;
            }
            deviceHandle = libDiscFunctions->mccCreateDaqDevice(params, newHandle, devDescriptors[i]);
            if (deviceHandle != newHandle)
                return MCC_BADBOARD;

            // Linux needs to also connect to the device (Windows doesn't)
            err = libDiscFunctions->mccConnectDaqDevice(params, deviceHandle, uidKey);
            if (err != MCC_NOERRORS)
                return err;

            devHandles.append(deviceHandle);
            newList.insert(uidKey, newHandle);
        }
    }

    /*  Go through the old list and release any
     *  devices not re-discovered. Swap the new
     *  list into the global list.               */

    foreach (QString devID, devList.keys()) {
        if (!newList.contains(devID)) {
            deviceHandle = devList.value(devID);
            err = libDiscFunctions->mccReleaseDaqDevice(params, deviceHandle);
        }
    }

    devList.clear();
    devList = newList;
    newList.clear();

    /*  Add iCal devices to list
    foreach (QString iD, icalDevs.keys())
        devList.insert(iD, icalDevs.value(iD));*/

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

void MccDiscover::callClassConstructors()
{
    libDiscFunctions = new LibDiscover;
    //ulMiscFuntions = new UlMiscLinux;
}
