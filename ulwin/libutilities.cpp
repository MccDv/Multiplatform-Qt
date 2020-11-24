#include "libutilities.h"

LibUtilities::LibUtilities()
{

}

double LibUtilities::getRangeVolts(int rangeVal)
{
    switch (rangeVal) {
    case NOTUSED:
        return 0;
    case BIP5VOLTS:
        return 10;
    case BIP10VOLTS:
        /*case "PCI-DAC6702", "PCI-DAC6703", "PCI-DAC6704"
             RangeString = "BIP10VOLTS"
             return 20.48
          'case "USB-6003"
          '   RangeString = "BIP10.5VOLTS"
          '   return 21#
          case Else
            RangeString = "BIP10VOLTS"*/
        return 20;
    case BIP2PT5VOLTS:
        return 5;
    case BIP1PT25VOLTS:
        return 2.5;
    case BIP1VOLTS:
        return 2;
    case BIPPT625VOLTS:
        return 1.25;
    case BIPPT5VOLTS:
        return 1;
    case BIPPT1VOLTS:
        return 0.2;
    case BIPPT05VOLTS:
        return 0.1;
    case BIPPT01VOLTS:
        return 0.02;
    case BIPPT005VOLTS:
        return 0.01;
    case BIP1PT67VOLTS:
        return 3.34;
    case BIPPT312VOLTS:
        return 0.625;
    case BIPPT156VOLTS:
        return 0.3125;
    case BIPPT078VOLTS:
        return 0.15625;
    case BIP60VOLTS:
        return 120;  //125.274
        //'to do - switch to toengunits
    case BIP15VOLTS:
        return 30;
    case BIPPT125VOLTS:
        return 0.25;
    case BIPPT25VOLTS:
        return 0.5;
    case BIPPT2VOLTS:
        return 0.4;
    case BIP2VOLTS:
        return 4;
    case BIP20VOLTS:
        return 40;
    case BIP4VOLTS:
        return 8;
    case BIP30VOLTS:
        return 60;
    case BIPPT025VOLTSPERVOLT:
        return 0.05;
    //case BIPPT073125VOLTS:
    //    return 0.14625;
    case UNI10VOLTS:
        return 10;
    case UNI5VOLTS:
        return 5;
    case UNI2PT5VOLTS:
        return 2.5;
    case UNI2VOLTS:
        return 2;
    case UNI1PT25VOLTS:
        return 1.25;
    case UNI1VOLTS:
        return 1;
    case UNIPT1VOLTS:
        return 0.1;
    case UNIPT01VOLTS:
        return 0.01;
    case UNIPT02VOLTS:
        return 0.02;
    case UNI1PT67VOLTS:
        return 1.67;
    case UNIPT5VOLTS:
        return 0.5;
    case UNIPT25VOLTS:
        return 0.25;
    case UNIPT2VOLTS:
        return 0.2;
    case UNIPT05VOLTS:
        return 0.05;
    case UNI4VOLTS:
        return 4.096;
    case MA4TO20:
        return 16;
    //case MA2to10:
    //    return 8;
    case MA1TO5:
        return 4;
    case MAPT5TO2PT5:
        return 2;
    case MA0TO20:
        return 20;
    case BIPPT025AMPS:
        return 0.05;
    default:
        return 0;
    }
}

