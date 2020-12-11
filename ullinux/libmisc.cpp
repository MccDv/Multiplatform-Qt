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
    UlError err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ulFlashLED";
    argString = "(mDaqDeviceHandle, flashCount)\n";
    argVals = QString("(%1, %2)")
            .arg(deviceHandle)
            .arg(flashCount);
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulFlashLed(deviceHandle, flashCount);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

QString LibMisc::mccGetUlVersion(QString &params)
{
    unsigned int index, maxConfigLen;
    maxConfigLen = 128;
    char configValue[maxConfigLen];
    char *pInfoValue = configValue;
    QString returnStr;
    UlError err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "ulGetInfoStr";
    argString = "(infoType, index, pInfoValue, maxConfigLen)\n";

    index = (uint)0;
    maxConfigLen = 16;
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulGetInfoStr(UL_INFO_VER_STR, index, pInfoValue, &maxConfigLen);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(UL_INFO_VER_STR)
            .arg(index)
            .arg(QString("0x%1").arg((quintptr)pInfoValue,
                                     QT_POINTER_SIZE * 2, 16, QChar('0')))
            .arg(maxConfigLen);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    if(err != 0)
        returnStr = "UL version unavailable";
    else
        returnStr = QString::fromLocal8Bit(pInfoValue, (int)maxConfigLen -1);
    return returnStr;
}

QString LibMisc::mccGetUlErrorText(int errValue)
{
    QString errText;
    UlError errCode;

    errText = "";
    char errMsg[ERR_MSG_LEN];
    errCode = (UlError)errValue;
    UlError err = ulGetErrMsg(errCode, errMsg);
    if(err == ERR_NO_ERROR)
    {
        errText = QString("[Error %1] %2")
                .arg(errCode)
                .arg(errMsg);
    }
    return errText;
}

