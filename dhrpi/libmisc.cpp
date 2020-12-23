#include "libmisc.h"
#include "../mvtest.h"

ErrorDialog *miscErrorDialog;

LibMisc::LibMisc()
{
    miscErrorDialog = MvTest::errDialogObj;
}

int LibMisc::mccIgnoreInstacal(QString &params)
{
    (void)params;
    return MCC_NOERRORS;
}

int LibMisc::mccFlashLed(QString &params, DaqDeviceHandle deviceHandle, int flashCount)
{
    int err;
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    uint devType;
    bool ok;

    devType = 0;
    if (params.contains("0x"))
        devType = params.mid(params.indexOf("0x") + 2).toInt(&ok, 16);


    hatName = testUtils->getHatTypeName(devType);
    funcName = hatName.append(": BlinkLED");
    argString = "(address, flashCount)\n";
    switch (devType) {
    case HAT_ID_MCC_118:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc118_blink_led(deviceHandle, flashCount);
        break;
#ifdef HAT_05
    case HAT_ID_MCC_172:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc172_blink_led(deviceHandle, flashCount);
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = mcc128_blink_led(deviceHandle, flashCount);
        break;
#endif
    default:
        argString = "(~)\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        err = RESULT_INVALID_DEVICE;
        argVals = "(~)";
        break;
    }

    if(argVals == "")
        argVals = QString("(%1, %2)")
                .arg(deviceHandle)
                .arg(flashCount);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

QString LibMisc::mccGetUlVersion(QString &params)
{
    QString returnStr, fileContents;
    QProcess *versionExe = new QProcess();
    QFile versionFile("ver.txt");
    QStringList cmdArgs;

    params = "";
    cmdArgs << "--command" << "daqhats_version >> ver.txt";
    returnStr = "unknown";
    versionExe->start("lxterminal", cmdArgs); //
    if (versionFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        fileContents = versionFile.readAll();
        int stVer = fileContents.indexOf("n ") + 2;
        int endVer = fileContents.indexOf(" is") - stVer;
        returnStr = fileContents.mid(stVer, endVer);
    }
    return returnStr;
}

QString LibMisc::mccGetUlErrorText(int errValue)
{
    switch (errValue) {
    case RESULT_SUCCESS:
        return "SUCCESS (No error)";
        break;
    case RESULT_BAD_PARAMETER:
        return "BAD_PARAMETER (Invalid parameter)";
        break;
    case RESULT_BUSY:
        return "BUSY (Device is busy)";
        break;
    case RESULT_TIMEOUT:
        return "TIMEOUT (Resource access timeout)";
        break;
    case RESULT_LOCK_TIMEOUT:
        return "LOCK_TIMEOUT (Resource lock timeout)";
        break;
    case RESULT_INVALID_DEVICE:
        return "INVALID_DEVICE (Wrong device type at address)";
        break;
    case RESULT_RESOURCE_UNAVAIL:
        return "RESOURCE_UNAVAIL (Resource unavailable)";
        break;
    case RESULT_UNDEFINED:
        return "UNDEFINED (Some other error -10)";
        break;
    default:
        return QString("Invalid error code (%1)").arg(errValue);
        break;
    }
}

QString LibMisc::mccGetErrConstText(int errValue)
{
    const char* errText;
    QString returnText;
    QString funcName, params;
    QString argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ErrorMessage";
    argString = "(errorCode)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    errText = hat_error_message(errValue);
    returnText = QString("%1").arg(errText);

    argVals = QString("(%1)").arg(errValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(RESULT_SUCCESS));
    return returnText;
}

int LibMisc::mccGetInfoStr(QString &params, int infoItem, unsigned int index,
                               char *infoValue, unsigned int &maxLen)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)maxLen;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccGetConfig(QString &params, int configItem, unsigned int index, long long &infoValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)infoValue;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccGetCfgStr(QString &params, int configItem, unsigned int index,
                              char *configValue, unsigned int &maxConfigLen)
{
    (void)configItem;
    (void)index;
    configValue[0] = '0';
    maxConfigLen = 0;
    params = "funcName + argString + funcName + argVals""";
    return 0;
}