QString LibUtilities::getRangeNomo(int rangeVal)
{
    double curRangeVolts;

    switch (rangeVal) {
    case NOTUSED:
        curRangeVolts = 0;
        break;
    case BIP5VOLTS:
        curRangeVolts = 5;
        break;
    case BIP10VOLTS:
        /*case "PCI-DAC6702", "PCI-DAC6703", "PCI-DAC6704"
             RangeString = "BIP10VOLTS"
             curRangeVolts = 20.48
          'case "USB-6003"
          '   RangeString = "BIP10.5VOLTS"
          '   curRangeVolts = 21#
          case Else
            RangeString = "BIP10VOLTS"*/
        curRangeVolts = 10;
        break;
    case BIP2PT5VOLTS:
        curRangeVolts = 2.5;
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
    case BIPPT1VOLTS:
        curRangeVolts = 0.1;
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
    case BIP1PT67VOLTS:
        curRangeVolts = 1.67;
        break;
    case BIPPT312VOLTS:
        curRangeVolts = 0.312;
        break;
    case BIPPT156VOLTS:
        curRangeVolts = 0.156;
        break;
    case BIPPT078VOLTS:
        curRangeVolts = 0.078125;
        break;
    case BIP60VOLTS:
        curRangeVolts = 60;  //125.274
        break;
    case BIP15VOLTS:
        curRangeVolts = 15;
        break;
    case BIPPT125VOLTS:
        curRangeVolts = 0.125;
        break;
    case BIPPT25VOLTS:
        curRangeVolts = 0.25;
        break;
    case BIPPT2VOLTS:
        curRangeVolts = 0.2;
        break;
    case BIP2VOLTS:
        curRangeVolts = 2;
        break;
    case BIP20VOLTS:
        curRangeVolts = 20;
        break;
    case BIP4VOLTS:
        curRangeVolts = 4;
        break;
    case BIP30VOLTS:
        curRangeVolts = 30;
        break;
    case BIPPT025VOLTSPERVOLT:
        curRangeVolts = 0.025;
        break;
    //case BIPPT073125VOLTS:
    //    curRangeVolts = 0.073125;
    case UNI10VOLTS:
        curRangeVolts = 10;
        break;
    case UNI5VOLTS:
        curRangeVolts = 5;
        break;
    case UNI2PT5VOLTS:
        curRangeVolts = 2.5;
        break;
    case UNI2VOLTS:
        curRangeVolts = 2;
        break;
    case UNI1PT25VOLTS:
        curRangeVolts = 1.25;
        break;
    case UNI1VOLTS:
        curRangeVolts = 1;
        break;
    case UNIPT1VOLTS:
        curRangeVolts = 0.1;
        break;
    case UNIPT01VOLTS:
        curRangeVolts = 0.01;
        break;
    case UNIPT02VOLTS:
        curRangeVolts = 0.02;
        break;
    case UNI1PT67VOLTS:
        curRangeVolts = 1.67;
        break;
    case UNIPT5VOLTS:
        curRangeVolts = 0.5;
        break;
    case UNIPT25VOLTS:
        curRangeVolts = 0.25;
        break;
    case UNIPT2VOLTS:
        curRangeVolts = 0.2;
        break;
    case UNIPT05VOLTS:
        curRangeVolts = 0.05;
        break;
    case UNI4VOLTS:
        curRangeVolts = 4.096;
        break;
    case MA4TO20:
        curRangeVolts = 16;
        break;
    //case MA2to10:
    //    curRangeVolts = 8;
    case MA1TO5:
        curRangeVolts = 4;
        break;
    case MAPT5TO2PT5:
        curRangeVolts = 2;
        break;
    case MA0TO20:
        curRangeVolts = 20;
        break;
    case BIPPT025AMPS:
        curRangeVolts = 0.05;
        break;
    default:
        curRangeVolts = 0;
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
    //case DAQI_CTR48:
    //    return 6;
    //case DAQI_DAC:
    //    return 7;
    default:
        return 0;
    }
}

QString LibUtilities::getOptionNames(int curOptions)
{
    QString optString = "";

    if (curOptions == 0)
        optString = "Default";
    else {
        if ((curOptions & BLOCKIO) == BLOCKIO)
            optString = "BlockIO, ";
        else {
            if (curOptions & SINGLEIO)
                optString = "SingleIO, ";
            if (curOptions & DMAIO)
                optString = "DMAIo, ";
        }
        if (curOptions & BURSTIO)
            optString = "BurstIO, ";
        if (curOptions & CONTINUOUS)
            optString += "Continuous, ";
        if (curOptions & BACKGROUND)
            optString += "Background, ";
        if (curOptions & EXTCLOCK)
            optString += "ExtClock, ";
        if (curOptions & EXTTRIGGER)
            optString += "ExtTrigger, ";
        if (curOptions & RETRIGMODE)
            optString += "ReTrigger, ";
        if (curOptions & BURSTMODE)
            optString += "BurstMode, ";
        if (curOptions & CONVERTDATA)
            optString += "ConvertData, ";
        if (curOptions & SCALEDATA)
            optString += "ScaleData, ";
        if (curOptions & NONSTREAMEDIO)
            optString += "NonStreamedIO, ";
        if (curOptions & ADCCLOCKTRIG)
            optString += "AdcClockTrig, ";
        if (curOptions & ADCCLOCK)
            optString += "AdcClock, ";
        if (curOptions & HIGHRESRATE)
            optString += "HighResRate, ";
        if (curOptions & NOCALIBRATEDATA)
            optString += "NoCalibrateData, ";
        if (curOptions & WAITFORNEWDATA)
            optString += "WaitForNewData, ";
        if (curOptions & NOFILTER)
            optString += "NoFilter, ";
        if (optString.length() > 2)
            optString = optString.left(optString.length() - 2);
    }
    return optString;
}

