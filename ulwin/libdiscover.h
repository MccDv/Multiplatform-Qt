#ifndef ULDISCOVERWINDOWS_H
#define ULDISCOVERWINDOWS_H

#include "..\..\DAQ\C\cbw.h"
#include "ulmiscwindows.h"
#include "ulTypes.h"
#include "MvErrorMap.h"
#include "../errordialog.h"

class UlDiscoverWindows
{

public:
    UlDiscoverWindows();

    int mccIgnoreInstacal(QString &params);
    int mccGetInstacalDevs(QString &params, QHash<QString, DaqDeviceHandle> &iCalDevs);
    int mccGetDaqDeviceInventory(QString &params, DaqDeviceInterface interfaceTypes,
                                 MccDaqDeviceDescriptor mccDescriptors[], UlNumDevs &numDescriptors);
    int mccDisconnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle);
    int mccReleaseDaqDevice(QString &params, DaqDeviceHandle deviceHandle);
    int mccConnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle, QString devUID);
    int mccIsDaqDeviceConnected(QString &params, DaqDeviceHandle deviceHandle, QString devUID, int &connected);
    DaqDeviceHandle mccCreateDaqDevice(QString &params, DaqDeviceHandle deviceHandle, MccDaqDeviceDescriptor mccDevDescriptor);

};

#endif // ULDISCOVERWINDOWS_H