QString LibMisc::mccGetErrConstText(int errValue)
{
    switch (errValue) {
    case ERR_UNHANDLED_EXCEPTION:
        return "UNHANDLED_EXCEPTION";
    case ERR_BAD_DEV_HANDLE:
        return "BAD_DEV_HANDLE";
    case ERR_BAD_DEV_TYPE:
        return "BAD_DEV_TYPE";
    case ERR_USB_DEV_NO_PERMISSION:
        return "DEV_NO_PERMISSION";
    case ERR_USB_INTERFACE_CLAIMED:
        return "USB_INTERFACE_CLAIMED";
    case ERR_DEV_NOT_FOUND:
        return "DEV_NOT_FOUND";
    case ERR_DEV_NOT_CONNECTED:
        return "DEV_NOT_CONNECTED";
    case ERR_DEAD_DEV:
        return "DEAD_DEV";
    case ERR_BAD_BUFFER_SIZE:
        return "BAD_BUFFER_SIZE";
    case ERR_BAD_BUFFER:
        return "BAD_BUFFER";
    case ERR_BAD_MEM_TYPE:
        return "BAD_MEM_TYPE";
    case ERR_BAD_MEM_REGION:
        return "BAD_MEM_REGION";
    case ERR_BAD_RANGE:
        return "BAD_RANGE";
    case ERR_BAD_AI_CHAN:
        return "BAD_AI_CHAN";
    case ERR_BAD_INPUT_MODE:
        return "BAD_INPUT_MODE";
    case ERR_ALREADY_ACTIVE:
        return "ALREADY_ACTIVE";
    case ERR_BAD_TRIG_TYPE:
        return "BAD_TRIG_TYPE";
    case ERR_OVERRUN:
        return "OVERRUN";
    case ERR_UNDERRUN:
        return "UNDERRUN";
    case ERR_TIMEDOUT:
        return "TIMEDOUT";
    case ERR_BAD_OPTION:
        return "BAD_OPTION";
    case ERR_BAD_RATE:
        return "BAD_RATE";
    case ERR_BAD_BURSTIO_COUNT:
        return "BAD_BURSTIO_COUNT";
    case ERR_CONFIG_NOT_SUPPORTED:
        return "CONFIG_NOT_SUPPORTED";
    case ERR_BAD_CONFIG_VAL:
        return "BAD_CONFIG_VAL";
    case ERR_BAD_AI_CHAN_TYPE:
        return "BAD_AI_CHAN_TYPE";
    case ERR_ADC_OVERRUN:
        return "ADC_OVERRUN";
    case ERR_BAD_TC_TYPE:
        return "BAD_TC_TYPE";
    case ERR_BAD_UNIT:
        return "BAD_UNIT";
    case ERR_BAD_QUEUE_SIZE:
        return "BAD_QUEUE_SIZE";
    case ERR_BAD_CONFIG_ITEM:
        return "BAD_CONFIG_ITEM";
    case ERR_BAD_INFO_ITEM:
        return "BAD_INFO_ITEM";
    case ERR_BAD_FLAG:
        return "BAD_FLAG";
    case ERR_BAD_SAMPLE_COUNT:
        return "BAD_SAMPLE_COUNT";
    case ERR_INTERNAL:
        return "INTERNAL";
    case ERR_BAD_COUPLING_MODE:
        return "BAD_COUPLING_MODE";
    case ERR_BAD_SENSOR_SENSITIVITY:
        return "BAD_SENSOR_SENSITIVITY";
    case ERR_BAD_IEPE_MODE:
        return "BAD_IEPE_MODE";
    case ERR_BAD_AI_CHAN_QUEUE:
        return "BAD_AI_CHAN_QUEUE";
    case ERR_BAD_AI_GAIN_QUEUE:
        return "BAD_AI_GAIN_QUEUE";
    case ERR_BAD_AI_MODE_QUEUE:
        return "BAD_AI_MODE_QUEUE";
    case ERR_FPGA_FILE_NOT_FOUND:
        return "FPGA_FILE_NOT_FOUND";
    case ERR_UNABLE_TO_READ_FPGA_FILE:
        return "UNABLE_TO_READ_FPGA_FILE";
    case ERR_NO_FPGA:
        return "NO_FPGA";
    case ERR_BAD_ARG:
        return "BAD_ARG";
    case ERR_MIN_SLOPE_VAL_REACHED:
        return "MIN_SLOPE_VAL_REACHED";
    case ERR_MAX_SLOPE_VAL_REACHED:
        return "MAX_SLOPE_VAL_REACHED";
    case ERR_MIN_OFFSET_VAL_REACHED:
        return "MIN_OFFSET_VAL_REACHED";
    case ERR_MAX_OFFSET_VAL_REACHED:
        return "MAX_OFFSET_VAL_REACHED";
    case ERR_BAD_PORT_TYPE:
        return "BAD_PORT_TYPE";
    case ERR_WRONG_DIG_CONFIG:
        return "WRONG_DIG_CONFIG";
    case ERR_BAD_BIT_NUM:
        return "BAD_BIT_NUM";
    case ERR_BAD_PORT_VAL:
        return "BAD_PORT_VAL";
    case ERR_BAD_RETRIG_COUNT:
        return "BAD_RETRIG_COUNT";
    case ERR_BAD_AO_CHAN:
        return "BAD_AO_CHAN";
    case ERR_BAD_DA_VAL:
        return "BAD_DA_VAL";
    case ERR_BAD_TMR:
        return "BAD_TMR";
    case ERR_BAD_FREQUENCY:
        return "BAD_FREQUENCY";
    case ERR_BAD_DUTY_CYCLE:
        return "BAD_DUTY_CYCLE";
    case ERR_BAD_INITIAL_DELAY:
        return "BAD_INITIAL_DELAY";
    case ERR_BAD_CTR:
        return "BAD_CTR";
    case ERR_BAD_CTR_VAL:
        return "BAD_CTR_VAL";
    case ERR_BAD_DAQI_CHAN_TYPE:
        return "BAD_DAQI_CHAN_TYPE";
    case ERR_BAD_NUM_CHANS:
        return "BAD_NUM_CHANS";
    case ERR_BAD_CTR_REG:
        return "BAD_CTR_REG";
    case ERR_BAD_CTR_MEASURE_TYPE:
        return "BAD_CTR_MEASURE_TYPE";
    case ERR_BAD_CTR_MEASURE_MODE:
        return "BAD_CTR_MEASURE_MODE";
    case ERR_BAD_DEBOUNCE_TIME:
        return "BAD_DEBOUNCE_TIME";
    case ERR_BAD_DEBOUNCE_MODE:
        return "BAD_DEBOUNCE_MODE";
    case ERR_BAD_EDGE_DETECTION:
        return "BAD_EDGE_DETECTION";
    case ERR_BAD_TICK_SIZE:
        return "BAD_TICK_SIZE";
    case ERR_BAD_DAQO_CHAN_TYPE:
        return "BAD_DAQO_CHAN_TYPE";
    case ERR_NO_CONNECTION_ESTABLISHED:
        return "NO_CONNECTION_ESTABLISHED";
    case ERR_BAD_EVENT_TYPE:
        return "BAD_EVENT_TYPE";
    case ERR_EVENT_ALREADY_ENABLED:
        return "EVENT_ALREADY_ENABLED";
    case ERR_BAD_EVENT_PARAMETER:
        return "BAD_EVENT_PARAMETER";
    case ERR_BAD_CALLBACK_FUCNTION:
        return "BAD_CALLBACK_FUCNTION";
    case ERR_BAD_MEM_ADDRESS:
        return "BAD_MEM_ADDRESS";
    case ERR_MEM_ACCESS_DENIED:
        return "MEM_ACCESS_DENIED";
    case ERR_DEV_UNAVAILABLE:
        return "DEV_UNAVAILABLE";
    case ERR_BAD_RETRIG_TRIG_TYPE:
        return "BAD_RETRIG_TRIG_TYPE";
    case ERR_BAD_DEV_VER:
        return "BAD_DEV_VER";
    case ERR_BAD_DIG_OPERATION:
        return "BAD_DIG_OPERATION";
    case ERR_BAD_PORT_INDEX:
        return "BAD_PORT_INDEX";
    case ERR_OPEN_CONNECTION:
        return "OPEN_CONNECTION";
    case ERR_DEV_NOT_READY:
        return "DEV_NOT_READY";
    case ERR_PACER_OVERRUN:
        return "PACER_OVERRUN";
    case ERR_BAD_TRIG_CHANNEL:
        return "BAD_TRIG_CHANNEL";
    case ERR_BAD_TRIG_LEVEL:
        return "BAD_TRIG_LEVEL";
    case ERR_BAD_CHAN_ORDER:
        return "BAD_CHAN_ORDER";
    case ERR_TEMP_OUT_OF_RANGE:
        return "TEMP_OUT_OF_RANGE";
    case ERR_TRIG_THRESHOLD_OUT_OF_RANGE:
        return "TRIG_THRESHOLD_OUT_OF_RANGE";
    case ERR_INCOMPATIBLE_FIRMWARE:
        return "INCOMPATIBLE_FIRMWARE";
    case ERR_BAD_NET_IFC:
        return "BAD_NET_IFC";
    case ERR_BAD_NET_HOST:
        return "BAD_NET_HOST";
    case ERR_BAD_NET_PORT:
        return "BAD_NET_PORT";
    case ERR_NET_IFC_UNAVAILABLE:
        return "NET_IFC_UNAVAILABLE";
    case ERR_NET_CONNECTION_FAILED:
        return "NET_CONNECTION_FAILED";
    case ERR_BAD_CONNECTION_CODE:
        return "BAD_CONNECTION_CODE";
    case ERR_CONNECTION_CODE_IGNORED:
        return "CONNECTION_CODE_IGNORED";
    case ERR_NET_DEV_IN_USE:
        return "NET_DEV_IN_USE";
    case ERR_BAD_NET_FRAME:
        return "BAD_NET_FRAME";
    case ERR_NET_TIMEOUT:
        return "NET_TIMEOUT";
    case ERR_DATA_SOCKET_CONNECTION_FAILED:
        return "DATA_SOCKET_CONNECTION_FAILED";
    case ERR_PORT_USED_FOR_ALARM:
        return "PORT_USED_FOR_ALARM";
    case ERR_BIT_USED_FOR_ALARM:
        return "BIT_USED_FOR_ALARM";
    case ERR_CMR_EXCEEDED:
        return "CMR_EXCEEDED";
    case ERR_NET_BUFFER_OVERRUN:
        return "NET_BUFFER_OVERRUN";
    case ERR_BAD_NET_BUFFER:
        return "BAD_NET_BUFFER";
    default:
        return "";
    }
}

