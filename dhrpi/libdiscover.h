#ifndef LIBDISCOVER_H
#define LIBDISCOVER_H

#include "daqhats/daqhats.h"
#include "../errordialog.h"
#include "daqhatutils.h"

//#include "daqhattest.h"
#include "libutilities.h"

class LibDiscover
{
public:
    LibDiscover();
    int mccIgnoreInstacal(QString &params);
    int mccGetInstacalDevs(QString &params, QHash<QString, DaqDeviceHandle> &iCalDevs);
    int mccGetDaqDeviceInventory(QString &params, DaqDeviceInterface interfaceTypes,
                                 MccDaqDeviceDescriptor mccDescriptors[], UlNumDevs &numDescriptors);
    int mccDisconnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle);
    int mccReleaseDaqDevice(QString &params, DaqDeviceHandle deviceHandle);
    int mccConnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle, QString devUID);
    int mccIsDaqDeviceConnected(QString &params, DaqDeviceHandle deviceHandle, QString devUID, int &connected);
    DaqDeviceHandle mccCreateDaqDevice(QString &params, DaqDeviceHandle &deviceHandle, MccDaqDeviceDescriptor mccDevDescriptor);


    int detectHats(QString &params, uint16_t hatFilter);
    int openDevice(QString &params, uint16_t devType, uint8_t address);
    int closeDevice(QString &params, uint16_t devType, uint8_t address);
    bool deviceIsOpen(QString &params, uint16_t devType, uint8_t address);
    int getFirmwareVersion(QString &params, uint16_t devType, uint8_t address, uint16_t &fwMain, uint16_t &fwBoot);
    int getSerialNumber(QString &params, uint16_t devType, uint8_t address, QString &serialNum);
    int blinkLED(QString &params, uint16_t devType, uint8_t address, uint8_t count);
    int readCalDate(QString &params, uint16_t devType, uint8_t address, QString &calDate);

    QString getBoardName(uint16_t devType);
    uint8_t getProductID(uint16_t devType);
    //DaqDeviceInterface getDevInterface(QString uniqueID);
    //QString getDevString(QString uniqueID);

    QHash<uint8_t, uint16_t> getListedDevices();

private:
    LibUtilities *testUtils;

    struct HatInfo hatInfoList[MAX_NUMBER_HATS];

    int mNumHats;
    QHash<uint8_t, uint16_t> mHatList;   //address, type

};

#endif // LIBDISCOVER_H
