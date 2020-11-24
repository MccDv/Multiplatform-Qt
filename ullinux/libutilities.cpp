#include "libutilities.h"

LibUtilities::LibUtilities()
{

}

double LibUtilities::getRangeVolts(int rangeVal)
{
    switch (rangeVal) {
    case BIP60VOLTS:
        return 120;
    case BIP30VOLTS:
        return 60;
    case BIP15VOLTS:
        return 30;
    case BIP20VOLTS:
        return 40;
    case BIP10VOLTS:
        return 20;
    case BIP5VOLTS:
        return 10;
    case BIP4VOLTS:
        return 8;
    case BIP3VOLTS:
        return 6;
    case BIP2PT5VOLTS:
        return 5;
    case BIP2VOLTS:
        return 4;
    case BIP1PT25VOLTS:
        return 2.5;
    case BIP1VOLTS:
        return 2;
    case BIPPT625VOLTS:
        return 1.25;
    case BIPPT5VOLTS:
        return 1;
    case BIPPT312VOLTS:
        return 0.624;
    case BIPPT25VOLTS:
        return 0.5;
    case BIPPT125VOLTS:
        return 0.25;
    case BIPPT2VOLTS:
        return 0.4;
    case BIPPT156VOLTS:
        return 0.312;
    case BIPPT1VOLTS:
        return 0.2;
    case BIPPT078VOLTS:
        return 0.156;
    case BIPPT05VOLTS:
        return 0.1;
    case BIPPT01VOLTS:
        return 0.02;
    case BIPPT005VOLTS:
        return 0.01;
    case UNI60VOLTS:
        return 60;
    case UNI30VOLTS:
        return 30;
    case UNI15VOLTS:
        return 15;
    case UNI20VOLTS:
        return 20;
    case UNI10VOLTS:
        return 10;
    case UNI5VOLTS:
        return 5;
    case MA0TO20:
        return 0.02;
    default:
        return 0;
    }
}

QString LibUtilities::getRangeNomo(int rangeVal)
{
    double curRangeVolts;

    switch (rangeVal) {
    case BIP60VOLTS:
        curRangeVolts = 60;
        break;
    case BIP30VOLTS:
        curRangeVolts = 30;
        break;
    case BIP15VOLTS:
        curRangeVolts = 15;
        break;
    case BIP20VOLTS:
        curRangeVolts = 20;
        break;
    case BIP10VOLTS:
        curRangeVolts = 10;
        break;
    case BIP5VOLTS:
        curRangeVolts = 5;
        break;
    case BIP4VOLTS:
        curRangeVolts = 4;
        break;
    case BIP3VOLTS:
        curRangeVolts = 3;
        break;
    case BIP2PT5VOLTS:
        curRangeVolts = 2.5;
        break;
    case BIP2VOLTS:
        curRangeVolts = 2;
        break;
    case BIP1PT25VOLTS:
        curRangeVolts = 1.25;
        break;
    case BIP1VOLTS:
        curRangeVolts = 1;
        break;
    case BIPPT625VOLTS:
        curRangeVolts = 0.625;
        break;
    case BIPPT5VOLTS:
        curRangeVolts = 0.5;
        break;
    case BIPPT312VOLTS:
        curRangeVolts = 0.312;
        break;
    case BIPPT25VOLTS:
        curRangeVolts = 0.25;
        break;
    case BIPPT125VOLTS:
        curRangeVolts = 0.125;
        break;
    case BIPPT2VOLTS:
        curRangeVolts = 0.2;
        break;
    case BIPPT156VOLTS:
        curRangeVolts = 0.156;
        break;
    case BIPPT1VOLTS:
        curRangeVolts = 0.1;
        break;
    case BIPPT078VOLTS:
        curRangeVolts = 0.078;
        break;
    case BIPPT05VOLTS:
        curRangeVolts = 0.05;
        break;
    case BIPPT01VOLTS:
        curRangeVolts = 0.01;
        break;
    case BIPPT005VOLTS:
        curRangeVolts = 0.005;
        break;
    case UNI60VOLTS:
        curRangeVolts = 60;
        break;
    case UNI30VOLTS:
        curRangeVolts = 30;
        break;
    case UNI15VOLTS:
        curRangeVolts = 15;
        break;
    case UNI20VOLTS:
        curRangeVolts = 20;
        break;
    case UNI10VOLTS:
        curRangeVolts = 10;
        break;
    case UNI5VOLTS:
        curRangeVolts = 5;
        break;
    case MA0TO20:
        curRangeVolts = 0.02;
        break;
    default:
        curRangeVolts = 0;
        break;
    }
    const QChar plusMinus = 0x00B1;
    if (rangeVal < 100)
        return QString("%1%2V").arg(plusMinus).arg(curRangeVolts);
    else
        return QString("%1V").arg(curRangeVolts);
}

int LibUtilities::getDIChanTypeIndex(int chanType)
{
    switch (chanType) {
    case DAQI_ANALOG_DIFF:
        return 1;
    case DAQI_ANALOG_SE:
        return 2;
    case DAQI_DIGITAL:
        return 3;
    case DAQI_CTR16:
        return 4;
    case DAQI_CTR32:
        return 5;
    case DAQI_CTR48:
        return 6;
    case DAQI_DAC:
        return 7;
    default:
        return 0;
    }
}