int LibMisc::mccGetInfoStr(QString &params, int infoItem, unsigned int index,
                               char *infoValue, unsigned int &maxLen)
{
    int err;
    QString funcName, argString, argVals;
    UlInfoItemStr ulInfoItem;
    QTime t;
    QString sStartTime;

    ulInfoItem = (UlInfoItemStr)infoItem;
    funcName = "ulGetInfoStr";
    argString = "(infoType, index, infoValue, length)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulGetInfoStr(ulInfoItem, index, infoValue, &maxLen);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(infoItem)
            .arg(index)
            .arg(infoValue)
            .arg(maxLen);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccGetConfig(QString &params, int configItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    UlConfigItem ulConfigItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    ulConfigItem = (UlConfigItem)configItem;
    funcName = "ulGetConfig";
    argString = "(ulConfigItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulGetConfig(ulConfigItem, index, &infoValue);
    argVals = QString("(%1, %2, %3)")
            .arg(ulConfigItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
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
    QString funcName, argString, argVals;
    UlConfigItem ulConfigItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    ulConfigItem = (UlConfigItem)configItem;
    funcName = "ulSetConfig";
    argString = "(ulConfigItem, index, configValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulSetConfig(ulConfigItem, index, infoValue);
    argVals = QString("(%1, %2, %3)")
            .arg(ulConfigItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDevGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    DevInfoItem devInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    devInfoItem = (DevInfoItem)infoItem;
    funcName = "ulDevGetInfo";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDevGetInfo(deviceHandle, devInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(devInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDevGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    DevConfigItem devConfigItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    devConfigItem = (DevConfigItem)configItem;
    funcName = "ulDevGetConfig";
    argString = "(deviceHandle, devConfigItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDevGetConfig(deviceHandle, devConfigItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(devConfigItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDevGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                            int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen)
{
    int err;
    QString funcName, argString, argVals;
    DevConfigItemStr devCfgItem;
    QTime t;
    QString sStartTime;

    devCfgItem = (DevConfigItemStr)configItem;
    funcName = "ulDevGetConfigStr";
    argString = "(deviceHandle, devCfgItem, index, configValue, length)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDevGetConfigStr(deviceHandle, devCfgItem, index, configValue, &maxConfigLen);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(devCfgItem)
            .arg(index)
            .arg(configValue)
            .arg(maxConfigLen);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDevSetConfig(QString &params, DaqDeviceHandle deviceHandle,
                                 int configItem, unsigned int index, long long configValue)
{
    int err;
    QString funcName, argString, argVals;
    DevConfigItem devConfigItem;
    QTime t;
    QString sStartTime;

    devConfigItem = (DevConfigItem)configItem;
    funcName = "ulDevSetConfig";
    argString = "(deviceHandle, devConfigItem, index, configValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDevSetConfig(deviceHandle, devConfigItem, index, configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(devConfigItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
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
    QString funcName, argString, argVals;
    AiInfoItem devInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    devInfoItem = (AiInfoItem)infoItem;
    funcName = "ulDevGetInfo";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAIGetInfo(deviceHandle, devInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(devInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccAiGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, double &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    AiInfoItemDbl aiInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    aiInfoItem = (AiInfoItemDbl)infoItem;
    funcName = "ulDevGetInfo";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAIGetInfoDbl(deviceHandle, aiInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(aiInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccAiGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long &configValue)
{
    int err;
    QString funcName, argString, argVals;
    AiConfigItem aiConfigItem;
    QTime t;
    QString sStartTime;

    configValue = 0;
    aiConfigItem = (AiConfigItem)configItem;
    funcName = "ulAIGetConfig";
    argString = "(deviceHandle, aiConfigItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAIGetConfig(deviceHandle, aiConfigItem, index, &configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(aiConfigItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccAiGetCfgDbl(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, double &configValue)
{
    int err;
    QString funcName, argString, argVals;
    AiConfigItemDbl aiConfigItem;
    QTime t;
    QString sStartTime;

    configValue = 0;
    aiConfigItem = (AiConfigItemDbl)configItem;
    funcName = "ulAIGetConfigDbl";
    argString = "(deviceHandle, configItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAIGetConfigDbl(deviceHandle, aiConfigItem, index, &configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(aiConfigItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;

}

int LibMisc::mccAiGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen)
{
    int err;
    QString funcName, argString, argVals;
    AiConfigItemStr aiConfigItem;
    QTime t;
    QString sStartTime;

    aiConfigItem = (AiConfigItemStr)configItem;
    funcName = "ulAIGetConfigStr";
    argString = "(deviceHandle, aiConfigItem, index, configValue, length)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAIGetConfigStr(deviceHandle, aiConfigItem, index, configValue, &maxConfigLen);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(aiConfigItem)
            .arg(index)
            .arg(configValue)
            .arg(maxConfigLen);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccAiSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long configValue)
{
    int err;
    QString funcName, argString, argVals;
    AiConfigItem aiConfigItem;
    QTime t;
    QString sStartTime;

    aiConfigItem = (AiConfigItem)configItem;
    funcName = "ulAISetConfig";
    argString = "(deviceHandle, aiConfigItem, index, configValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAISetConfig(deviceHandle, aiConfigItem, index, configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(aiConfigItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccAoGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                              int infoItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    AoInfoItem aoInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    aoInfoItem = (AoInfoItem)infoItem;
    funcName = "ulAOGetInfo";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAOGetInfo(deviceHandle, aoInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(aoInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccAoGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, double &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    AoInfoItemDbl aoInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    aoInfoItem = (AoInfoItemDbl)infoItem;
    funcName = "ulAOGetInfoDbl";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAOGetInfoDbl(deviceHandle, aoInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(aoInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccAoGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long &configValue)
{
    int err;
    QString funcName, argString, argVals;
    AoConfigItem aoConfigItem;
    QTime t;
    QString sStartTime;

    configValue = 0;
    aoConfigItem = (AoConfigItem)configItem;
    funcName = "ulAOGetConfig";
    argString = "(deviceHandle, configItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAOGetConfig(deviceHandle, aoConfigItem, index, &configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(aoConfigItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccAoSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                             int configItem, unsigned int index, long long configValue)
{
    int err;
    AoConfigItem cfgItem;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    cfgItem = (AoConfigItem)configItem;
    funcName = "ulAOSetConfig";
    argString = "(deviceHandle, configItem, index, configValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulAOSetConfig(deviceHandle, cfgItem, index, configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(cfgItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDioGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    DioInfoItem dioInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    dioInfoItem = (DioInfoItem)infoItem;
    funcName = "ulDIOGetInfo";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDIOGetInfo(deviceHandle, dioInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(dioInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDioGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, double &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    DioInfoItemDbl dioInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    dioInfoItem = (DioInfoItemDbl)infoItem;
    funcName = "ulDIOGetInfoDbl";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDIOGetInfoDbl(deviceHandle, dioInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(dioInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDioGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long &configValue)
{
    int err;
    QString funcName, argString, argVals;
    DioConfigItem dioConfigItem;
    QTime t;
    QString sStartTime;

    configValue = 0;
    dioConfigItem = (DioConfigItem)configItem;
    funcName = "ulDIOGetConfig";
    argString = "(deviceHandle, configItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDIOGetConfig(deviceHandle, dioConfigItem, index, &configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(dioConfigItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDioSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long configValue)
{
    int err;
    QString funcName, argString, argVals;
    DioConfigItem cfgItem;
    QTime t;
    QString sStartTime;

    funcName = "ulDIOGetConfig";
    argString = "(deviceHandle, configItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    cfgItem = (DioConfigItem)configItem;
    err = ulDIOSetConfig(deviceHandle, cfgItem, index, configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(cfgItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccCtrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    CtrInfoItem ctrInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    ctrInfoItem = (CtrInfoItem)infoItem;
    funcName = "ulCtrGetInfo";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulCtrGetInfo(deviceHandle, ctrInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(ctrInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccCtrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, double &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    CtrInfoItemDbl ctrInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    ctrInfoItem = (CtrInfoItemDbl)infoItem;
    funcName = "ulCtrGetInfoDbl";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulCtrGetInfoDbl(deviceHandle, ctrInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(ctrInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccCtrGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long &configValue)
{
    int err;
    QString funcName, argString, argVals;
    CtrConfigItem ctrConfigItem;
    QTime t;
    QString sStartTime;

    configValue = 0;
    ctrConfigItem = (CtrConfigItem)configItem;
    funcName = "ulCtrGetConfig";
    argString = "(deviceHandle, configItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulCtrGetConfig(deviceHandle, ctrConfigItem, index, &configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(ctrConfigItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccCtrSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                              int configItem, unsigned int index, long long configValue)
{
    int err;
    QString funcName, argString, argVals;
    CtrConfigItem cfgItem;
    QTime t;
    QString sStartTime;

    cfgItem = (CtrConfigItem)configItem;
    funcName = "ulCtrSetConfig";
    argString = "(deviceHandle, configItem, index, configValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulCtrSetConfig(deviceHandle, cfgItem, index, configValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(cfgItem)
            .arg(index)
            .arg(configValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccTmrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                               int infoItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    TmrInfoItem tmrInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    tmrInfoItem = (TmrInfoItem)infoItem;
    funcName = "ulTmrGetInfo";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulTmrGetInfo(deviceHandle, tmrInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(tmrInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccTmrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, double &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    TmrInfoItemDbl tmrInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    tmrInfoItem = (TmrInfoItemDbl)infoItem;
    funcName = "ulTmrGetInfoDbl";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulTmrGetInfoDbl(deviceHandle, tmrInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(tmrInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDaqInGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    DaqIInfoItem daqIInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    daqIInfoItem = (DaqIInfoItem)infoItem;
    funcName = "ulDaqIGetInfo";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDaqIGetInfo(deviceHandle, daqIInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(daqIInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDaqInGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                    int infoItem, unsigned int index, double &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    DaqIInfoItemDbl daqIInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    daqIInfoItem = (DaqIInfoItemDbl)infoItem;
    funcName = "ulDaqIGetInfoDbl";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDaqIGetInfoDbl(deviceHandle, daqIInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(daqIInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDaqOutGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                  int infoItem, unsigned int index, long long &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    DaqOInfoItem daqOInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    daqOInfoItem = (DaqOInfoItem)infoItem;
    funcName = "ulDaqOGetInfo";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDaqOGetInfo(deviceHandle, daqOInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(daqOInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccDaqOutGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                     int infoItem, unsigned int index, double &infoValue)
{
    int err;
    QString funcName, argString, argVals;
    DaqOInfoItemDbl daqOInfoItem;
    QTime t;
    QString sStartTime;

    infoValue = 0;
    daqOInfoItem = (DaqOInfoItemDbl)infoItem;
    funcName = "ulDaqOGetInfoDbl";
    argString = "(deviceHandle, infoItem, index, infoValue)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = ulDaqOGetInfoDbl(deviceHandle, daqOInfoItem, index, &infoValue);
    argVals = QString("(%1, %2, %3, %4)")
            .arg(deviceHandle)
            .arg(daqOInfoItem)
            .arg(index)
            .arg(infoValue);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

/*  Map parameters start with #:#:. The first number indicates index applies
 *  (0 = no index, 1 = index is used), the second number indicates
 *  which function to call (0 = standard, 1 = string, 2 = double.           */

QMap<int, QString> LibMisc::mccGetUlInfoItems()
{
    QMap<int, QString> ulInfoItems;

    ulInfoItems.insert(UL_INFO_VER_STR, "0:1:UL Version");
    return ulInfoItems;
}

QMap<int, QString> LibMisc::mccGetUlCfgItems()
{
    QMap<int, QString> ulConfigItems;

    ulConfigItems.insert(UL_CFG_USB_XFER_PRIORITY, "0:0:USB XFer Priority");
    return ulConfigItems;
}

QMap<int, QString> LibMisc::mccGetDevInfoItems()
{
    QMap<int, QString> devInfoItems;

    devInfoItems.insert(DEV_INFO_HAS_AI_DEV, "0:0:Has AD Dev");
    devInfoItems.insert(DEV_INFO_HAS_AO_DEV, "0:0:Has DA Dev");
    devInfoItems.insert(DEV_INFO_HAS_DIO_DEV, "0:0:Has DIO Dev");
    devInfoItems.insert(DEV_INFO_HAS_CTR_DEV, "0:0:Has CTR Dev");
    devInfoItems.insert(DEV_INFO_HAS_TMR_DEV, "0:0:Has TMR Dev");
    devInfoItems.insert(DEV_INFO_HAS_DAQI_DEV, "0:0:Has DAQI Dev");
    devInfoItems.insert(DEV_INFO_HAS_DAQO_DEV, "0:0:Has DAQO Dev");
    devInfoItems.insert(DEV_INFO_DAQ_EVENT_TYPES, "0:0:Has Events");
    devInfoItems.insert(DEV_INFO_MEM_REGIONS, "0:0:Has MEM Regions");
    return devInfoItems;
}

QMap<int, QString> LibMisc::mccGetDevCfgItems()
{
    QMap<int, QString> devConfigItems;

    devConfigItems.insert(DEV_CFG_VER_STR, "1:1:Device Version");
    devConfigItems.insert(DEV_CFG_CONNECTION_CODE, "0:0:Connect Code");
    devConfigItems.insert(DEV_CFG_HAS_EXP, "0:0:Exp Attached");
    devConfigItems.insert(DEV_CFG_IP_ADDR_STR, "0:1:IP Address");
    devConfigItems.insert(DEV_CFG_NET_IFC_STR, "0:1:Net Interface");
    devConfigItems.insert(DEV_CFG_MEM_UNLOCK_CODE, "0:0:Mem Unlock Code");
    devConfigItems.insert(DEV_CFG_RESET, "0:0:Reset");
    return devConfigItems;
}

QMap<int, QString> LibMisc::mccGetAiInfoItems()
{
    QMap<int, QString> aiInfoItems;

    aiInfoItems.insert(AI_INFO_MIN_SCAN_RATE, "0:2:Min Rate");
    aiInfoItems.insert(AI_INFO_MAX_SCAN_RATE, "0:2:Max Rate");
    aiInfoItems.insert(AI_INFO_MAX_THROUGHPUT, "0:2:Max Throughput");
    aiInfoItems.insert(AI_INFO_MAX_BURST_RATE, "0:2:Max BurstRate");
    aiInfoItems.insert(AI_INFO_MAX_BURST_THROUGHPUT, "0:2:Burst Throughput");
    aiInfoItems.insert(AI_INFO_RESOLUTION, "0:0:Resolution");
    aiInfoItems.insert(AI_INFO_NUM_CHANS, "0:0:Num Chans");
    aiInfoItems.insert(AI_INFO_NUM_CHANS_BY_MODE, "1:0:Chans by Mode");
    aiInfoItems.insert(AI_INFO_NUM_CHANS_BY_TYPE, "1:0:Chans by Type");
    aiInfoItems.insert(AI_INFO_CHAN_TYPES, "0:0:Chan Types");
    aiInfoItems.insert(AI_INFO_SCAN_OPTIONS, "0:0:Scan Options");
    aiInfoItems.insert(AI_INFO_HAS_PACER, "0:0:Has Pacer");
    aiInfoItems.insert(AI_INFO_NUM_DIFF_RANGES, "0:0:Num DiffRanges");
    aiInfoItems.insert(AI_INFO_NUM_SE_RANGES, "0:0:Num SERanges");
    aiInfoItems.insert(AI_INFO_DIFF_RANGE, "1:0:Diff Range");
    aiInfoItems.insert(AI_INFO_SE_RANGE, "1:0:SE Range");
    aiInfoItems.insert(AI_INFO_TRIG_TYPES, "0:0:Trig Types");
    aiInfoItems.insert(AI_INFO_MAX_QUEUE_LENGTH_BY_MODE, "1:0:Queue Length");
    aiInfoItems.insert(AI_INFO_QUEUE_TYPES, "0:0:Queue Types");
    aiInfoItems.insert(AI_INFO_QUEUE_LIMITS, "0:0:Queue Limits");
    aiInfoItems.insert(AI_INFO_FIFO_SIZE, "0:0:Fifo Size");
    aiInfoItems.insert(AI_INFO_IEPE_SUPPORTED, "0:0:IEPE Support");
    return aiInfoItems;
}

QMap<int, QString> LibMisc::mccGetAiCfgItems()
{
    QMap<int, QString> aiCfgItems;

    aiCfgItems.insert(AI_CFG_CHAN_TYPE, "1:0:Chan Type");
    aiCfgItems.insert(AI_CFG_CHAN_TC_TYPE, "1:0:Chan TC Type");
    aiCfgItems.insert(AI_CFG_SCAN_TEMP_UNIT, "0:0:Temp Unit");
    aiCfgItems.insert(AI_CFG_SCAN_CHAN_TEMP_UNIT, "1:0:Chan Unit");
    aiCfgItems.insert(AI_CFG_ADC_TIMING_MODE, "0:0:Timing Mode");
    aiCfgItems.insert(AI_CFG_AUTO_ZERO_MODE, "0:0:Auto Zero");
    aiCfgItems.insert(AI_CFG_CAL_DATE, "1:0:Cal Date");
    aiCfgItems.insert(AI_CFG_CAL_DATE_STR, "1:1:Cal String");
    aiCfgItems.insert(AI_CFG_CHAN_IEPE_MODE, "1:0:Chan IEPE");
    aiCfgItems.insert(AI_CFG_CHAN_COUPLING_MODE, "1:0:Chan Coupling");
    aiCfgItems.insert(AI_CFG_CHAN_SENSOR_CONNECTION_TYPE, "1:0:Chan Sensor");
    aiCfgItems.insert(AI_CFG_OTD_MODE, "0:0:OTD Mode");
    aiCfgItems.insert(AI_CFG_CHAN_OTD_MODE, "1:0:Chan OTD");
    aiCfgItems.insert(AI_CFG_CAL_TABLE_TYPE, "1:0:Cal Table");
    aiCfgItems.insert(AI_CFG_REJECT_FREQ_TYPE, "0:0:Reject Freq");
    aiCfgItems.insert(AI_CFG_CHAN_SLOPE, "1:2:Chan Slope");
    aiCfgItems.insert(AI_CFG_CHAN_OFFSET, "1:2:Chan Offset");
    aiCfgItems.insert(AI_CFG_CHAN_SENSOR_SENSITIVITY, "1:2:Chan Sensitivity");
    aiCfgItems.insert(AI_CFG_CHAN_DATA_RATE, "1:2:Chan Data Rate");
    aiCfgItems.insert(AI_CFG_CHAN_COEFS_STR, "1:1:Chan Coeffs");
    aiCfgItems.insert(AI_CFG_EXP_CAL_DATE, "1:0:Exp Cal Date");
    aiCfgItems.insert(AI_CFG_EXP_CAL_DATE_STR, "1:1:Exp Cal String");
    return aiCfgItems;
}

QMap<int, QString> LibMisc::mccGetAoInfoItems()
{
    QMap<int, QString> aoInfoItems;

    aoInfoItems.insert(AO_INFO_RANGE, "0:0:Range");
    aoInfoItems.insert(AO_INFO_FIFO_SIZE, "0:0:FIFOSize");
    aoInfoItems.insert(AO_INFO_HAS_PACER, "0:0:HasPacer");
    aoInfoItems.insert(AO_INFO_NUM_CHANS, "0:0:NumChans");
    aoInfoItems.insert(AO_INFO_NUM_RANGES, "0:0:NumRanges");
    aoInfoItems.insert(AO_INFO_RESOLUTION, "0:0:Resolution");
    aoInfoItems.insert(AO_INFO_TRIG_TYPES, "0:0:TrigTypes");
    aoInfoItems.insert(AO_INFO_SCAN_OPTIONS, "0:0:ScanOptions");
    aoInfoItems.insert(AO_INFO_MAX_SCAN_RATE, "0:2:MaxRate");
    aoInfoItems.insert(AO_INFO_MIN_SCAN_RATE, "0:2:MinRate");
    aoInfoItems.insert(AO_INFO_MAX_THROUGHPUT, "0:2:MaxThroughput");
    return aoInfoItems;
}

QMap<int, QString> LibMisc::mccGetAoCfgItems()
{
    QMap<int, QString> aoConfigItems;

    aoConfigItems.insert(AO_CFG_SYNC_MODE, "0:0:SyncMode");
    aoConfigItems.insert(AO_CFG_CHAN_SENSE_MODE, "1:0:ChanSenseMode");
    return aoConfigItems;
}

QMap<int, QString> LibMisc::mccGetDioInfoItems()
{
    QMap<int, QString> dioInfoItems;

    dioInfoItems.insert(DIO_INFO_NUM_BITS, "1:0:NumBits");
    dioInfoItems.insert(DIO_INFO_FIFO_SIZE, "0:0:FIFOSize");
    dioInfoItems.insert(DIO_INFO_HAS_PACER, "0:0:HasPacer");
    dioInfoItems.insert(DIO_INFO_NUM_PORTS, "0:0:NumPorts");
    dioInfoItems.insert(DIO_INFO_PORT_TYPE, "1:0:PortType");
    dioInfoItems.insert(DIO_INFO_TRIG_TYPES, "1:0:TrigTypes");
    dioInfoItems.insert(DIO_INFO_PORT_IO_TYPE, "1:0:PortIOType");
    dioInfoItems.insert(DIO_INFO_SCAN_OPTIONS, "0:0:ScanOptions");
    dioInfoItems.insert(DIO_INFO_MIN_SCAN_RATE, "0:2:MinRate");
    dioInfoItems.insert(DIO_INFO_MAX_SCAN_RATE, "0:2:MaxRate");
    dioInfoItems.insert(DIO_INFO_MAX_THROUGHPUT, "0:2:Throughput");
    return dioInfoItems;
}

QMap<int, QString> LibMisc::mccGetDioCfgItems()
{
    QMap<int, QString> dioConfigItems;

    dioConfigItems.insert(DIO_CFG_PORT_DIRECTION_MASK, "1:0:PortDirMask");
    dioConfigItems.insert(DIO_CFG_PORT_INITIAL_OUTPUT_VAL, "1:0:PortInitOutVal");
    dioConfigItems.insert(DIO_CFG_PORT_ISO_FILTER_MASK, "1:0:PortFilterMask");
    dioConfigItems.insert(DIO_CFG_PORT_LOGIC, "1:0:PortLogic");
    return dioConfigItems;
}

QMap<int, QString> LibMisc::mccGetCtrInfoItems()
{
    QMap<int, QString> ctrInfoItems;
    ctrInfoItems.insert(CTR_INFO_NUM_CTRS, "0:0:NumCtrs");
    ctrInfoItems.insert(CTR_INFO_FIFO_SIZE, "0:0:FIFOSize");
    ctrInfoItems.insert(CTR_INFO_HAS_PACER, "0:0:HasPacer");
    ctrInfoItems.insert(CTR_INFO_RESOLUTION, "0:0:Resolution");
    ctrInfoItems.insert(CTR_INFO_TRIG_TYPES, "0:0:TrigTypes");
    ctrInfoItems.insert(CTR_INFO_SCAN_OPTIONS, "0:0:ScanOptions");
    ctrInfoItems.insert(CTR_INFO_MAX_SCAN_RATE, "0:2:MaxRate");
    ctrInfoItems.insert(CTR_INFO_MIN_SCAN_RATE, "0:2:MinRate");
    ctrInfoItems.insert(CTR_INFO_MAX_THROUGHPUT, "0:2:MaxThroughput");
    ctrInfoItems.insert(CTR_INFO_REGISTER_TYPES, "0:0:RegisterTypes");
    ctrInfoItems.insert(CTR_INFO_MEASUREMENT_MODES, "1:0:MeasureModes");
    ctrInfoItems.insert(CTR_INFO_MEASUREMENT_TYPES, "1:0:MeasureTypes");
    return ctrInfoItems;
}

QMap<int, QString> LibMisc::mccGetCtrCfgItems()
{
    QMap<int, QString> ctrConfigItems;
    ctrConfigItems.insert(CTR_CFG_REG, "0:0:ConfigRegister");
    return ctrConfigItems;
}

QMap<int, QString> LibMisc::mccGetTmrInfoItems()
{
    QMap<int, QString> tmrInfoItems;
    tmrInfoItems.insert(TMR_INFO_NUM_TMRS, "0:0:NumTmrs");
    tmrInfoItems.insert(TMR_INFO_TYPE, "1:0:TmrType");
    tmrInfoItems.insert(TMR_INFO_MIN_FREQ, "0:2:MinFreq");
    tmrInfoItems.insert(TMR_INFO_MAX_FREQ, "0:2:MaxFreq");
    return tmrInfoItems;
}

QMap<int, QString> LibMisc::mccGetDaqInInfoItems()
{
    QMap<int, QString> daqInInfoItems;

    daqInInfoItems.insert(DAQI_INFO_SCAN_OPTIONS, "0:0:DaqInOptions");
    daqInInfoItems.insert(DAQI_INFO_CHAN_TYPES, "0:0:DaqInChanTypes");
    daqInInfoItems.insert(DAQI_INFO_TRIG_TYPES, "0:0:DaqInTrigTypes");
    daqInInfoItems.insert(DAQI_INFO_FIFO_SIZE, "0:0:DaqInFIFOSize");
    daqInInfoItems.insert(DAQI_INFO_MIN_SCAN_RATE, "0:2:DaqInMinRate");
    daqInInfoItems.insert(DAQI_INFO_MAX_SCAN_RATE, "0:2:DaqInMaxRate");
    daqInInfoItems.insert(DAQI_INFO_MAX_THROUGHPUT, "0:2:DaqInThroughput");
    return daqInInfoItems;
}

QMap<int, QString> LibMisc::mccGetDaqOutInfoItems()
{
    QMap<int, QString> daqOutInfoItems;

    daqOutInfoItems.insert(DAQO_INFO_CHAN_TYPES, "0:0:DaqOutChanTypes");
    daqOutInfoItems.insert(DAQO_INFO_SCAN_OPTIONS, "0:0:DaqOutOptions");
    daqOutInfoItems.insert(DAQO_INFO_TRIG_TYPES, "0:0:DaqOutTrigTypes");
    daqOutInfoItems.insert(DAQO_INFO_FIFO_SIZE, "0:0:DaqOutFIFOSize");
    daqOutInfoItems.insert(DAQO_INFO_MIN_SCAN_RATE, "0:2:DaqInMinRate");
    daqOutInfoItems.insert(DAQO_INFO_MAX_SCAN_RATE, "0:2:DaqInMaxRate");
    daqOutInfoItems.insert(DAQO_INFO_MAX_THROUGHPUT, "0:2:DaqInThroughput");
    return daqOutInfoItems;
}