QString LibUtilities::getDigOptionNames(int curOptions)
{
    QString optString = "";

    if (curOptions == 0)
        optString = "Default";
    else {
        if (curOptions & WORDXFER)
            optString += "WordXfer, ";
        if (curOptions & DWORDXFER)
            optString += "DWordXfer, ";
        if (optString.length() > 2)
            optString = optString.left(optString.length() - 2);
    }
    return optString;
}

QString LibUtilities::getCtrOptionNames(int curOptions)
{
    QString optString = "";

    if (curOptions == 0)
        optString = "Default";
    else {
        if (curOptions & CTR32BIT)
            optString += "Ctr32Bit, ";
        if (curOptions & CTR64BIT)
            optString += "Ctr64Bit, ";
        if (curOptions & CTR48BIT)
            optString += "Ctr48Bit, ";
        if (optString.length() > 2)
            optString = optString.left(optString.length() - 2);
    }
    return optString;
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

    (void)index;
    indexName = "";
    switch (infoType) {
    case GRP_DEVICE:
        return QString("%1").arg(infoValue);
    case GRP_AIN:
        if (infoItem == BIADCHANMODE)
            return getAiInputModeName(infoValue);
        if (infoItem == BIADSCANOPTIONS)
            return getOptionNames(infoValue);
        if ((infoItem == BIADDIFFRANGE) | (infoItem == BIADSERANGE))
            return getRangeName((int)infoValue);
        if (infoItem == BIADTRIGTYPE)
            return getTrigTypeNames(infoValue);
        if (infoItem == BIADQUEUETYPES)
            return getQueueTypeNames(infoValue);
        if (infoItem == BIADQUEUELIMITS)
            return getQueueLimitNames(infoValue);
        return QString("%1").arg(infoValue);
    case GRP_AOUT:
        if (infoItem == BIDACDEVRANGE)
            return getRangeName((int)infoValue);
        if (infoItem == BIDACSCANOPTIONS)
            return getOptionNames(infoValue);
        if (infoItem == BIDACTRIGTYPE)
            return getTrigTypeNames(infoValue);
        return QString("%1").arg(infoValue);
    case GRP_DIO:
        if ((infoItem == BIDISCANOPTIONS) | (infoItem == BIDOSCANOPTIONS))
            return getOptionNames(infoValue);
        if (infoItem == DIDEVTYPE)
            return getDioPortTypeName(infoValue);
        return QString("%1").arg(infoValue);
    case GRP_CTR:
        if (infoItem == CICTRTYPE)
            return getCtrTypeName(infoValue);
        if (infoItem == BICTRSCANOPTIONS)
            return getOptionNames(infoValue);
        return QString("%1").arg(infoValue);
    case GRP_TMR:
        return QString("%1").arg(infoValue);
    case GRP_DAQIN:
        if (infoItem == BIDAQISCANOPTIONS)
            return getOptionNames(infoValue);
        return QString("%1").arg(infoValue);
    case GRP_DAQOUT:
        if (infoItem == BIDAQOSCANOPTIONS)
            return getOptionNames(infoValue);
        return QString("%1").arg(infoValue);
    case GRP_MEMORY:
        return QString("%1").arg(infoValue);
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

QString LibUtilities::getConfigDescription(int configType, int configItem,
                                                 long long configValue, unsigned int index)
{
    /*  Returns the string represented by configValue or
     *  returns configValue as a string. Optionally, if
     *  index is represented by a string, prepends that
     *  string followed by "|" for parsing in the calling
     *  function. If configValue is not an int, it's ignored.      */

    QString indexName;

    indexName = "";
    switch (configType) {
    case GRP_DEVICE:
        if (configItem == BIDEVVERSION) {
            indexName = getFirmwareNames(index);
            return QString("%1|").arg(indexName);
        }
        return QString("%1").arg(configValue);
    case GRP_AIN:
        if (configItem == BICALTABLETYPE)
            return getAiCalTableName(configValue);
        if (configItem == BITEMPREJFREQ)
            return getAiRejFreqName(configValue);
        return QString("%1").arg(configValue);
    case GRP_AOUT:
        if (configItem == BISYNCMODE)
            return getAoSyncModeName(configValue);
        return QString("%1").arg(configValue);
    case GRP_DIO:
        return QString("%1").arg(configValue);
    case GRP_CTR:
        return QString("%1").arg(configValue);
    case GRP_TMR:
        return QString("%1").arg(configValue);
    case GRP_DAQIN:
        if (configItem == BIDAQICHANTYPE)
            return getDaqIChanTypeNames(configValue);
        return QString("%1").arg(configValue);
    case GRP_DAQOUT:
        if (configItem == BIDAQOCHANTYPE)
            return getDaqOChanTypeNames(configValue);
        return QString("%1").arg(configValue);
    case GRP_MEMORY:
        return QString("%1").arg(configValue);
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
        if (configItem == BIDEVVERSION) {
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
    case VER_FW_MAIN:
        return "Main";
    case VER_FW_MEASUREMENT:
        return "Measure";
    case VER_FW_RADIO:
        return "Radio";
    case VER_FPGA:
        return "FPGA";
    case VER_FW_MEASUREMENT_EXP:
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
    case BIPPT312VOLTS:
        return "BipPt312Volts";
    case BIPPT156VOLTS:
        return "BipPt156Volts";
    case UNI10VOLTS:
        return "Uni10Volts";
    case UNI5VOLTS:
        return "Uni5Volts";
    case UNI4VOLTS:
        return "Uni4Volts";
    case UNI2PT5VOLTS:
        return "Uni2Pt5Volts";
    case UNI2VOLTS:
        return "Uni2Volts";
    case UNI1PT25VOLTS:
        return "Uni1Pt25Volts";
    case UNI1VOLTS:
        return "Uni1Volts";
    case MA0TO20:
        return "0to20ma";
    default:
        return "Invalid Range";
    }
}

QString LibUtilities::getAiChanTypeName(int chanType)
{
    QString chanTypeString;

    if (chanType == 0)
        return "Invalid Type";
    else {
        if (chanType & AI_CHAN_TYPE_VOLTAGE)
            chanTypeString = "Volts, ";
        if (chanType & AI_CHAN_TYPE_CURRENT)
            chanTypeString += "Current, ";
        if (chanType & AI_CHAN_TYPE_RESISTANCE_10K4W)
            chanTypeString += "R10k4w, ";
        if (chanType & AI_CHAN_TYPE_RESISTANCE_1K4W)
            chanTypeString += "R1k4w, ";
        if (chanType & AI_CHAN_TYPE_RESISTANCE_10K2W)
            chanTypeString += "R10k2w, ";
        if (chanType & AI_CHAN_TYPE_RESISTANCE_1K2W)
            chanTypeString += "R1k2w, ";
        if (chanType & AI_CHAN_TYPE_TC)
            chanTypeString += "TC, ";
        if (chanType & AI_CHAN_TYPE_RTD_1000OHM_4W)
            chanTypeString += "RTD1k4w, ";
        if (chanType & AI_CHAN_TYPE_RTD_100OHM_4W)
            chanTypeString += "RTD1004w, ";
        if (chanType & AI_CHAN_TYPE_RTD_1000OHM_3W)
            chanTypeString += "RTD1k3w, ";
        if (chanType & AI_CHAN_TYPE_RTD_100OHM_3W)
            chanTypeString += "RTD1003w, ";
        if (chanType & AI_CHAN_TYPE_QUART_BRIDGE_350OHM)
            chanTypeString += "BridgeQ350, ";
        if (chanType & AI_CHAN_TYPE_QUART_BRIDGE_120OHM)
            chanTypeString += "BridgeQ120, ";
        if (chanType & AI_CHAN_TYPE_HALF_BRIDGE)
            chanTypeString += "BridgeHalf, ";
        if (chanType & AI_CHAN_TYPE_FULL_BRIDGE_62PT5mVV)
            chanTypeString += "BridgeF62mVV, ";
        if (chanType & AI_CHAN_TYPE_FULL_BRIDGE_7PT8mVV)
            chanTypeString += "BridgeF7p8mVV, ";
        if (chanTypeString.length())
            return chanTypeString.left(chanTypeString.length() - 2);
        return "Invalid Type";
    }
}

QString LibUtilities::getAiInputModeName(int inMode)
{
    switch (inMode) {
    case DIFFERENTIAL:
        return "Diff";
    case SINGLE_ENDED:
        return "SE";
    case GROUNDED:
        return "GND";
    default:
        return "Invalid mode";
    }
}

QString LibUtilities::getAiCalTableTypeName(int tableType)
{
    //used for table type return, not index
    switch (tableType) {
    case 0:
        return "Factory";
    case 1:
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
    case 60:
        return "60Hz Rejection";
    case 50:
        return "50Hz Rejection";
    default:
        return "";
    }
}

QString LibUtilities::getAoSyncModeName(int syncMode)
{
    switch (syncMode) {
    case 1:
        return "Slave";
    case 0:
        return "Master";
    default:
        return "Invalid";
    }
}

QString LibUtilities::getDaqOChanTypeNames(int typeNum)
{
    switch (typeNum) {
    case ANALOG:
        return "Analog";
    case DIGITAL8:
        return "Digital8";
    case DIGITAL16:
        return "Digital16";
    case DIGITAL:
        return "Digital";
    default:
        return "";
    }
}

QString LibUtilities::getTcTypeName(int tcType)
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
    default:
        return "Invalid Type";
        break;
    }
}

QString LibUtilities::getTempUnitName(int tempUnit)
{
    switch (tempUnit) {
    case CELSIUS:
        return "Celsius";
    case FAHRENHEIT:
        return "Fahrenheit";
    case KELVIN:
        return "Kelvin";
    default:
        return "";
    }
}

QString LibUtilities::getTrigTypeNames(int trigType)
{
    switch (trigType) {
    case TRIG_POS_EDGE:
        return "Positive Edge";
    case TRIG_NEG_EDGE:
        return "Negative Edge";
    case TRIG_HIGH:
        return "TrigHigh";
    case TRIG_LOW:
        return "TrigLow";
    case GATE_HIGH:
        return "GateHigh";
    case GATE_LOW:
        return "GateLow";
    case TRIG_RISING:
        return "TrigRising";
    case TRIG_FALLING:
        return "TrigFalling";
    case TRIGABOVE:
        return "TrigAbove";
    case TRIGBELOW:
        return "TrigBelow";
    case GATE_ABOVE:
        return "GateAbove";
    case GATE_BELOW:
        return "GateBelow";
    case GATE_IN_WINDOW:
        return "GateInWindow";
    case GATE_OUT_WINDOW:
        return "GateOutWindow";
    case TRIG_PATTERN_EQ:
        return "TrigPatternEq";
    case TRIG_PATTERN_NE:
        return "TrigPatternNE";
    case TRIG_PATTERN_ABOVE:
        return "TrigPatternAbove";
    case TRIG_PATTERN_BELOW:
        return "TrigPatternBelow";
    default:
        return "";
    }
}

QString LibUtilities::getQueueTypeNames(int queueTypes)
{
    int mask;
    int maskedVal;
    QString chanName;

    maskedVal = 0;
    for (int i = 0; i < 3; i++) {
        mask = pow(2, i);
        maskedVal = (queueTypes & mask);
        switch (maskedVal) {
        case 1:
            chanName += "ChanQueue, ";
            break;
        case 2:
            chanName += "GainQueue, ";
            break;
        case 4:
            chanName += "ModeQueue, ";
            break;
        default:
            break;
        }
    }
    int loc = chanName.lastIndexOf(",");
    return chanName.left(loc);
}

QString LibUtilities::getQueueLimitNames(int queueLimits)
{
    int mask;
    int maskedVal;
    QString chanName;

    maskedVal = 0;
    for (int i = 0; i < 2; i++) {
        mask = pow(2, i);
        maskedVal = (queueLimits & mask);
        switch (maskedVal) {
        case 1:
            chanName += "Unique, ";
            break;
        case 2:
            chanName += "Ascending, ";
            break;
        default:
            chanName = ", ";
            break;
        }
    }
    int loc = chanName.lastIndexOf(",");
    return chanName.left(loc);
}

QString LibUtilities::getDaqIChanTypeNames(int typeNum)
{
    switch (typeNum) {
    case ANALOG:
        return "Analog";
    case DIGITAL8:
        return "Digital8";
    case DIGITAL16:
        return "Digital16";
    case CTR16:
        return "Counter16";
    case CTR32LOW:
        return "Counter32Low";
    case CTR32HIGH:
        return "Counter32High";
    case CJC:
        return "CJC";
    case TC:
        return "TC";
    case ANALOG_SE:
        return "AnalogSE";
    case ANALOG_DIFF:
        return "AnalogDiff";
    case SETPOINTSTATUS:
        return "SetPointStatus";
    case CTRBANK0:
        return "CtrBank0";
    case CTRBANK1:
        return "CtrBank1";
    case CTRBANK2:
        return "CtrBank2";
    case CTRBANK3:
        return "CtrBank3";
    case PADZERO:
        return "PadZero";
    case DIGITAL:
        return "Digital";
    case CTR:
        return "Ctr";
    default:
        return "";
    }
}

QString LibUtilities::getDigitalDirection(int digDir)
{
    switch (digDir) {
    case DIGITALIN:
        return "Input";
        break;
    case DIGITALOUT:
        return "Output";
        break;
    default:
        return "InvalidDir";
        break;
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
        return "Invalid Type";
        break;
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
    (void)ioType;
    /*switch (ioType) {
    case DPIOT_IN:
        return "Fixed input";
        break;
    case DPIOT_OUT:
        return "Fixed output";
        break;
    case DPIOT_IO:
        return "IO Port-Config";
        break;
    case DPIOT_BITIO:
        return "IO Bit-Config";
        break;
    case DPIOT_NONCONFIG:
        return "IO Non-Config";
        break;
    default:
        return "Invalid Type";
        break;
    }
        */
    return "";
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
    (void)typeNum;
    return "";
}

QString LibUtilities::getCtrRegTypeNames(int regType)
{
    (void)regType;
    return "";
}

QString LibUtilities::getCtrMeasModeNames(int modeNum)
{
    (void)modeNum;
    return "";
}

QString LibUtilities::getTmrTypeName(int tmrType)
{
    (void)tmrType;
    return "";
}

QString LibUtilities::getEventNames(int eventMask)
{
    QString eventString;

    if (eventMask == 0)
        return "No Events";
    else {
        if (eventMask & ON_DATA_AVAILABLE)
            eventString = "OnDataAvailable, ";
        if (eventMask & ON_SCAN_ERROR)
            eventString += "OnScanError, ";
        if (eventMask & ON_END_OF_INPUT_SCAN)
            eventString += "OnEndOfInScan, ";
        if (eventMask & ON_END_OF_OUTPUT_SCAN)
            eventString += "OnEndOfOutScan, ";
        if (eventString.length())
            return eventString.left(eventString.length() - 2);
        return "EventType";
    }
}

QString LibUtilities::getRegionNames(int memRegion)
{
    (void)memRegion;
    return "";
}

QString LibUtilities::getEnableDisableName(int value)
{
    switch (value) {
    case 1:
        return "Disabled";
    case 2:
        return "Enabled";
    default:
        return "Invalid Value";
    }
}