QString LibUtilities::getOptionNames(int curOptions)
{
    QString optString;

    if (curOptions == 0)
        optString = "Default";
    else {
        if (curOptions & SO_SINGLEIO)
            optString = "SingleIO, ";
        if (curOptions & SO_BLOCKIO)
            optString += "BlockIO, ";
        if (curOptions & SO_BURSTIO)
            optString += "BurstIO, ";
        if (curOptions & SO_CONTINUOUS)
            optString += "Continuous, ";
        if (curOptions & SO_EXTCLOCK)
            optString += "ExtClock, ";
        if (curOptions & SO_EXTTRIGGER)
            optString += "ExtTrigger, ";
        if (curOptions & SO_RETRIGGER)
            optString += "ReTrigger, ";
        if (curOptions & SO_BURSTMODE)
            optString += "BurstMode, ";
        if (curOptions & SO_PACEROUT)
            optString += "PacerOut, ";
        if (curOptions & SO_EXTTIMEBASE)
            optString += "ExtTimebase, ";
        if (curOptions & SO_TIMEBASEOUT)
            optString += "TimebaseOut, ";
        optString = optString.left(optString.length() - 2);
    }
    return optString;
}

QString LibUtilities::getDigOptionNames(int curOptions)
{
    (void)curOptions;
    return "";
}

QString LibUtilities::getCtrOptionNames(int curOptions)
{
    (void)curOptions;
    return "";
}

QString LibUtilities::getInfoDescription(int infoType, int infoItem,
                                             long long infoValue, unsigned int index)
{
    /*  Returns the string represented by infoValue or
     *  returns infoValue as a string. Optionally, if
     *  index is represented by a string, prepends that
     *  string followed by "|" for parsing in the calling
     *  function. If infoValue is not an int, it's ignored.      */

    QString indexName;

    indexName = "";
    switch (infoType) {
    case GRP_DEVICE:
        if (infoItem == DEV_INFO_DAQ_EVENT_TYPES)
            return getEventNames(infoValue);
        if (infoItem == DEV_INFO_MEM_REGIONS)
            return getRegionNames((MemRegion)infoValue);
        return QString("%1").arg(infoValue);
    case GRP_AIN:
        if (infoItem == AI_INFO_NUM_CHANS_BY_MODE) {
            indexName = getAiInputModeName(index);
            return QString("%1|%2").arg(indexName).arg(infoValue);
        }
        if (infoItem == AI_INFO_NUM_CHANS_BY_TYPE) {
            indexName = getAiChanTypeName(index);
            return QString("%1|%2").arg(indexName).arg(infoValue);
        }
        if (infoItem == AI_INFO_SCAN_OPTIONS)
            return getOptionNames((ScanOption)infoValue);
        if ((infoItem == AI_INFO_DIFF_RANGE) | (infoItem == AI_INFO_SE_RANGE))
            return getRangeName((Range)infoValue);
        if (infoItem == AI_INFO_TRIG_TYPES)
            return getTrigTypeNames((TriggerType)infoValue);
        if (infoItem == AI_INFO_QUEUE_TYPES)
            return getQueueTypeNames((AiQueueType)infoValue);
        if (infoItem == AI_INFO_QUEUE_LIMITS)
            return getQueueLimitNames((AiChanQueueLimitation)infoValue);
        if (infoItem == AI_INFO_MAX_QUEUE_LENGTH_BY_MODE) {
            indexName = getAiInputModeName(index);
            return QString("%1|%2").arg(indexName).arg(infoValue);
        }
        return QString("%1").arg(infoValue);
    case GRP_AOUT:
        if (infoItem == AO_INFO_SCAN_OPTIONS)
            return getOptionNames((ScanOption)infoValue);
        if (infoItem == AO_INFO_RANGE)
            return getRangeName((Range)infoValue);
        if (infoItem == AO_INFO_TRIG_TYPES)
            return getTrigTypeNames((TriggerType)infoValue);
        return QString("%1").arg(infoValue);
    case GRP_DIO:
        if (infoItem == DIO_INFO_PORT_TYPE)
            return getDioPortTypeName((DigitalPortType)infoValue);
        if (infoItem == DIO_INFO_PORT_IO_TYPE)
            return getDPortIoTypeName((DigitalPortIoType)infoValue);
        if (infoItem == DIO_INFO_TRIG_TYPES)
            return getTrigTypeNames((TriggerType)infoValue);
        if (infoItem == DIO_INFO_SCAN_OPTIONS)
            return getOptionNames((ScanOption)infoValue);
        return QString("%1").arg(infoValue);
    case GRP_CTR:
        if (infoItem == CTR_INFO_REGISTER_TYPES)
            return getCtrRegTypeNames(infoValue);
        if (infoItem == CTR_INFO_MEASUREMENT_MODES) {
            indexName = getCtrMeasTypeNames(index);
            QString modeName = getCtrMeasModeNames(infoValue);
            return QString("%1|%2").arg(indexName).arg(modeName);
        }
        if (infoItem == CTR_INFO_MEASUREMENT_TYPES)
            return getCtrMeasTypeNames(infoValue);
        if (infoItem == CTR_INFO_SCAN_OPTIONS)
            return getOptionNames(infoValue);
        if (infoItem == CTR_INFO_TRIG_TYPES)
            return getTrigTypeNames(infoValue);
        return QString("%1").arg(infoValue);
    case GRP_TMR:
        if (infoItem == TMR_INFO_TYPE)
            return getTmrTypeName(infoValue);
        return QString("%1").arg(infoValue);
    case GRP_DAQIN:
        if (infoItem == DAQI_INFO_CHAN_TYPES)
            return getDaqIChanTypeNames(infoValue);
        if (infoItem == DAQI_INFO_TRIG_TYPES)
            return getTrigTypeNames((TriggerType)infoValue);
        if (infoItem == DAQI_INFO_SCAN_OPTIONS)
            return getOptionNames((ScanOption)infoValue);
        return QString("%1").arg(infoValue);
    case GRP_DAQOUT:
        if (infoItem == DAQO_INFO_CHAN_TYPES)
            return getDaqOChanTypeNames(infoValue);
        if (infoItem == DAQO_INFO_TRIG_TYPES)
            return getTrigTypeNames((TriggerType)infoValue);
        if (infoItem == DAQO_INFO_SCAN_OPTIONS)
            return getOptionNames((ScanOption)infoValue);
        return QString("%1").arg(infoValue);
    case GRP_MEMORY:
        return getRegionNames(infoValue);
    default:
        return QString("%1").arg(infoValue);
    }
}

