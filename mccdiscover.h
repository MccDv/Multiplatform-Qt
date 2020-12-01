#ifndef MCCDISCOVER_H
#define MCCDISCOVER_H

#include <QHash>
#include <QString>
#include <QList>
#include "libTypes.h"
#include "mvErrorMap.h"

#include "libdiscover.h"
#include "libmisc.h"

class MccDiscover
{

public:
    MccDiscover();

    int ignoreInstacal(QString &params);
    int updateInventory(QString &params, DaqDeviceInterface hatFilter, UlNumDevs &numFound);
    QString getBoardName(QString uniqueID);
    UlNumDevs getProductID(QString uniqueID);
    DaqDeviceInterface getDevInterface(QString uniqueID);
    QString getDevString(QString uniqueID);

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