int LibMisc::mccSetConfig(QString &params, int configItem, unsigned int index, long long infoValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)infoValue;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDevGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)deviceHandle;
    (void)index;
    (void)infoValue;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDevGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long &infoValue)
{
    int err;

    params = "";
    (void)deviceHandle;
    (void)index;
    (void)infoValue;
    (void)configItem;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDevGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                            int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    maxConfigLen = 0;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDevSetConfig(QString &params, DaqDeviceHandle deviceHandle,
                                 int configItem, unsigned int index, long long configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDevSetConfigStr(QString &params, DaqDeviceHandle deviceHandle,
                                    int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen)
{
    (void)deviceHandle;
    (void)configItem;
    (void)index;
    params = "";
    maxConfigLen = 0;
    configValue[0] = '\0';

    return 0;
}

int LibMisc::mccAiGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                              int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccAiGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, double &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccAiGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long &configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccAiGetCfgDbl(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, double &configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccAiGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    maxConfigLen = 0;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccAiSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccAoGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                              int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccAoGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, double &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccAoGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long &configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccAoSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDioGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName;
    QString argString, argVals;
    QTime t;
    QString sStartTime;
    QString hatName;
    uint devType;
    (void)deviceHandle;
    (void)index;
    (void)infoValue;
    int numChans;
    bool ok;

    devType = 0;
    numChans = 0;
    infoValue = 0;
    if (params.contains("0x"))
        devType = params.mid(params.indexOf("0x") + 2).toInt(&ok, 16);

    switch (devType) {
    case HAT_ID_MCC_152:
        hatName = testUtils->getHatTypeName(devType);
        switch (infoItem) {
#ifdef HAT_05
        case MCC_DIG_NUMDEVS:
            funcName = hatName.append(": numDioChans");
            argString = "() = dioChans\n";
            sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
            numChans = mcc152_info()->NUM_DIO_CHANNELS;
            if (numChans > 0)
                infoValue = 1;
            break;
        case MCC_DIG_PORTIOTYPE:
            infoValue = DPIOT_BITIO;
            break;
        case MCC_DIG_NUMBITS:
            funcName = hatName.append(": numDioChans");
            argString = "() = dioChans\n";
            sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
            numChans = mcc152_info()->NUM_DIO_CHANNELS;
            infoValue = numChans;
            break;
#endif  //HAT_05
        default:
            break;
        }
        break;
    default:
        argString = "(~) = dioChans\n";
        sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
        numChans = 0;
        argVals = "(~) = ~0";
        break;
    }

    if(argVals == "")
        argVals = QString(" = %1")
                .arg(numChans);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDioGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, double &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDioGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long &configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDioSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccCtrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccCtrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, double &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccCtrGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long &configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccCtrSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long configValue)
{
    int err;

    params = "";
    (void)configItem;
    (void)index;
    (void)configValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccTmrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccTmrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, double &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDaqInGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDaqInGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                    int infoItem, unsigned int index, double &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDaqOutGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

int LibMisc::mccDaqOutGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                     int infoItem, unsigned int index, double &infoValue)
{
    int err;

    params = "";
    (void)infoItem;
    (void)index;
    (void)infoValue;
    (void)deviceHandle;
    err = RESULT_SUCCESS;
    return err;
}

void LibMisc::setPortDirInfo(int portDirType)
{
    mPortDirType = portDirType;
}

/*  Map parameters start with #:#:. The first number indicates index applies
 *  (0 = no index, 1 = index is used), the second number indicates
 *  which function to call (0 = standard, 1 = string, 2 = double.           */

QMap<int, QString> LibMisc::mccGetUlInfoItems()
{
    QMap<int, QString> ulInfoItems;

    return ulInfoItems;
}

QMap<int, QString> LibMisc::mccGetUlCfgItems()
{
    QMap<int, QString> ulConfigItems;

    return ulConfigItems;
}

QMap<int, QString> LibMisc::mccGetDevInfoItems()
{
    QMap<int, QString> devInfoItems;

    return devInfoItems;
}

QMap<int, QString> LibMisc::mccGetDevCfgItems()
{
    QMap<int, QString> devConfigItems;

    return devConfigItems;
}

QMap<int, QString> LibMisc::mccGetAiInfoItems()
{
    QMap<int, QString> aiInfoItems;

    return aiInfoItems;
}

QMap<int, QString> LibMisc::mccGetAiCfgItems()
{
    QMap<int, QString> aiCfgItems;

    return aiCfgItems;
}

QMap<int, QString> LibMisc::mccGetAoInfoItems()
{
    QMap<int, QString> aoInfoItems;

    return aoInfoItems;
}

QMap<int, QString> LibMisc::mccGetAoCfgItems()
{
    QMap<int, QString> aoConfigItems;

    return aoConfigItems;
}

QMap<int, QString> LibMisc::mccGetDioInfoItems()
{
    QMap<int, QString> dioInfoItems;

    return dioInfoItems;
}

QMap<int, QString> LibMisc::mccGetDioCfgItems()
{
    QMap<int, QString> dioConfigItems;

    return dioConfigItems;
}

QMap<int, QString> LibMisc::mccGetCtrInfoItems()
{
    QMap<int, QString> ctrInfoItems;
    return ctrInfoItems;
}

QMap<int, QString> LibMisc::mccGetCtrCfgItems()
{
    QMap<int, QString> ctrConfigItems;

    return ctrConfigItems;
}

QMap<int, QString> LibMisc::mccGetTmrInfoItems()
{
    QMap<int, QString> tmrInfoItems;

    return tmrInfoItems;
}

QMap<int, QString> LibMisc::mccGetDaqInInfoItems()
{
    QMap<int, QString> daqInInfoItems;

    return daqInInfoItems;
}

QMap<int, QString> LibMisc::mccGetDaqOutInfoItems()
{
    QMap<int, QString> daqOutInfoItems;

    return daqOutInfoItems;
}