QString LibUtilities::getInfoDblDescription(int infoType, int infoItem,
                                                double infoValue, unsigned int index)
{
    /*  Returns the string represented by infoValue or
     *  returns infoValue as a string. Optionally, if
     *  index is represented by a string, prepends that
     *  string followed by "|" for parsing in the calling
     *  function.       */

    QString indexName;

    (void)infoItem;
    (void)index;
    indexName = "";
    switch (infoType) {
    case GRP_DEVICE:
        return QString("%1").arg(infoValue);
    case GRP_AIN:
        return QString("%1").arg(infoValue);
    case GRP_AOUT:
        return QString("%1").arg(infoValue);
    case GRP_DIO:
        return QString("%1").arg(infoValue);
    case GRP_CTR:
        return QString("%1").arg(infoValue);
    case GRP_TMR:
        return QString("%1").arg(infoValue);
    case GRP_DAQIN:
        return QString("%1").arg(infoValue);
    case GRP_DAQOUT:
        return QString("%1").arg(infoValue);
    case GRP_MEMORY:
        return QString("%1").arg(infoValue);
    default:
        return QString("%1").arg(infoValue);
    }
}

QString LibUtilities::getInfoStrDescription(int infoType, int infoItem, unsigned int index)
{
    (void)infoType;
    (void)infoItem;
    (void)index;
    return "";
}

QString LibUtilities::getConfigDescription(int infoType, int configItem,
                                               long long configValue, unsigned int index)
{
    /*  Returns the string represented by configValue or
     *  returns configValue as a string. Optionally, if
     *  index is represented by a string, prepends that
     *  string followed by "|" for parsing in the calling
     *  function. If configValue is not an int, it's ignored.      */

    QString indexName;

    indexName = "";
    switch (infoType) {
    case GRP_DEVICE:
        if (configItem == DEV_CFG_VER_STR) {
            indexName = getFirmwareNames(index);
            return QString("%1|").arg(indexName);
        }
        return QString("%1").arg(configValue);
    case GRP_AIN:
        if (configItem == AI_CFG_CHAN_TYPE)
            return getAiChanTypeName(configValue);
        if (configItem == AI_CFG_CHAN_TC_TYPE)
            return getTcTypeName(configValue);
        if (configItem == AI_CFG_SCAN_TEMP_UNIT)
            return getTempUnitName(configValue);
        if (configItem == AI_CFG_SCAN_CHAN_TEMP_UNIT)
            return getTempUnitName(configValue);
        if (configItem == AI_CFG_CAL_TABLE_TYPE) {
            QString tableName = getAiCalTableTypeName(configValue);
            indexName = "Base";
            if (index > 0)
                indexName = "EXP";
            return QString("%1|%2").arg(indexName).arg(tableName);
        }
        if (configItem == AI_CFG_REJECT_FREQ_TYPE)
            return getAiRejFreqName(configValue);
        if (configItem == AI_CFG_OTD_MODE)
            return getEnableDisableName(configValue);
        if (configItem == AI_CFG_CHAN_OTD_MODE)
            return getEnableDisableName(configValue);
        if (configItem == AI_CFG_CAL_DATE) {
            indexName = getAiCalTableName(index);
            return QString("%1|%2").arg(indexName).arg(configValue);
        }
        if (configItem == AI_CFG_EXP_CAL_DATE) {
            indexName = getAiCalTableName(index);
            return QString("%1|%2").arg(indexName).arg(configValue);
        }
        return QString("%1").arg(configValue);
    case GRP_AOUT:
        if (configItem == AO_CFG_SYNC_MODE)
            return getAoSyncModeName(configValue);
        if (configItem == AO_CFG_CHAN_SENSE_MODE)
            return getEnableDisableName(configValue);
        return QString("%1").arg(configValue);
    case GRP_DIO:
    case GRP_CTR:
        return QString("%1").arg(configValue);
    case GRP_TMR:
        return QString("%1").arg(configValue);
    case GRP_DAQIN:
        return QString("%1").arg(configValue);
    case GRP_DAQOUT:
        return QString("%1").arg(configValue);
    case GRP_MEMORY:
        return getRegionNames(configValue);
    default:
        return QString("%1").arg(configValue);
    }
}

