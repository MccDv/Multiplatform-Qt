#include "libutilities.h"

LibUtilities::LibUtilities()
{

}

QString LibUtilities::getHatTypeName(uint16_t hatType)
{
    switch (hatType) {
    case HAT_ID_MCC_118:
        return "MCC118";
        break;
#ifdef HAT_03
    case HAT_ID_MCC_134:
        return "MCC134";
        break;
#endif
#ifdef HAT_04
    case HAT_ID_MCC_152:
        return "MCC152";
        break;
#endif
#ifdef HAT_05
    case HAT_ID_MCC_172:
        return "MCC172";
        break;
#endif
#ifdef HAT_06
    case HAT_ID_MCC_128:
        return "MCC128";
        break;
#endif
    default:
        return "NO_ID";
        break;
    }
}

double LibUtilities::getRangeVolts(int rangeVal)
{
    switch (rangeVal) {
    case A_IN_RANGE_BIP_10V:
        return 20;
    case A_IN_RANGE_BIP_5V:
        return 10;
    case A_IN_RANGE_BIP_2V:
        return 4;
    case A_IN_RANGE_BIP_1V:
        return 2;
    default:
        return 0;
    }
}

QString LibUtilities::getRangeNomo(int rangeVal)
{
    double curRangeVolts;

    switch (rangeVal) {
    case A_IN_RANGE_BIP_10V:
        curRangeVolts = 10;
        break;
    case A_IN_RANGE_BIP_5V:
        curRangeVolts = 5;
        break;
    case A_IN_RANGE_BIP_2V:
        curRangeVolts = 2;
        break;
    case A_IN_RANGE_BIP_1V:
        curRangeVolts = 1;
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
        if (curOptions & OPTS_CONTINUOUS)
            optString += "Continuous, ";
        if (curOptions & OPTS_EXTCLOCK)
            optString += "ExtClock, ";
        if (curOptions & OPTS_EXTTRIGGER)
            optString += "ExtTrigger, ";
        if (curOptions & OPTS_NOSCALEDATA)
            optString += "NoScaleData, ";
        if (curOptions & OPTS_NOCALIBRATEDATA)
            optString += "NoCalData, ";
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
    return indexName;
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
    return "Main";
}

QString LibUtilities::getRangeName(int rangeVal)
{
    switch (rangeVal) {
    case A_IN_RANGE_BIP_10V:
        return "Bip10Volts";
    case A_IN_RANGE_BIP_5V:
        return "Bip5Volts";
    case A_IN_RANGE_BIP_2V:
        return "Bip2Volts";
    case A_IN_RANGE_BIP_1V:
        return "Bip1Volts";
    default:
        return "BadRange";
    }
}

QString LibUtilities::getAiChanTypeName(int chanType)
{
    return "ChanType";
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
    return "";
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
    return "";
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
    return "Invalid";
}

QString LibUtilities::getDaqOChanTypeNames(int typeNum)
{
    int mask;
    return 0;
}

QString LibUtilities::getTempUnitName(int tempUnit)
{
    return "Celsius";
}

QString LibUtilities::getTrigTypeNames(int trigType)
{
    switch (trigType) {
    case TRIG_RISING_EDGE:
        return "RisingEdge";
        break;
    case TRIG_FALLING_EDGE:
        return "FallingEdge";
        break;
    case TRIG_ACTIVE_HIGH:
        return "ActiveHigh";
        break;
    case TRIG_ACTIVE_LOW:
        return "ActiveLow";
        break;
    default:
        return "";
    }
}

QString LibUtilities::getQueueTypeNames(int queueTypes)
{
    int mask;

    return "queue";
}

QString LibUtilities::getQueueLimitNames(int queueLimits)
{
    return 0;
}

QString LibUtilities::getDigitalDirection(int digDir)
{
    switch (digDir) {
    case 1:
        return "Input";
    case 0:
        return "Output";
    default:
        return "Direction";
    }
}

QString LibUtilities::getDioPortTypeName(int typeNum)
{
    return "PortType";
}

QString LibUtilities::getDioPortTypeDesig(int typeNum)
{
    return "1A";
}

QString LibUtilities::getDPortIoTypeName(int ioType)
{
    return "PortIOType";
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

    return "";
}

QString LibUtilities::getCtrRegTypeNames(int regType)
{
    int mask;
    int maskedVal;
    QString regName;

    regName += "Invalid RegType";
    return regName;
}

QString LibUtilities::getCtrMeasModeNames(int modeNum)
{
    int mask;
    int maskedVal;
    QString modeName;

    return "Default";

}

QString LibUtilities::getTmrTypeName(int tmrType)
{
    return "Standard";
}

QString LibUtilities::getEventNames(int eventMask)
{
    return "EventType";
}

QString LibUtilities::getRegionNames(int memRegion)
{
    QString regionNames;

    return "MemRegion";
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

#ifdef HAT_03

QString getTcTypeName(uint8_t tcType)
{
    switch (tcType) {
    case TC_TYPE_J:
        return "J";
        break;
    case TC_TYPE_K:
        return "K";
        break;
    case TC_TYPE_T:
        return "T";
        break;
    case TC_TYPE_E:
        return "E";
        break;
    case TC_TYPE_R:
        return "R";
        break;
    case TC_TYPE_S:
        return "S";
        break;
    case TC_TYPE_B:
        return "B";
        break;
    case TC_TYPE_N:
        return "N";
        break;
    case TC_DISABLED:
        return "Disabled";
        break;
    default:
        return "unknown";
        break;
    }
}

/*QVector <uint8_t> getTcTypesFromString(QString tcTypes)
{
    QString  chanString;
    int nextIndex, prevIndex;
    QVector<uint8_t> tcTypeVector;

    nextIndex = 0;
    prevIndex = 0;
    chanString = "";
    do {
        nextIndex = tcTypes.indexOf(",", nextIndex);
        chanString = tcTypes.mid(prevIndex, nextIndex - prevIndex);
        nextIndex++;
        prevIndex = nextIndex;
        tcTypeVector.push_back(chanString.toUInt());
    } while (nextIndex > 0);
    return tcTypeVector;
}*/

QString setTcTypeInString(QString tcTypes, uint8_t chan, uint8_t newType)
{
    QString typePrefs;
    QString newTypeString;
    int nextIndex, prevIndex, chanIndex;
    int numChars;

    nextIndex = 0;
    prevIndex = 0;
    chanIndex = 0;
    numChars = 1;
    //chanString = "";
    typePrefs = tcTypes;
    newTypeString = QString("%1").arg(newType);
    do {
        nextIndex = tcTypes.indexOf(",", nextIndex);
        //chanString = tcTypes.mid(prevIndex, nextIndex - prevIndex);
        if(chan == chanIndex) {
            numChars = (nextIndex - prevIndex);
            if (numChars < 0)
                numChars = 255;
            typePrefs.replace(prevIndex, numChars, newTypeString);
            break;
        } else {
            nextIndex++;
            prevIndex = nextIndex;
            nextIndex = tcTypes.indexOf(",", nextIndex);
        }
        chanIndex ++;
    } while (chanIndex <= chan);
    return typePrefs;
}

#else

QString getTcTypeName(uint8_t tcType)
{
    (void)tcType;
    return "";
}

QVector <uint8_t> getTcTypesFromString(QString tcTypes)
{
    QVector <uint8_t> tcTypeVector;

    tcTypeVector.clear();
    (void)tcTypes;
    return tcTypeVector;
}

QString setTcTypeInString(QString tcTypes, uint8_t chan, uint8_t newType)
{
    (void)tcTypes;
    (void)chan;
    (void)newType;
    return "";
}

#endif
