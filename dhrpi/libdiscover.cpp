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
    return MCC_NOERRORS;
}

int LibDiscover::mccGetDaqDeviceInventory(QString &params, DaqDeviceInterface
                    interfaceTypes, MccDaqDeviceDescriptor *mccDescriptors, UlNumDevs &numDescriptors)
{
    (void)interfaceTypes;

    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    char* chrAddress;
    QString sAddress;

    uint16_t hatFilter = HAT_ID_ANY;
    funcName = "hat_list";
    argString = "(hatFilter, hatInfoList) = numHats\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    mHatList.clear();
    mNumHats = hat_list(hatFilter, hatInfoList);
    argVals = QString("(%1, [%2]) = %3")
            .arg(hatFilter)
            .arg(mNumHats)
            .arg(mNumHats);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    for (int hatDev = 0; hatDev < mNumHats; hatDev++) {
        mHatList.insert(hatInfoList[hatDev].address, hatInfoList[hatDev].id);
        sAddress = QString("%1").arg(hatInfoList[hatDev].address);
        std::string stAddr = sAddress.toStdString();
        chrAddress = new char[stAddr.size() + 1];
        strcpy(chrAddress, stAddr.c_str());
        mccDescriptors->mccProductId = hatInfoList[hatDev].id;
        strcpy(mccDescriptors->mccProductName, hatInfoList[hatDev].product_name);
        strcpy(mccDescriptors->mccUniqueId, chrAddress);
    }
    numDescriptors = mNumHats;
    return MCC_NOERRORS;
}

DaqDeviceHandle LibDiscover::mccCreateDaqDevice(QString &params,
                    DaqDeviceHandle &deviceHandle, MccDaqDeviceDescriptor mccDevDescriptor)
{
    params = "";
    deviceHandle = QString("%1").arg(mccDevDescriptor.mccUniqueId).toInt();
    return deviceHandle;
}

int LibDiscover::mccIsDaqDeviceConnected(QString &params,
                    DaqDeviceHandle deviceHandle, QString devUID, int &connected)
{
    (void)devUID;
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    bool isOpen;
    uint devType;
    uint8_t address;

    devType = 0;
    address = deviceHandle;
    if (mHatList.contains(address))
        devType = mHatList.value(address);

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": IsOpen");
    argString = "(address) = result\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc118_is_open(address);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc134_is_open(address);
        break;
#endif
#ifdef HAT_04
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc152_is_open(address);
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc172_is_open(address);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc128_is_open(address);
        break;
#endif
    default:
        argString = "(~) = result\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = 0;
        argVals = "(~)";
        break;
    }

    argVals = QString("(%1) = %2").arg(address).arg(isOpen);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    connected = isOpen;
    return MCC_NOERRORS;
}

int LibDiscover::mccConnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle, QString devUID)
{
    (void)devUID;
    int err;
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    uint devType;
    uint8_t address;

    devType = 0;
    address = deviceHandle;
    if (mHatList.contains(address))
        devType = mHatList.value(address);

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": Open");
    argString = "(mAddress)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc118_open(address);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc134_open(address);
        break;
#endif
#ifdef HAT_04
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc152_open(address);
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc172_open(address);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_open(address);
        break;
#endif
    default:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        break;
    }
    argVals = QString("(%1)").arg(address);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDiscover::mccDisconnectDaqDevice(QString &params, DaqDeviceHandle deviceHandle)
{
    int err;
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    uint devType;
    uint8_t address;

    devType = 0;
    address = deviceHandle;
    if (mHatList.contains(address))
        devType = mHatList.value(address);

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": Close");
    argString = "(mAddress)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc118_close(address);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc134_close(address);
        break;
#endif
#ifdef HAT_04
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc152_close(address);
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc172_close(address);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc128_close(address);
        break;
#endif
    default:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = RESULT_INVALID_DEVICE;
        break;
    }
    argVals = QString("(%1)").arg(address);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDiscover::mccReleaseDaqDevice(QString &params, DaqDeviceHandle deviceHandle)
{
    params = "";
    (void)deviceHandle;
    return MCC_NOERRORS;
}

int LibDiscover::detectHats(QString &params, uint16_t hatFilter)
{
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "hat_list";
    argString = "(hatFilter, hatInfoList) = numHats\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    mHatList.clear();
    mNumHats = hat_list(hatFilter, hatInfoList);
    argVals = QString("(%1, [%2]) = %3")
            .arg(hatFilter)
            .arg(mNumHats)
            .arg(mNumHats);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    for (int hatDev = 0; hatDev < mNumHats; hatDev++) {
        mHatList.insert(hatInfoList[hatDev].address, hatInfoList[hatDev].id);
    }
    return mNumHats;
}

