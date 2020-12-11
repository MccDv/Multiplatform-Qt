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
    return err;
}

QString LibMisc::mccGetUlVersion(QString &params)
{
    QString returnStr, fileContents;
    QProcess *versionExe = new QProcess();
    QFile versionFile("ver.txt");
    QStringList cmdArgs;

    params = "";
    cmdArgs << "--command" << "daqhats_version" << ">>" << "ver.txt";
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
    QString errText;

    return errText;
}

QString LibMisc::mccGetErrConstText(int errValue)
{
    return "NO_ERROR";
}

int LibMisc::mccGetInfoStr(QString &params, int infoItem, unsigned int index,
                               char *infoValue, unsigned int &maxLen)
{
    int err;
    return err;
}

int LibMisc::mccGetConfig(QString &params, int configItem, unsigned int index, long long &infoValue)
{
    int err;

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

    return err;
}

int LibMisc::mccDevGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccDevGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccDevGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                            int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen)
{
    int err;

    return err;
}

int LibMisc::mccDevSetConfig(QString &params, DaqDeviceHandle deviceHandle,
                                 int configItem, unsigned int index, long long configValue)
{
    int err;

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

    return err;
}

int LibMisc::mccAiGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, double &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccAiGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long &configValue)
{
    int err;

    return err;
}

int LibMisc::mccAiGetCfgDbl(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, double &configValue)
{
    int err;

    return err;
}

int LibMisc::mccAiGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen)
{
    int err;

    return err;
}

int LibMisc::mccAiSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long configValue)
{
    int err;

    return err;
}

int LibMisc::mccAoGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                              int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccAoGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, double &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccAoGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long &configValue)
{
    int err;

    return err;
}

int LibMisc::mccAoSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long configValue)
{
    int err;

    return err;
}

int LibMisc::mccDioGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccDioGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, double &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccDioGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long &configValue)
{
    int err;

    return err;
}

int LibMisc::mccDioSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long configValue)
{
    int err;

    return err;
}

int LibMisc::mccCtrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccCtrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, double &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccCtrGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long &configValue)
{
    int err;

    return err;
}

int LibMisc::mccCtrSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long configValue)
{
    int err;

    return err;
}

int LibMisc::mccTmrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccTmrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, double &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccDaqInGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccDaqInGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                    int infoItem, unsigned int index, double &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccDaqOutGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, long long &infoValue)
{
    int err;

    return err;
}

int LibMisc::mccDaqOutGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                     int infoItem, unsigned int index, double &infoValue)
{
    int err;

    return err;
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

