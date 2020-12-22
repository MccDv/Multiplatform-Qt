#ifndef LIBMISC_H
#define LIBMISC_H

#include <QString>
#include <QMap>
#include <QFile>
#include "libTypes.h"
#include "libutilities.h"
#include "mvErrorMap.h"

class LibMisc
{

public:

    LibMisc();

    int mccIgnoreInstacal(QString &params);
    int mccFlashLed(QString &params, DaqDeviceHandle deviceHandle, int flashCount);
    QString mccGetUlVersion(QString &params);
    QString mccGetUlErrorText(int errValue);
    QString mccGetErrConstText(int errValue);

    int mccGetInfoStr(QString &params, int infoItem, unsigned int index,
                      char *infoValue, unsigned int &maxLen);
    int mccGetConfig(QString &params, int configItem, unsigned int index, long long &infoValue);
    int mccGetCfgStr(QString &params, int configItem, unsigned int index,
                     char *configValue, unsigned int &maxConfigLen);
    int mccSetConfig(QString &params, int configItem, unsigned int index, long long infoValue);
    int mccDevGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                      int infoItem, unsigned int index, long long &infoValue);
    int mccDevGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                     int configItem, unsigned int index, long long &infoValue);
    int mccDevGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                        int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen);
    int mccDevSetConfig(QString &params, DaqDeviceHandle deviceHandle,
                        int configItem, unsigned int index, long long configValue);
    int mccDevSetConfigStr(QString &params, DaqDeviceHandle deviceHandle,
                           int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen);

    int mccAiGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                      int infoItem, unsigned int index, long long &infoValue);
    int mccAiGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                        int infoItem, unsigned int index, double &infoValue);
    int mccAiGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                    int configItem, unsigned int index, long long &configValue);
    int mccAiGetCfgDbl(QString &params, DaqDeviceHandle deviceHandle,
                        int configItem, unsigned int index, double &configValue);
    int mccAiGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                        int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen);
    int mccAiSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                    int configItem, unsigned int index, long long configValue);

    int mccAoGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                      int infoItem, unsigned int index, long long &infoValue);
    int mccAoGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                        int infoItem, unsigned int index, double &infoValue);
    int mccAoGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                    int configItem, unsigned int index, long long &configValue);
    int mccAoSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                    int configItem, unsigned int index, long long configValue);

    int mccDioGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                      int infoItem, unsigned int index, long long &infoValue);
    int mccDioGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                         int infoItem, unsigned int index, double &infoValue);
    int mccDioGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                     int configItem, unsigned int index, long long &configValue);
    int mccDioSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                     int configItem, unsigned int index, long long configValue);

    int mccCtrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                      int infoItem, unsigned int index, long long &infoValue);
    int mccCtrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                         int infoItem, unsigned int index, double &infoValue);
    int mccCtrGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                     int configItem, unsigned int index, long long &configValue);
    int mccCtrSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                     int configItem, unsigned int index, long long configValue);

    int mccTmrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                      int infoItem, unsigned int index, long long &infoValue);
    int mccTmrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                         int infoItem, unsigned int index, double &infoValue);

    int mccDaqInGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                      int infoItem, unsigned int index, long long &infoValue);
    int mccDaqInGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                            int infoItem, unsigned int index, double &infoValue);
    int mccDaqOutGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                      int infoItem, unsigned int index, long long &infoValue);
    int mccDaqOutGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                            int infoItem, unsigned int index, double &infoValue);

    QMap<int, QString> mccGetUlInfoItems();
    QMap<int, QString> mccGetUlCfgItems();
    QMap<int, QString> mccGetDevInfoItems();
    QMap<int, QString> mccGetDevCfgItems();
    QMap<int, QString> mccGetAiInfoItems();
    QMap<int, QString> mccGetAiCfgItems();
    QMap<int, QString> mccGetAoInfoItems();
    QMap<int, QString> mccGetAoCfgItems();
    QMap<int, QString> mccGetDioInfoItems();
    QMap<int, QString> mccGetDioCfgItems();
    QMap<int, QString> mccGetCtrInfoItems();
    QMap<int, QString> mccGetCtrCfgItems();
    QMap<int, QString> mccGetTmrInfoItems();
    QMap<int, QString> mccGetDaqInInfoItems();
    QMap<int, QString> mccGetDaqOutInfoItems();

private:
    LibUtilities *testUtils;

};

#endif // LIBMISC_H