QString LibUtilities::getConfigDblDescription(int infoType, int configItem,
                                                  double configValue, unsigned int index)
{
    /*  Returns the string represented by configValue or
     *  returns configValue as a string. Optionally, if
     *  index is represented by a string, prepends that
     *  string followed by "|" for parsing in the calling
     *  function.       */

    QString indexName;

    (void)configItem;
    (void)index;
    indexName = "";
    switch (infoType) {
    case GRP_DEVICE:
        return QString("%1").arg(configValue);
    case GRP_AIN:
        return QString("%1").arg(configValue);
    case GRP_AOUT:
        return QString("%1").arg(configValue);
    case GRP_DIO:
        return QString("%1").arg(configValue);
    case GRP_CTR:
        return QString("%1").arg(configValue);
    case GRP_TMR:
        return QString("%1").arg(configValue);
    case GRP_DAQIN:
        return QString("%1").arg(configValue);
    case GRP_DAQOUT:
        return QString("%1").arg(configValue);
    case GRP_MEMORY:
        return QString("%1").arg(configValue);
    default:
        return QString("%1").arg(configValue);
    }
}

QString LibUtilities::getConfigStrDescription(int infoType, int configItem, unsigned int index)
{
    /*  Returns the string represented by index
     *  string followed by "|" for parsing in the calling
     *  function.         */

    QString indexName;

    indexName = "";
    switch (infoType) {
    case GRP_DEVICE:
        if (configItem == DEV_CFG_VER_STR) {
            indexName = getFirmwareNames(index);
            return QString("%1|").arg(indexName);
        }
        return "";
    case GRP_AIN:
        return "";
    case GRP_AOUT:
        return "";
    case GRP_DIO:
        return "";
    case GRP_CTR:
        return "";
    case GRP_TMR:
        return "";
    case GRP_DAQIN:
        return "";
    case GRP_DAQOUT:
        return "";
    case GRP_MEMORY:
        return "";
    default:
        return "";
    }
}

QString LibUtilities::getFirmwareNames(int fwType)
{
    switch (fwType) {
    case DEV_VER_FW_MAIN:
        return "Main";
    case DEV_VER_FPGA:
        return "FPGA";
    case DEV_VER_RADIO:
        return "Radio";
    case DEV_VER_FW_MEASUREMENT:
        return "Measure";
    case DEV_VER_FW_MEASUREMENT_EXP:
        return "Measure EXP";
    default:
        return "";
    }
}

QString LibUtilities::getRangeName(int rangeVal)
{
    switch (rangeVal) {
    case BIP60VOLTS:
        return "Bip60Volts";
    case BIP30VOLTS:
        return "Bip30Volts";
    case BIP15VOLTS:
        return "Bip15Volts";
    case BIP20VOLTS:
        return "Bip20Volts";
    case BIP10VOLTS:
        return "Bip10Volts";
    case BIP5VOLTS:
        return "Bip5Volts";
    case BIP4VOLTS:
        return "Bip4Volts";
    case BIP2PT5VOLTS:
        return "Bip2Pt5Volts";
    case BIP2VOLTS:
        return "Bip2Volts";
    case BIP1PT25VOLTS:
        return "Bip1Pt25Volts";
    case BIP1VOLTS:
        return "Bip1Volts";
    case BIPPT625VOLTS:
        return "BipPt625Volts";
    case BIPPT5VOLTS:
        return "BipPt5Volts";
    case BIPPT25VOLTS:
        return "BipPt25Volts";
    case BIPPT125VOLTS:
        return "BipPt125Volts";
    case BIPPT2VOLTS:
        return "BipPt2Volts";
    case BIPPT1VOLTS:
        return "BipPt1Volts";
    case BIPPT078VOLTS:
        return "BipPt078Volts";
    case BIPPT05VOLTS:
        return "BipPt05Volts";
    case BIPPT01VOLTS:
        return "BipPt01Volts";
    case BIPPT005VOLTS:
        return "BipPt005Volts";
    case BIP3VOLTS:
        return "Bip3Volts";
    case BIPPT312VOLTS:
        return "BipPt312Volts";
    case BIPPT156VOLTS:
        return "BipPt156Volts";
    case UNI60VOLTS:
        return "Uni60Volts";
    case UNI30VOLTS:
        return "Uni30Volts";
    case UNI15VOLTS:
        return "Uni15Volts";
    case UNI20VOLTS:
        return "Uni20Volts";
    case UNI10VOLTS:
        return "Uni10Volts";
    case UNI5VOLTS:
        return "Uni5Volts";
    case UNI4VOLTS:
        return "Uni4Volts";
    case UNI2PT5VOLTS:
        return "Uni2Pt5Volts";
    case UNI2VOLTS:
        return "";
    case UNI1PT25VOLTS:
        return "Uni1Pt25Volts";
    case UNI1VOLTS:
        return "Uni1Volts";
    case UNIPT625VOLTS:
        return "UniPt625Volts";
    case UNIPT5VOLTS:
        return "UniPt5Volts";
    case UNIPT25VOLTS:
        return "UniPt25Volts";
    case UNIPT125VOLTS:
        return "UniPt125Volts";
    case UNIPT2VOLTS:
        return "UniPt2Volts";
    case UNIPT1VOLTS:
        return "UniPt1Volts";
    case UNIPT078VOLTS:
        return "UniPt078Volts";
    case UNIPT05VOLTS:
        return "UniPt05Volts";
    case UNIPT01VOLTS:
        return "UniPt01Volts";
    case UNIPT005VOLTS:
        return "UniPt005Volts";
    case MA0TO20:
        return "0to20ma";
    default:
        return "";
    }
}