QHash<uint8_t, uint16_t> LibDiscover::getListedDevices()
{
    return mHatList;
}

int LibDiscover::openDevice(QString &params, uint16_t devType, uint8_t address)
{
    int err;
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": Open");
    argString = "(mAddress)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc118_open(address);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc134_open(address);
        break;
#endif
#ifdef HAT_04
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc152_open(address);
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc172_open(address);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_open(address);
        break;
#endif
    default:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        break;
    }
    argVals = QString("(%1)").arg(address);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

bool LibDiscover::deviceIsOpen(QString &params, uint16_t devType, uint8_t address)
{
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    bool isOpen;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": IsOpen");
    argString = "(address) = result\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc118_is_open(address);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc134_is_open(address);
        break;
#endif
#ifdef HAT_04
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc152_is_open(address);
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc172_is_open(address);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = mcc128_is_open(address);
        break;
#endif
    default:
        argString = "(~) = result\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        isOpen = 0;
        argVals = "(~)";
        break;
    }

    argVals = QString("(%1) = %2").arg(address).arg(isOpen);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return isOpen;
}

int LibDiscover::closeDevice(QString &params, uint16_t devType, uint8_t address)
{
    int err;
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": Close");
    argString = "(mAddress)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc118_close(address);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc134_close(address);
        break;
#endif
#ifdef HAT_04
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc152_close(address);
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc172_close(address);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc128_close(address);
        break;
#endif
    default:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = RESULT_INVALID_DEVICE;
        break;
    }
    argVals = QString("(%1)").arg(address);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDiscover::blinkLED(QString &params, uint16_t devType, uint8_t address, uint8_t count)
{
    int err;
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": BlinkLED");
    argString = "(address, flashCount)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc118_blink_led(address, count);
        break;
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc172_blink_led(address, count);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc128_blink_led(address, count);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    if(argVals == "")
        argVals = QString("(%1, %2)")
                .arg(address)
                .arg(count);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibDiscover::getSerialNumber(QString &params, uint16_t devType, uint8_t address, QString &serialNum)
{
    int err;
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    char serNum[10];

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": serialNum");
    serialNum = "";
    argString = "(mAddress, serNum)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc118_serial(address, serNum);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc134_serial(address, serNum);
        break;
#endif
#ifdef HAT_04
    case HAT_ID_MCC_152:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc152_serial(address, serNum);
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc172_serial(address, serNum);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc128_serial(address, serNum);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    if(argVals == "")
        argVals = QString("(%1, %2)")
                .arg(address)
                .arg(serNum);

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err == RESULT_SUCCESS) {
        serialNum = QString("%1").arg(serNum);
    }
    return err;
}

int LibDiscover::getFirmwareVersion(QString &params, uint16_t devType, uint8_t address, uint16_t &fwMain, uint16_t &fwBoot)
{
    int err;
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    uint16_t version, boot;

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": firmwareVersion");
    argString = "(address, &version, &boot)\n";
    version = 0;
    boot = 0;
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc118_firmware_version(address, &version, &boot);
        break;
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc172_firmware_version(address, &version);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc128_firmware_version(address, &version);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    if(argVals == "")
        argVals = QString("(%1, %2.%3, %4.%5)")
                .arg(address)
                .arg(version >> 8, 1, 16)
                .arg((uint8_t)version, 2, 16, QChar('0'))
                .arg(boot >> 8, 1, 16)
                .arg((uint8_t)boot, 2, 16, QChar('0'));

    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err == RESULT_SUCCESS) {
        fwMain = version;
        fwBoot = boot;
    }
    return err;
}

int LibDiscover::readCalDate(QString &params, uint16_t devType, uint8_t address, QString &calDate)
{
    int err;
    QString funcName, hatName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    char dateReturned[12];

    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": CalDate");
    calDate = "";
    argString = "(address, calDate)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc118_calibration_date(address, dateReturned);
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc134_calibration_date(address, dateReturned);
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc172_calibration_date(address, dateReturned);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = mcc128_calibration_date(address, dateReturned);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "~";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    if(argVals == "")
        argVals = QString("(%1, %2)")
                .arg(address)
                .arg(dateReturned);
    params = funcName + argString + funcName + argVals;
    discoverErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if (err == RESULT_SUCCESS) {
        calDate = QString("%1").arg(dateReturned);
    }
    return err;
}
