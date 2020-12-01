#ifndef LIBUTILITIES_H
#define LIBUTILITIES_H

#include <QString>
#include <QtMath>
#include "libTypes.h"
#include "mvEnums.h"
#include "daqhats.h"
#include "libenum.h"
//#include "ulenumlinux.h"

class LibUtilities
{
public:
    LibUtilities();

    double getRangeVolts(int rangeVal);
    int getDIChanTypeIndex(int chanType);

    QString getHatTypeName(uint16_t hatType);
    QString getRangeNomo(int rangeVal);
    QString getOptionNames(int curOptions);
    QString getDigOptionNames(int curOptions);
    QString getCtrOptionNames(int curOptions);

    QString getInfoDescription(int infoType, int infoItem, long long infoValue, unsigned int index);
    QString getInfoDblDescription(int infoType, int infoItem, double infoValue, unsigned int index);
    QString getInfoStrDescription(int infoType, int infoItem, unsigned int index);
    QString getConfigDescription(int infoType, int configItem, long long configValue, unsigned int index);
    QString getConfigStrDescription(int infoType, int configItem, unsigned int index);
    QString getConfigDblDescription(int infoType, int configItem, double configValue, unsigned int index);

    QString getFirmwareNames(int fwType);
    QString getRangeName(int rangeVal);
    QString getAiChanTypeName(int chanType);
    QString getAiInputModeName(int inMode);
    QString getAiRejFreqName(int rejType);
    QString getAiCalTableName(int index);
    QString getAiCalTableTypeName(int tableType);
    QString getTcTypeName(int tcType);
    QString getTempUnitName(int tempUnit);
    QString getDaqIChanTypeNames(int typeNum);

    QString getAoSyncModeName(int syncMode);
    QString getDaqOChanTypeNames(int typeNum);

    QString getDigitalDirection(int digDir);
    QString getDioPortTypeName(int typeNum);
    QString getDioPortTypeDesig(int typeNum);
    QString getDPortIoTypeName(int ioType);

    QString getCtrTypeName(int ctrType);
    QString getCtrRegTypeNames(int regType);
    QString getCtrMeasTypeNames(int typeNum);
    QString getCtrMeasModeNames(int modeNum);
    QString getTmrTypeName(int tmrType);

    QString getTrigTypeNames(int trigType);
    QString getQueueTypeNames(int queueTypes);
    QString getQueueLimitNames(int queueLimits);

    QString getEventNames(int eventMask);
    QString getRegionNames(int memRegion);
    QString getEnableDisableName(int value);

private:
    const QChar mPlusMinus = 0x00B1;

};

#endif // LIBUTILITIES_H