QString LibUtilities::getAiChanTypeName(int chanType)
{
    QString chanTypeString;

    if (chanType == 0)
        return "ChanType";
    else {
        if (chanType & AI_VOLTAGE)
            chanTypeString = "Volts, ";
        if (chanType & AI_TC)
            chanTypeString += "TC, ";
        if (chanType & AI_RTD)
            chanTypeString += "RTD, ";
        if (chanType & AI_THERMISTOR)
            chanTypeString += "Tmstr, ";
        if (chanType & AI_SEMICONDUCTOR)
            chanTypeString += "SemiCdr, ";
        if (chanType & AI_DISABLED)
            chanTypeString += "Disabled, ";
        if (chanTypeString.length())
            return chanTypeString.left(chanTypeString.length() - 2);
        return "ChanType";
    }
}

QString LibUtilities::getAiInputModeName(int inMode)
{
    switch (inMode) {
    case AI_DIFFERENTIAL:
        return "Diff";
    case AI_SINGLE_ENDED:
        return "SE";
    case AI_PSEUDO_DIFFERENTIAL:
        return "Pseudo Diff";
    default:
        return "InputMode";
    }
}

QString LibUtilities::getAiCalTableTypeName(int tableType)
{
    //used for table type return, not index
    switch (tableType) {
    case AI_CTT_FACTORY:
        return "Factory";
    case AI_CTT_FIELD:
        return "Field";
    default:
        return "";
    }
}

QString LibUtilities::getAiCalTableName(int index)
{
    //used for index, not table type return
    switch (index) {
    case 0:
        return "Factory";
    case 1:
        return "Field";
    default:
        return "";
    }
}

QString LibUtilities::getAiRejFreqName(int rejType)
{
    switch (rejType) {
    case AI_RFT_60HZ:
        return "60Hz Rejection";
    case AI_RFT_50HZ:
        return "50Hz Rejection";
    default:
        return "";
    }
}

QString LibUtilities::getDaqIChanTypeNames(int typeNum)
{
    int mask;
    DaqInChanType maskedVal;
    QString chanName;

    maskedVal = (DaqInChanType)0;
    for (int i = 0; i < 8; i++) {
        mask = pow(2, i);
        maskedVal = (DaqInChanType)(typeNum & (DaqInChanType)mask);
        switch (maskedVal) {
        case DAQI_ANALOG_DIFF:
            chanName += "AnalogDiff, ";
            break;
        case DAQI_ANALOG_SE:
            chanName += "AnalogSE, ";
            break;
        case DAQI_DIGITAL:
            chanName += "Digital, ";
            break;
        case DAQI_CTR16:
            chanName += "Counter16, ";
            break;
        case DAQI_CTR32:
            chanName += "Counter32, ";
            break;
        case DAQI_CTR48:
            chanName += "Counter48, ";
            break;
        case DAQI_DAC:
            chanName += "DAC, ";
            break;
        default:
            //chanName += "Invalid ChanType, ";
            break;
        }
    }
    int loc = chanName.lastIndexOf(",");
    return chanName.left(loc);
}

QString LibUtilities::getAoSyncModeName(int syncMode)
{
    switch (syncMode) {
    case AOSM_SLAVE:
        return "Slave";
    case AOSM_MASTER:
        return "Master";
    default:
        return "Invalid";
    }
}

QString LibUtilities::getDaqOChanTypeNames(int typeNum)
{
    int mask;
    DaqOutChanType maskedVal;
    QString chanName;

    maskedVal = (DaqOutChanType)0;
    for (int i = 0; i < 2; i++) {
        mask = pow(2, i);
        maskedVal = (DaqOutChanType)(typeNum & (DaqOutChanType)mask);
        switch (maskedVal) {
        case DAQO_ANALOG:
            chanName += "AnalogOut, ";
            break;
        case DAQO_DIGITAL:
            chanName += "DigitalOut, ";
            break;
        default:
            //chanName += "Invalid ChanType, ";
            break;
        }
    }
    int loc = chanName.lastIndexOf(",");
    return chanName.left(loc);
}

QString LibUtilities::getTcTypeName(int tcType)
{
    switch (tcType) {
    case TC_J:
        return "J";
        break;
    case TC_K:
        return "K";
        break;
    case TC_T:
        return "T";
        break;
    case TC_E:
        return "E";
        break;
    case TC_R:
        return "R";
        break;
    case TC_S:
        return "S";
        break;
    case TC_B:
        return "B";
        break;
    case TC_N:
        return "N";
        break;
    default:
        return "TcType";
        break;
    }
}

QString LibUtilities::getTempUnitName(int tempUnit)
{
    switch (tempUnit) {
    case TU_CELSIUS:
        return "Celsius";
    case TU_FAHRENHEIT:
        return "Fahrenheit";
    case TU_KELVIN:
        return "Kelvin";
    default:
        return "";
    }
}

