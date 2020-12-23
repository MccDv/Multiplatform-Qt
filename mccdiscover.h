#ifndef MCCDISCOVER_H
#define MCCDISCOVER_H

#include <QHash>
#include <QString>
#include <QList>
#include "libTypes.h"
#include "mvErrorMap.h"
#include "mvEnums.h"

#include "libdiscover.h"
#include "libmisc.h"

class MccDiscover
{

public:
    MccDiscover();

    int ignoreInstacal(QString &params);
    int updateInventory(QString &params, DaqDeviceInterface hatFilter, UlNumDevs &numFound);
    int connectDevice(QString &params, DaqDeviceHandle devHandle, QString uniqueIDStr);
    DaqDeviceHandle createDevice(QString &params, DaqDeviceHandle &deviceHandle, MccDaqDeviceDescriptor mccDevDescriptor);
    int isDeviceConnected(QString &params, DaqDeviceHandle devHandle, QString uniqueIDStr, int &connected);
    int disconnectDevice(QString &params, DaqDeviceHandle devHandle);
    QString getBoardName(QString uniqueID);
    UlNumDevs getProductID(QString uniqueID);
    DaqDeviceInterface getDevInterface(QString uniqueID);
    QString getDevString(QString uniqueID);
    MccDaqDeviceDescriptor getDescriptor(QString uniqueId);

    QHash<QString, DaqDeviceHandle> getListedDevices();

private:

    LibDiscover *libDiscFunctions;
    LibMisc *libMiscFuntions;

    MccDaqDeviceDescriptor devDescriptors[MAX_DEV_COUNT];

    UlNumDevs mnNumListed;
    QHash<QString, DaqDeviceHandle> devList;

    void callClassConstructors();

};

#endif // MCCDISCOVER_H