QString LibUtilities::getTrigTypeNames(int trigType)
{
    int mask;
    TriggerType maskedVal;
    QString chanName;

    maskedVal = (TriggerType)0;
    for (int i = 0; i < 19; i++) {
        mask = pow(2, i);
        maskedVal = (TriggerType)(trigType & (TriggerType)mask);
        switch (maskedVal) {
        case TRIG_POS_EDGE:
            chanName += "Positive Edge, ";
            break;
        case TRIG_NEG_EDGE:
            chanName += "Negative Edge, ";
            break;
        case TRIG_HIGH:
            chanName += "TrigHigh, ";
            break;
        case TRIG_LOW:
            chanName += "TrigLow, ";
            break;
        case GATE_HIGH:
            chanName += "GateHigh, ";
            break;
        case GATE_LOW:
            chanName += "GateLow, ";
            break;
        case TRIG_RISING:
            chanName += "TrigRising, ";
            break;
        case TRIG_FALLING:
            chanName += "TrigFalling, ";
            break;
        case TRIG_ABOVE:
            chanName += "TrigAbove, ";
            break;
        case TRIG_BELOW:
            chanName += "TrigBelow, ";
            break;
        case GATE_ABOVE:
            chanName += "GateAbove, ";
            break;
        case GATE_BELOW:
            chanName += "GateBelow, ";
            break;
        case GATE_IN_WINDOW:
            chanName += "GateInWindow, ";
            break;
        case GATE_OUT_WINDOW:
            chanName += "GateOutWindow, ";
            break;
        case TRIG_PATTERN_EQ:
            chanName += "TrigPatternEq, ";
            break;
        case TRIG_PATTERN_NE:
            chanName += "TrigPatternNE, ";
            break;
        case TRIG_PATTERN_ABOVE:
            chanName += "TrigPatternAbove, ";
            break;
        case TRIG_PATTERN_BELOW:
            chanName += "TrigPatternBelow, ";
            break;
        default:
            break;
        }
    }
    int loc = chanName.lastIndexOf(",");
    return chanName.left(loc);
}

QString LibUtilities::getQueueTypeNames(int queueTypes)
{
    int mask;
    AiQueueType maskedVal;
    QString chanName;

    maskedVal = (AiQueueType)0;
    for (int i = 0; i < 3; i++) {
        mask = pow(2, i);
        maskedVal = (AiQueueType)(queueTypes & (AiQueueType)mask);
        switch (maskedVal) {
        case CHAN_QUEUE:
            chanName += "ChanQueue, ";
            break;
        case GAIN_QUEUE:
            chanName += "GainQueue, ";
            break;
        case MODE_QUEUE:
            chanName += "ModeQueue, ";
            break;
        default:
            //chanName += "QType, ";
            break;
        }
    }
    int loc = chanName.lastIndexOf(",");
    return chanName.left(loc);
}

QString LibUtilities::getQueueLimitNames(int queueLimits)
{
    int mask;
    AiChanQueueLimitation maskedVal;
    QString chanName;

    maskedVal = (AiChanQueueLimitation)0;
    for (int i = 0; i < 2; i++) {
        mask = pow(2, i);
        maskedVal = (AiChanQueueLimitation)(queueLimits & (AiChanQueueLimitation)mask);
        switch (maskedVal) {
        case UNIQUE_CHAN:
            chanName += "Unique, ";
            break;
        case ASCENDING_CHAN:
            chanName += "Ascending, ";
            break;
        default:
            //chanName += "QLimit, ";
            break;
        }
    }
    int loc = chanName.lastIndexOf(",");
    return chanName.left(loc);
}

QString LibUtilities::getDigitalDirection(int digDir)
{
    switch (digDir) {
    case DD_INPUT:
        return "Input";
    case DD_OUTPUT:
        return "Output";
    default:
        return "Direction";
    }
}

QString LibUtilities::getDioPortTypeName(int typeNum)
{
    switch (typeNum) {
    case AUXPORT0:
        return "Auxport0";
    case AUXPORT1:
        return "Auxport1";
    case AUXPORT2:
        return "Auxport2";
    case FIRSTPORTA:
        return "FirstPortA";
    case FIRSTPORTB:
        return "FirstPortB";
    case FIRSTPORTCL:
        return "FirstPortCL";
    case FIRSTPORTCH:
        return "FirstPortCH";
    case SECONDPORTA:
        return "SecondPortA";
    case SECONDPORTB:
        return "SecondPortB";
    case SECONDPORTCL:
        return "SecondPortCL";
    case SECONDPORTCH:
        return "SecondPortCH";
    case THIRDPORTA:
        return "ThirdPortA";
    case THIRDPORTB:
        return "ThirdPortB";
    case THIRDPORTCL:
        return "ThirdPortCL";
    case THIRDPORTCH:
        return "ThirdPortCH";
    case FOURTHPORTA:
        return "FourthPortA";
    case FOURTHPORTB:
        return "FourthPortB";
    case FOURTHPORTCL:
        return "FourthPortCL";
    case FOURTHPORTCH:
        return "FourthPortCH";
    case FIFTHPORTA:
        return "FifthPortA";
    case FIFTHPORTB:
        return "FifthPortB";
    case FIFTHPORTCL:
        return "FifthPortCL";
    case FIFTHPORTCH:
        return "FifthPortCH";
    case SIXTHPORTA:
        return "SixthPortA";
    case SIXTHPORTB:
        return "SixthPortB";
    case SIXTHPORTCL:
        return "SixthPortCL";
    case SIXTHPORTCH:
        return "SixthPortCH";
    case SEVENTHPORTA:
        return "SeventhPortA";
    case SEVENTHPORTB:
        return "SeventhPortB";
    case SEVENTHPORTCL:
        return "SeventhPortCL";
    case SEVENTHPORTCH:
        return "SeventhPortCH";
    case EIGHTHPORTA:
        return "EighthPortA";
    case EIGHTHPORTB:
        return "EighthPortB";
    case EIGHTHPORTCL:
        return "EighthPortCL";
    case EIGHTHPORTCH:
        return "EighthPortCH";
    default:
        return "PortType";
    }
}

QString LibUtilities::getDioPortTypeDesig(int typeNum)
{
    switch (typeNum) {
    case AUXPORT0:
        return "AX0";
    case AUXPORT1:
        return "AX1";
    case AUXPORT2:
        return "AX2";
    case FIRSTPORTA:
        return "1A";
    case FIRSTPORTB:
        return "1B";
    case FIRSTPORTCL:
        return "1CL";
    case FIRSTPORTCH:
        return "1CH";
    case SECONDPORTA:
        return "2A";
    case SECONDPORTB:
        return "2B";
    case SECONDPORTCL:
        return "2CL";
    case SECONDPORTCH:
        return "2CH";
    case THIRDPORTA:
        return "3A";
    case THIRDPORTB:
        return "3B";
    case THIRDPORTCL:
        return "3CL";
    case THIRDPORTCH:
        return "3CH";
    case FOURTHPORTA:
        return "4A";
    case FOURTHPORTB:
        return "4B";
    case FOURTHPORTCL:
        return "4CL";
    case FOURTHPORTCH:
        return "4CH";
    case FIFTHPORTA:
        return "5A";
    case FIFTHPORTB:
        return "5B";
    case FIFTHPORTCL:
        return "5CL";
    case FIFTHPORTCH:
        return "5CH";
    case SIXTHPORTA:
        return "6A";
    case SIXTHPORTB:
        return "6B";
    case SIXTHPORTCL:
        return "6CL";
    case SIXTHPORTCH:
        return "6CH";
    case SEVENTHPORTA:
        return "7A";
    case SEVENTHPORTB:
        return "7B";
    case SEVENTHPORTCL:
        return "7CL";
    case SEVENTHPORTCH:
        return "7CH";
    case EIGHTHPORTA:
        return "8A";
    case EIGHTHPORTB:
        return "8B";
    case EIGHTHPORTCL:
        return "8CL";
    case EIGHTHPORTCH:
        return "8CH";
    default:
        return "Invalid Type";
        break;
    }
}

QString LibUtilities::getDPortIoTypeName(int ioType)
{
    switch (ioType) {
    case DPIOT_IN:
        return "Fixed input";
    case DPIOT_OUT:
        return "Fixed output";
    case DPIOT_IO:
        return "IO Port-Config";
    case DPIOT_BITIO:
        return "IO Bit-Config";
    case DPIOT_NONCONFIG:
        return "IO Non-Config";
    default:
        return "PortIOType";
    }
}

QString LibUtilities::getCtrTypeName(int ctrType)
{
    switch (ctrType) {
    case 1:
        return "82C54";
    case 2:
        return "9513";
    case 3:
        return "8536";
    case 4:
        return "7266";
    case 5:
        return "Event Counter";
    case 6:
        return "Scan Counter";
    case 7:
        return "Timer Out";
    case 8:
        return "Quad Counter";
    case 9:
        return "Pulse Out";
    default:
        return "";
    }
}

QString LibUtilities::getCtrMeasTypeNames(int typeNum)
{
    int mask;
    int maskedVal;
    QString chanName;

    maskedVal = 0;
    for (int i = 0; i < 6; i++) {
        mask = pow(2, i);
        maskedVal = (typeNum & mask);
        switch (maskedVal) {
        case CMT_COUNT:
            chanName += "Count, ";
            break;
        case CMT_PERIOD:
            chanName += "Period, ";
            break;
        case CMT_PULSE_WIDTH:
            chanName += "PulseWidth, ";
            break;
        case CMT_TIMING:
            chanName += "Timing, ";
            break;
        case CMT_ENCODER:
            chanName += "Encoder, ";
            break;
        default:
            //chanName += "Invalid CtrType, ";
            break;
        }
    }
    int loc = chanName.lastIndexOf(",");
    return chanName.left(loc);
}

QString LibUtilities::getCtrRegTypeNames(int regType)
{
    int mask;
    int maskedVal;
    QString regName;

    maskedVal = 0;
    for (int i = 0; i < 6; i++) {
        mask = pow(2, i);
        maskedVal = (regType & mask);
        switch (maskedVal) {
        case CRT_COUNT:
            regName += "Count, ";
            break;
        case CRT_LOAD:
            regName += "Load, ";
            break;
        case CRT_MIN_LIMIT:
            regName += "MinLimit, ";
            break;
        case CRT_MAX_LIMIT:
            regName += "MaxLimit, ";
            break;
        case CRT_OUTPUT_VAL0:
            regName += "Output0, ";
            break;
        case CRT_OUTPUT_VAL1:
            regName += "Output1, ";
            break;
        default:
            //regName += "Invalid RegType, ";
            break;
        }
    }
    int loc = regName.lastIndexOf(",");
    return regName.left(loc);
}

QString LibUtilities::getCtrMeasModeNames(int modeNum)
{
    int mask;
    int maskedVal;
    QString modeName;

    if (modeNum == 0)
        return "Default";

    maskedVal = 0;
    for (int i = 0; i < 26; i++) {
        mask = pow(2, i);
        maskedVal = (modeNum & mask);
        switch (maskedVal) {
        case CMM_CLEAR_ON_READ:
            modeName += "ClearOnRead, ";
            break;
        case CMM_COUNT_DOWN:
            modeName += "CountDown, ";
            break;
        case CMM_GATE_CONTROLS_DIR:
            modeName += "GateDir, ";
            break;
        case CMM_GATE_CLEARS_CTR:
            modeName += "GateClear, ";
            break;
        case CMM_GATE_TRIG_SRC:
            modeName += "GateTrig, ";
            break;
        case CMM_OUTPUT_ON:
            modeName += "OutputOn, ";
            break;
        case CMM_OUTPUT_INITIAL_STATE_HIGH:
            modeName += "InitHigh, ";
            break;
        case CMM_NO_RECYCLE:
            modeName += "NoRecycle, ";
            break;
        case CMM_RANGE_LIMIT_ON:
            modeName += "Rangelimit, ";
            break;
        case CMM_GATING_ON:
            modeName += "GateOn, ";
            break;
        case CMM_INVERT_GATE:
            modeName += "InvGate, ";
            break;
        case CMM_PERIOD_X10:
            modeName += "Per X10, ";
            break;
        case CMM_PERIOD_X100:
            modeName += "Per X100, ";
            break;
        case CMM_PERIOD_X1000:
            modeName += "Per X1000, ";
            break;
        case CMM_PERIOD_GATING_ON:
            modeName += "Per GateOn, ";
            break;
        case CMM_PERIOD_INVERT_GATE:
            modeName += "Per InvGate, ";
            break;
        case CMM_PULSE_WIDTH_GATING_ON:
            modeName += "Pw GateOn, ";
            break;
        case CMM_PULSE_WIDTH_INVERT_GATE:
            modeName += "Pw InvGate, ";
            break;
        case CMM_TIMING_MODE_INVERT_GATE:
            modeName += "T InvGate, ";
            break;
        case CMM_ENCODER_X2:
            modeName += "E X2, ";
            break;
        case CMM_ENCODER_X4:
            modeName += "E X4, ";
            break;
        case CMM_ENCODER_LATCH_ON_Z:
            modeName += "E LatchZ, ";
            break;
        case CMM_ENCODER_CLEAR_ON_Z:
            modeName += "E ClearZ, ";
            break;
        case CMM_ENCODER_NO_RECYCLE:
            modeName += "E NoRecycle, ";
            break;
        case CMM_ENCODER_RANGE_LIMIT_ON:
            modeName += "E Rangelimit, ";
            break;
        case CMM_ENCODER_Z_ACTIVE_EDGE:
            modeName += "Z Edge, ";
            break;
        default:
            //modeName += "Invalid RegType, ";
            break;
        }
    }
    int loc = modeName.lastIndexOf(",");
    return modeName.left(loc);
}

QString LibUtilities::getTmrTypeName(int tmrType)
{
    switch (tmrType) {
    case TMR_STANDARD:
        return "Standard";
        break;
    case TMR_ADVANCED:
        return "Advanced";
        break;
    default:
        return "TimerType";
        break;
    }
}

QString LibUtilities::getEventNames(int eventMask)
{
    QString eventString;

    if (eventMask == 0)
        return "No Events";
    else {
        if (eventMask & DE_ON_DATA_AVAILABLE)
            eventString = "OnDataAvailable, ";
        if (eventMask & DE_ON_INPUT_SCAN_ERROR)
            eventString += "OnInScanError, ";
        if (eventMask & DE_ON_END_OF_INPUT_SCAN)
            eventString += "OnEndOfInScan, ";
        if (eventMask & DE_ON_OUTPUT_SCAN_ERROR)
            eventString += "OnOutScanError, ";
        if (eventMask & DE_ON_END_OF_OUTPUT_SCAN)
            eventString += "OnEndOfOutScan, ";
        if (eventString.length())
            return eventString.left(eventString.length() - 2);
        return "EventType";
    }
}

QString LibUtilities::getRegionNames(int memRegion)
{
    QString regionNames;

    if (memRegion == 0)
        return "None";
    else {
        if (memRegion & MR_CAL)
            regionNames = "Cal, ";
        if (memRegion & MR_USER)
            regionNames += "User, ";
        if (memRegion & MR_SETTINGS)
            regionNames += "Settings, ";
        if (memRegion & MR_RESERVED0)
            regionNames += "Reserved0, ";
        if (regionNames.length())
            return regionNames.left(regionNames.length() - 2);
        return "MemRegion";
    }
}

QString LibUtilities::getEnableDisableName(int value)
{
    switch (value) {
    case 1:
        return "Disabled";
    case 2:
        return "Enabled";
    default:
        return "Enabled???";
    }
}
