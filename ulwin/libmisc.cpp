#include "libmisc.h"
#include "../mvtest.h"

ErrorDialog *miscErrorDialog;

LibMisc::LibMisc()
{
    miscErrorDialog = MvTest::errDialogObj;
}

int LibMisc::mccIgnoreInstacal(QString &params)
{
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbIgnoreInstaCal";
    argString = "()\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbIgnoreInstaCal();
    argVals = QString("");

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

int LibMisc::mccFlashLed(QString &params, DaqDeviceHandle deviceHandle, int flashCount)
{
    int err;
    QString funcName, argString, argVals;
    (void)flashCount;
    QTime t;
    QString sStartTime;

    funcName = "cbFlashLED";
    argString = "(boardNum)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbFlashLED(deviceHandle);
    argVals = QString("(%1) = %2")
            .arg(deviceHandle)
            .arg(err);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}

QString LibMisc::mccGetUlVersion(QString &params)
{
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "mccGetUlVersion";
    argString = "(const CURRENTREVNUM)\n";
    QString returnStr = QString("%1xx").arg(CURRENTREVNUM);
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    argVals = QString("%1").arg(CURRENTREVNUM);

    int err = 0;
    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return returnStr;
}

QString LibMisc::mccGetUlErrorText(int errValue)
{
    char ErrMessage[ERRSTRLEN];

    cbGetErrMsg(errValue, ErrMessage);
    return ErrMessage;
}

QString LibMisc::mccGetErrConstText(int errValue)
{
    switch (errValue) {
    case BADBOARD:
        return "BADBOARD";
    case DEADDIGITALDEV:
        return "DEADDIGITALDEV";
    case DEADCOUNTERDEV:
        return "DEADCOUNTERDEV";
    case DEADDADEV:
        return "DEADDADEV";
    case DEADADDEV:
        return "DEADADDEV";
    case NOTDIGITALCONF:
        return "NOTDIGITALCONF";
    case NOTCOUNTERCONF:
        return "NOTCOUNTERCONF";
    case NOTDACONF:
        return "NOTDACONF";
    case NOTADCONF:
        return "NOTADCONF";
    case NOTMUXCONF:
        return "NOTMUXCONF";
    case BADPORTNUM:
        return "BADPORTNUM";
    case BADCOUNTERDEVNUM:
        return "BADCOUNTERDEVNUM";
    case BADDADEVNUM:
        return "BADDADEVNUM";
    case BADSAMPLEMODE:
        return "BADSAMPLEMODE";
    case BADINT:
        return "BADINT";
    case BADADCHAN:
        return "BADADCHAN";
    case BADCOUNT:
        return "BADCOUNT";
    case BADCNTRCONFIG:
        return "BADCNTRCONFIG";
    case BADDAVAL:
        return "BADDAVAL";
    case BADDACHAN:
        return "BADDACHAN";
    case ALREADYACTIVE:
        return "ALREADYACTIVE";
    case PAGEOVERRUN:
        return "PAGEOVERRUN";
    case BADRATE:
        return "BADRATE";
    case COMPATMODE:
        return "COMPATMODE";
    case TRIGSTATE:
        return "TRIGSTATE";
    case ADSTATUSHUNG:
        return "ADSTATUSHUNG";
    case TOOFEW:
        return "TOOFEW";
    case OVERRUN:
        return "OVERRUN";
    case BADRANGE:
        return "BADRANGE";
    case NOPROGGAIN:
        return "NOPROGGAIN";
    case BADFILENAME:
        return "BADFILENAME";
    case DISKISFULL:
        return "DISKISFULL";
    case COMPATWARN:
        return "COMPATWARN";
    case BADPOINTER:
        return "BADPOINTER";
    case TOOMANYGAINS:
        return "TOOMANYGAINS";
    case RATEWARNING:
        return "RATEWARNING";
    case CONVERTDMA:
        return "CONVERTDMA";
    case DTCONNECTERR:
        return "DTCONNECTERR";
    case FORECONTINUOUS:
        return "FORECONTINUOUS";
    case BADBOARDTYPE:
        return "BADBOARDTYPE";
    case WRONGDIGCONFIG:
        return "WRONGDIGCONFIG";
    case NOTCONFIGURABLE:
        return "NOTCONFIGURABLE";
    case BADPORTCONFIG:
        return "BADPORTCONFIG";
    case BADFIRSTPOINT:
        return "BADFIRSTPOINT";
    case ENDOFFILE:
        return "ENDOFFILE";
    case NOT8254CTR:
        return "NOT8254CTR";
    case NOT9513CTR:
        return "NOT9513CTR";
    case BADTRIGTYPE:
        return "BADTRIGTYPE";
    case BADTRIGVALUE:
        return "BADTRIGVALUE";
    case BADOPTION:
        return "BADOPTION";
    case BADPRETRIGCOUNT:
        return "BADPRETRIGCOUNT";
    case BADDIVIDER:
        return "BADDIVIDER";
    case BADSOURCE:
        return "BADSOURCE";
    case BADCOMPARE:
        return "BADSOURCE";
    case BADTIMEOFDAY:
        return "BADTIMEOFDAY";
    case BADGATEINTERVAL:
        return "BADGATEINTERVAL";
    case BADGATECNTRL:
        return "BADGATECNTRL";
    case BADCOUNTEREDGE:
        return "BADCOUNTEREDGE";
    case BADSPCLGATE:
        return "BADSPCLGATE";
    case BADRELOAD:
        return "BADRELOAD";
    case BADRECYCLEFLAG:
        return "BADRECYCLEFLAG";
    case BADBCDFLAG:
        return "BADBCDFLAG";
    case BADDIRECTION:
        return "BADDIRECTION";
    case BADOUTCONTROL:
        return "BADOUTCONTROL";
    case BADBITNUMBER:
        return "BADBITNUMBER";
    case NONEENABLED:
        return "NONEENABLED";
    case BADCTRCONTROL:
        return "BADCTRCONTROL";
    case BADEXPCHAN:
        return "BADEXPCHAN";
    case WRONGADRANGE:
        return "WRONGADRANGE";
    case OUTOFRANGE:
        return "OUTOFRANGE";
    case BADTEMPSCALE:
        return "BADTEMPSCALE";
    case BADERRCODE:
        return "BADERRCODE";
    case NOQUEUE:
        return "NOQUEUE";
    case CONTINUOUSCOUNT:
        return "CONTINUOUSCOUNT";
    case UNDERRUN:
        return "UNDERRUN";
    case BADMEMMODE:
        return "BADMEMMODE";
    case FREQOVERRUN:
        return "FREQOVERRUN";
    case NOCJCCHAN:
        return "NOCJCCHAN";
    case BADCHIPNUM:
        return "BADCHIPNUM";
    case DIGNOTENABLED:
        return "DIGNOTENABLED";
    case CONVERT16BITS:
        return "CONVERT16BITS";
    case NOMEMBOARD:
        return "NOMEMBOARD";
    case DTACTIVE:
        return "DTACTIVE";
    case NOTMEMCONF:
        return "NOTMEMCONF";
    case ODDCHAN:
        return "ODDCHAN";
    case CTRNOINIT:
        return "CTRNOINIT";
    case NOT8536CTR:
        return "NOT8536CTR";
    case FREERUNNING:
        return "FREERUNNING";
    case INTERRUPTED:
        return "INTERRUPTED";
    case NOSELECTORS:
        return "NOSELECTORS";
    case NOBURSTMODE:
        return "NOBURSTMODE";
    case NOTWINDOWSFUNC:
        return "NOTWINDOWSFUNC";
    case NOTSIMULCONF:
        return "NOTSIMULCONF";
    case EVENODDMISMATCH:
        return "EVENODDMISMATCH";
    case M1RATEWARNING:
        return "M1RATEWARNING";
    case NOTRS485:
        return "NOTRS485";
    case NOTDOSFUNC:
        return "NOTDOSFUNC";
    case RANGEMISMATCH:
        return "RANGEMISMATCH";
    case CLOCKTOOSLOW:
        return "CLOCKTOOSLOW";
    case BADCALFACTORS:
        return "BADCALFACTORS";
    case BADCONFIGTYPE:
        return "BADCONFIGTYPE";
    case BADCONFIGITEM:
        return "BADCONFIGITEM";
    case NOPCMCIABOARD:
        return "NOPCMCIABOARD";
    case NOBACKGROUND:
        return "NOBACKGROUND";
    case STRINGTOOSHORT:
        return "STRINGTOOSHORT";
    case CONVERTEXTMEM:
        return "CONVERTEXTMEM";
    case BADEUADD:
        return "BADEUADD";
    case DAS16JRRATEWARNING:
        return "DAS16JRRATEWARNING";
    case DAS08TOOLOWRATE:
        return "DAS08TOOLOWRATE";
    case AMBIGSENSORONGP:
        return "AMBIGSENSORONGP";
    case NOSENSORTYPEONGP:
        return "NOSENSORTYPEONGP";
    case NOCONVERSIONNEEDED:
        return "NOCONVERSIONNEEDED";
    case NOEXTCONTINUOUS:
        return "NOEXTCONTINUOUS";
    case INVALIDPRETRIGCONVERT:
        return "INVALIDPRETRIGCONVERT";
    case BADCTRREG:
        return "BADCTRREG";
    case BADTRIGTHRESHOLD:
        return "BADTRIGTHRESHOLD";
    case BADPCMSLOTREF:
        return "BADPCMSLOTREF";
    case AMBIGPCMSLOTREF:
        return "AMBIGPCMSLOTREF";
    case BADSENSORTYPE:
        return "BADSENSORTYPE";
    case DELBOARDNOTEXIST:
        return "DELBOARDNOTEXIST";
    case NOBOARDNAMEFILE:
        return "NOBOARDNAMEFILE";
    case CFGFILENOTFOUND:
        return "CFGFILENOTFOUND";
    case NOVDDINSTALLED:
        return "NOVDDINSTALLED";
    case NOWINDOWSMEMORY:
        return "NOWINDOWSMEMORY";
    case OUTOFDOSMEMORY:
        return "OUTOFDOSMEMORY";
    case OBSOLETEOPTION:
        return "OBSOLETEOPTION";
    case NOPCMREGKEY:
        return "NOPCMREGKEY";
    case NOCBUL32SYS:
        return "NOCBUL32SYS";
    case NODMAMEMORY:
        return "NODMAMEMORY";
    case IRQNOTAVAILABLE:
        return "IRQNOTAVAILABLE";
    case NOT7266CTR:
        return "NOT7266CTR";
    case BADQUADRATURE:
        return "BADQUADRATURE";
    case BADCOUNTMODE:
        return "BADCOUNTMODE";
    case BADENCODING:
        return "BADENCODING";
    case BADINDEXMODE:
        return "BADINDEXMODE";
    case BADINVERTINDEX:
        return "BADINVERTINDEX";
    case BADFLAGPINS:
        return "BADFLAGPINS";
    case NOCTRSTATUS:
        return "NOCTRSTATUS";
    case NOINDEXALLOWED:
        return "NOINDEXALLOWED";
    case OPENCONNECTION:
        return "OPENCONNECTION";
    case BMCONTINUOUSCOUNT:
        return "BMCONTINUOUSCOUNT";
    case BADCALLBACKFUNC:
        return "BADCALLBACKFUNC";
    case MBUSINUSE:
        return "MBUSINUSE";
    case MBUSNOCTLR:
        return "MBUSNOCTLR";
    case BADEVENTTYPE:
        return "BADEVENTTYPE";
    case ALREADYENABLED:
        return "ALREADYENABLED";
    case BADEVENTSIZE:
        return "BADEVENTSIZE";
    case CANTINSTALLEVENT:
        return "CANTINSTALLEVENT";
    case BADBUFFERSIZE:
        return "BADBUFFERSIZE";
    case BADAIMODE:
        return "BADAIMODE";
    case BADSIGNAL:
        return "BADSIGNAL";
    case BADCONNECTION:
        return "BADCONNECTION";
    case BADINDEX:
        return "BADINDEX";
    case NOCONNECTION:
        return "NOCONNECTION";
    case BADBURSTIOCOUNT:
        return "BADBURSTIOCOUNT";
    case DEADDEV:
        return "DEADDEV";

    case INVALIDACCESS:
        return "INVALIDACCESS";
    case UNAVAILABLE:
        return "UNAVAILABLE";
    case NOTREADY:
        return "NOTREADY";
    case BITUSEDFORALARM:
        return "BITUSEDFORALARM";
    case PORTUSEDFORALARM:
        return "PORTUSEDFORALARM";
    case PACEROVERRUN:
        return "PACEROVERRUN";
    case BADCHANTYPE:
        return "BADCHANTYPE";
    case BADTRIGSENSE:
        return "BADTRIGSENSE";
    case BADTRIGCHAN:
        return "BADTRIGCHAN";
    case BADTRIGLEVEL:
        return "BADTRIGLEVEL";
    case NOPRETRIGMODE:
        return "NOPRETRIGMODE";
    case BADDEBOUNCETIME:
        return "BADDEBOUNCETIME";
    case BADDEBOUNCETRIGMODE:
        return "BADDEBOUNCETRIGMODE";
    case BADMAPPEDCOUNTER:
        return "BADMAPPEDCOUNTER";
    case BADCOUNTERMODE:
        return "BADCOUNTERMODE";
    case BADTCCHANMODE:
        return "BADTCCHANMODE";
    case BADFREQUENCY:
        return "BADFREQUENCY";
    case BADEVENTPARAM:
        return "BADEVENTPARAM";
    case NONETIFC:
        return "NONETIFC";
    case DEADNETIFC:
        return "DEADNETIFC";
    case NOREMOTEACK:
        return "NOREMOTEACK";
    case INPUTTIMEOUT:
        return "INPUTTIMEOUT";
    case MISMATCHSETPOINTCOUNT:
        return "MISMATCHSETPOINTCOUNT";
    case INVALIDSETPOINTLEVEL:
        return "INVALIDSETPOINTLEVEL";
    case INVALIDSETPOINTOUTPUTTYPE:
        return "INVALIDSETPOINTOUTPUTTYPE";
    case INVALIDSETPOINTOUTPUTVALUE:
        return "INVALIDSETPOINTOUTPUTVALUE";
    case INVALIDSETPOINTLIMITS:
        return "INVALIDSETPOINTLIMITS";
    case STRINGTOOLONG:
        return "STRINGTOOLONG";
    case INVALIDLOGIN:
        return "INVALIDLOGIN";
    case SESSIONINUSE:
        return "SESSIONINUSE";
    case NOEXTPOWER:
        return "NOEXTPOWER";
    case BADDUTYCYCLE:
        return "BADDUTYCYCLE";
    case BADINITIALDELAY:
        return "BADINITIALDELAY";
    case NOTEDSSENSOR:
        return "NOTEDSSENSOR";
    case INVALIDTEDSSENSOR:
        return "INVALIDTEDSSENSOR";
    case CALIBRATIONFAILED:
        return "CALIBRATIONFAILED";
    case BITUSEDFORTERMINALCOUNTSTATUS:
        return "BITUSEDFORTERMINALCOUNTSTATUS";
    case PORTUSEDFORTERMINALCOUNTSTATUS:
        return "PORTUSEDFORTERMINALCOUNTSTATUS";
    case BADEXCITATION:
        return "BADEXCITATION";
    case BADBRIDGETYPE:
        return "BADBRIDGETYPE";
    case BADLOADVAL:
        return "BADLOADVAL";
    case BADTICKSIZE:
        return "BADTICKSIZE";
    case BTHCONNECTIONFAILED:
        return "BTHCONNECTIONFAILED";
    case INVALIDBTHFRAME:
        return "INVALIDBTHFRAME";
    case BADTRIGEVENT:
        return "BADTRIGEVENT";
    case NETCONNECTIONFAILED:
        return "NETCONNECTIONFAILED";
    case DATASOCKETCONNECTIONFAILED:
        return "DATASOCKETCONNECTIONFAILED";
    case INVALIDNETFRAME:
        return "INVALIDNETFRAME";
    case NETTIMEOUT:
        return "NETTIMEOUT";
    case NETDEVNOTFOUND:
        return "NETDEVNOTFOUND";
    case INVALIDCONNECTIONCODE:
        return "INVALIDCONNECTIONCODE";
    case CONNECTIONCODEIGNORED:
        return "CONNECTIONCODEIGNORED";
    case NETDEVINUSE:
        return "NETDEVINUSE";
    case NETDEVINUSEBYANOTHERPROC:
        return "NETDEVINUSEBYANOTHERPROC";
    case SOCKETDISCONNECTED:
        return "SOCKETDISCONNECTED";
    case BOARDNUMINUSE:
        return "BOARDNUMINUSE";
    case DEVALREADYCREATED:
        return "DEVALREADYCREATED";
    case BOARDNOTEXIST:
        return "BOARDNOTEXIST";
    case INVALIDNETHOST:
        return "INVALIDNETHOST";
    case INVALIDNETPORT:
        return "INVALIDNETPORT";
    case INVALIDIFC:
        return "INVALIDIFC";
    case INVALIDAIINPUTMODE:
        return "INVALIDAIINPUTMODE";
    case AIINPUTMODENOTCONFIGURABLE:
        return "AIINPUTMODENOTCONFIGURABLE";
    case INVALIDEXTPACEREDGE:
        return "INVALIDEXTPACEREDGE";
    case CMREXCEEDED:
        return "CMREXCEEDED";
    default:
        QString errNo = QString(" (%1)").arg(errValue);
        return "NOERRDEFINED" + errNo;
    }
}

int LibMisc::mccGetInfoStr(QString &params, int infoItem,
                                 unsigned int index, char *infoValue, unsigned int &maxLen)
{
    int err;
    (void)index;

    if (infoItem == MVULVERSION) {
        int cfgLen = maxLen - 1;
        if (cfgLen > 0) {
            QString ulRevision = QString::number(CURRENTREVNUM);
            const QByteArray stringData = ulRevision.toUtf8();
            infoValue[qMin(cfgLen, stringData.size())] = '\0';
            std::copy(stringData.constBegin(),
                      stringData.constBegin() + qMin(cfgLen, stringData.size()), infoValue);
            maxLen = stringData.size();
        }
        params = "Approximation using CURRENTREVNUM";
        err = 0;
    } else {
        //length = maxConfigLen;
        //err = mvGetConfigString(params, BOARDINFO, deviceHandle, configItem, index, configValue, length);
        maxLen = 0;
    }
    return err;
}

int LibMisc::mccGetConfig(QString &params, int configItem, unsigned int index, long long &configValue)
{
    (void)configItem;
    (void)index;
    params = "";
    configValue = 0;
    return 0;
}

int LibMisc::mccGetCfgStr(QString &params, int configItem, unsigned int index,
                                char *configValue, unsigned int &maxConfigLen)
{
    //int err;
    (void)index;
    (void)configItem;
    (void)configValue;
    params = "";
    //length = maxConfigLen;
    //err = mvGetConfigString(params, BOARDINFO, deviceHandle, configItem, index, configValue, length);
    maxConfigLen = 0;

    return 0;
}

int LibMisc::mccSetConfig(QString &params, int configItem, unsigned int index, long long configValue)
{
    (void)configItem;
    (void)index;
    params = "";
    (void)configValue;
    return 0;
}

int LibMisc::mccDevGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, long long &infoValue)
{
    int infoType, err, surrogateItem;
    long long cfgVal, devNum;
    infoType = BOARDINFO;

    infoValue = 0;
    switch (infoItem) {
    case CICTRTYPE:
        surrogateItem = BICINUMDEVS;
        err = mvGetConfig(params, infoType, deviceHandle, index,  surrogateItem, cfgVal);
        if (cfgVal > 0) {
            infoType = COUNTERINFO;
            int subItem = CICTRTYPE;
            for (devNum = 0; devNum < cfgVal; devNum++) {
                err = mvGetConfig(params, infoType, deviceHandle, devNum,  subItem, cfgVal);
                if ((cfgVal == 7) | (cfgVal == 9)) {
                    infoValue = 1;
                    break;
                }
            }
        }
        break;
    default:
        err = mvGetConfig(params, infoType, deviceHandle, index,  infoItem, cfgVal);
        infoValue = (cfgVal > 0);
        break;
    }
    return err;
}

int LibMisc::mccDevGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, long long &configValue)
{
    int err, infoType;

    infoType = BOARDINFO;
    err = mvSetConfig(params, infoType, deviceHandle, index, configItem, configValue);
    return err;
}

int LibMisc::mccDevGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                                   int configItem, unsigned int index, char* configValue, unsigned int &maxConfigLen)
{
    int err, length;

    length = maxConfigLen;
    err = mvGetConfigString(params, BOARDINFO, deviceHandle, configItem, index, configValue, length);
    maxConfigLen = length;
    return err;
}

int LibMisc::mccDevSetConfig(QString &params, DaqDeviceHandle deviceHandle,
                                   int configItem, unsigned int index, long long configValue)
{
    int err, infoType;

    infoType = BOARDINFO;
    err = mvSetConfig(params, infoType, deviceHandle, index, configItem, configValue);
    return err;
}

int LibMisc::mccDevSetConfigStr(QString &params, DaqDeviceHandle deviceHandle,
                                      int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen)
{
    int err, infoType;

    infoType = BOARDINFO;
    err = mvSetConfigStr(params, infoType, deviceHandle, index, configItem, configValue, maxConfigLen);
    return err;
}

int LibMisc::mccAiGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                int infoItem, unsigned int index, long long &infoValue)
{
    int infoType, err;
    infoType = BOARDINFO;

    infoValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  infoItem, infoValue);
    return err;
}

int LibMisc::mccAiGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                   int infoItem, unsigned int index, double &infoValue)
{
    (void)deviceHandle;
    (void)infoItem;
    (void)index;
    params = "";
    infoValue = 0.0;
    return 0;
}

int LibMisc::mccAiGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                               int configItem, unsigned int index, long long &configValue)
{
    int infoType, err;
    infoType = BOARDINFO;

    configValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  configItem, configValue);
    return err;
}

int LibMisc::mccAiGetCfgDbl(QString &params, DaqDeviceHandle deviceHandle,
                                  int configItem, unsigned int index, double &configValue)
{
    (void)deviceHandle;
    (void)configItem;
    (void)index;
    params = "";
    configValue = 0.0;
    return 0;
}

int LibMisc::mccAiGetCfgStr(QString &params, DaqDeviceHandle deviceHandle,
                                  int configItem, unsigned int index, char *configValue, unsigned int &maxConfigLen)
{
    int err, length;

    length = maxConfigLen;
    err = mvGetConfigString(params, BOARDINFO, deviceHandle, configItem, index, configValue, length);
    maxConfigLen = length;
    return err;
}

int LibMisc::mccAiSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                               int configItem, unsigned int index, long long configValue)
{
    int err, infoType;

    infoType = BOARDINFO;
    err = mvSetConfig(params, infoType, deviceHandle, index, configItem, configValue);
    return err;
}

int LibMisc::mccAoGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                int infoItem, unsigned int index, long long &infoValue)
{
    int infoType, err;
    infoType = BOARDINFO;

    infoValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  infoItem, infoValue);
    return err;
}

int LibMisc::mccAoGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                   int infoItem, unsigned int index, double &infoValue)
{
    (void)deviceHandle;
    (void)infoItem;
    (void)index;
    params = "";
    infoValue = 0;
    return 0;
}

int LibMisc::mccAoGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                               int configItem, unsigned int index, long long &configValue)
{
    int infoType, err;
    infoType = BOARDINFO;

    configValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  configItem, configValue);
    return err;
}

int LibMisc::mccAoSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                               int configItem, unsigned int index, long long configValue)
{
    int err, infoType;

    infoType = BOARDINFO;
    err = mvSetConfig(params, infoType, deviceHandle, index, configItem, configValue);
    return err;
}

int LibMisc::mccDioGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                int infoItem, unsigned int index, long long &infoValue)
{
    int infoType, err;

    switch (infoItem) {
    case BIDITRIGCOUNT:
    case BIDOTRIGCOUNT:
    case BIDINUMDEVS:
    case BIPATTERNTRIGPORT:
    case BIDISOFILTER:
    case BIDISCANOPTIONS:
    case BIDOSCANOPTIONS:
    case BIRELAYLOGIC:
    case BIOPENRELAYLEVEL:
        infoType = BOARDINFO;
        break;
    default:
        infoType = DIGITALINFO;
        break;
    }

    infoValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  infoItem, infoValue);
    return err;
}

int LibMisc::mccDioGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                    int infoItem, unsigned int index, double &infoValue)
{
    (void)deviceHandle;
    (void)infoItem;
    (void)index;
    params = "";
    infoValue = 0;
    return 0;
}

int LibMisc::mccDioGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, long long &configValue)
{
    int infoType, err;
    infoType = BOARDINFO;
    if (configItem == DIDISABLEDIRCHECK)
        infoType = DIGITALINFO;

    configValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  configItem, configValue);
    return err;
}

int LibMisc::mccDioSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, long long configValue)
{
    int err, infoType;

    infoType = BOARDINFO;
    if (configItem == DIDISABLEDIRCHECK)
        infoType = DIGITALINFO;
    err = mvSetConfig(params, infoType, deviceHandle, index, configItem, configValue);
    return err;
}

int LibMisc::mccCtrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, long long &infoValue)
{
    int infoType, err;

    switch (infoItem) {
    case CICTRTYPE:
        infoType = COUNTERINFO;
        break;
    default:
        infoType = BOARDINFO;
        break;
    }

    infoValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  infoItem, infoValue);
    return err;
}

int LibMisc::mccCtrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                    int infoItem, unsigned int index, double &infoValue)
{
    (void)deviceHandle;
    (void)infoItem;
    (void)index;
    params = "";
    infoValue = 0;
    return 0;
}

int LibMisc::mccCtrGetCfg(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, long long &configValue)
{
    int infoType, err;
    infoType = BOARDINFO;

    configValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  configItem, configValue);
    return err;
}

int LibMisc::mccCtrSetCfg(QString &params, DaqDeviceHandle deviceHandle,
                                int configItem, unsigned int index, long long configValue)
{
    int err, infoType;

    infoType = BOARDINFO;
    err = mvSetConfig(params, infoType, deviceHandle, index, configItem, configValue);
    return err;
}

int LibMisc::mccTmrGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                 int infoItem, unsigned int index, long long &infoValue)
{
    (void)deviceHandle;
    (void)infoItem;
    (void)index;
    params = "";
    infoValue = 0;
    return 0;
}

int LibMisc::mccTmrGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                    int infoItem, unsigned int index, double &infoValue)
{
    (void)deviceHandle;
    (void)infoItem;
    (void)index;
    params = "";
    infoValue = 0;
    return 0;
}

int LibMisc::mccDaqInGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                   int infoItem, unsigned int index, long long &infoValue)
{
    int infoType, err;

    infoType = BOARDINFO;
    infoValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  infoItem, infoValue);
    return err;
}

int LibMisc::mccDaqInGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                      int infoItem, unsigned int index, double &infoValue)
{
    (void)deviceHandle;
    (void)infoItem;
    (void)index;
    params = "";
    infoValue = 0;
    return 0;
}

int LibMisc::mccDaqOutGetInfo(QString &params, DaqDeviceHandle deviceHandle,
                                    int infoItem, unsigned int index, long long &infoValue)
{
    int infoType, err;

    infoType = BOARDINFO;
    infoValue = 0;
    err = mvGetConfig(params, infoType, deviceHandle, index,  infoItem, infoValue);
    return err;
}

int LibMisc::mccDaqOutGetInfoDbl(QString &params, DaqDeviceHandle deviceHandle,
                                       int infoItem, unsigned int index, double &infoValue)
{
    (void)deviceHandle;
    (void)infoItem;
    (void)index;
    params = "";
    infoValue = 0;
    return 0;
}

int LibMisc::mvGetConfig(QString &params, int infoType, DaqDeviceHandle
                                deviceHandle, unsigned int index, int configItem, long long &configVal)
{
    int err, cfgVal, devNum;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    cfgVal = 0;
    devNum = int(index);
    funcName = "cbGetConfig";
    argString = "(InfoType, deviceHandle, DevNum, ConfigItem, &cfgVal)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbGetConfig(infoType, deviceHandle, devNum, configItem, &cfgVal);
    argVals = QString("(%1, %2, %3, %4, %5)")
            .arg(infoType)
            .arg(deviceHandle)
            .arg(devNum)
            .arg(configItem)
            .arg(cfgVal);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    configVal = cfgVal;
    return err;
}

int LibMisc:: mvSetConfig(QString &params, int infoType, DaqDeviceHandle deviceHandle,
                               unsigned int index, int configItem, long long configVal)
{
    int err, cfgVal, devNum;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    cfgVal = configVal;
    devNum = int(index);
    funcName = "cbSetConfig";
    argString = "(infoType, deviceHandle, devNum, configItem, configVal)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbSetConfig(infoType, deviceHandle, index, configItem, cfgVal);
    argVals = QString("(%1, %2, %3, %4, %5)")
            .arg(infoType)
            .arg(deviceHandle)
            .arg(devNum)
            .arg(configItem)
            .arg(cfgVal);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    configVal = cfgVal;
    return err;
}

int LibMisc::mvSetConfigStr(QString &params, int infoType, DaqDeviceHandle deviceHandle,
                                  unsigned int index, int configItem, char *cfgString, unsigned int &length)
{
    int err, devNum, cfgLength;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    devNum = int(index);
    cfgLength = int(length);
    funcName = "cbSetConfigString";
    argString = "(infoType, deviceHandle, index, configItem, cfgString, length)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbSetConfigString(infoType, deviceHandle, devNum, configItem, cfgString, &cfgLength);
    argVals = QString("(%1, %2, %3, %4, %5, %6)")
            .arg(infoType)
            .arg(deviceHandle)
            .arg(devNum)
            .arg(configItem)
            .arg(cfgString)
            .arg(cfgLength);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    length = cfgLength;
    return err;
}

int LibMisc::mvGetConfigString(QString &params, int infoType, DaqDeviceHandle deviceHandle,
                                     int configItem, unsigned int index, char *configVal, int &length)
{
    int err;
    QString funcName, argString, argVals;
    QTime t;
    QString sStartTime;

    funcName = "cbGetConfigString";
    argString = "(InfoType, deviceHandle, index, ConfigItem, configVal, &length)\n";
    sStartTime = t.currentTime().toString("hh:mm:ss.zzz") + "\n";
    err = cbGetConfigString(infoType, deviceHandle, index, configItem, configVal, &length);
    argVals = QString("(%1, %2, %3, %4, %5, %6)")
            .arg(infoType)
            .arg(deviceHandle)
            .arg(index)
            .arg(configItem)
            .arg(configVal)
            .arg(length);

    params = funcName + argString + funcName + argVals;
    miscErrorDialog->addFunction(sStartTime + params + QString("\n%1").arg(err));
    return err;
}


QMap<int, QString> LibMisc::mccGetUlInfoItems()
{
    QMap<int, QString> ulInfoItems;

    ulInfoItems.insert(MVULVERSION, "0:1:UL Version");
    return ulInfoItems;
}

QMap<int, QString> LibMisc::mccGetUlCfgItems()
{
    QMap<int, QString> ulConfigItems;
    ulConfigItems.clear();
    return ulConfigItems;
}

QMap<int, QString> LibMisc::mccGetDevCfgItems()
{
    QMap<int, QString> devConfigItems;

    devConfigItems.insert(BIDEVUNIQUEID, "0:1:Unique ID");
    devConfigItems.insert(BIDEVSERIALNUM, "0:1:Serial Num");
    devConfigItems.insert(BIMFGSERIALNUM, "0:1:Mfg Serial Num");
    devConfigItems.insert(BIDEVMACADDR, "0:1:MAC Address");
    devConfigItems.insert(BIDEVVERSION, "1:1:Version");
    devConfigItems.insert(BIDEVNOTES, "0:1:User Notes");
    devConfigItems.insert(BINETBIOSNAME, "0:1:BIOS Name");
    devConfigItems.insert(BIDEVIPADDR, "0:1:IP Address");
    devConfigItems.insert(BINETCONNECTCODE, "0:0:Connect Code");
    devConfigItems.insert(BINETIOTIMEOUT, "0:0:Net Timeout");
    devConfigItems.insert(BIUSERDEVIDNUM, "0:0:User ID");
    devConfigItems.insert(BIINTLEVEL, "0:0:Interrupt");
    devConfigItems.insert(BIINPUTPACEROUT, "0:0:InPacerOut");
    devConfigItems.insert(BIOUTPUTPACEROUT, "0:0:OutPacerOut");
    devConfigItems.insert(BIEXTINPACEREDGE, "0:0:ExtInPacerEdge");
    devConfigItems.insert(BIEXTOUTPACEREDGE, "0:0:ExtOutPacerEdge");
    devConfigItems.insert(BIEXTCLKTYPE, "0:0:ExtClkType");
    devConfigItems.insert(BINETCONNECTIONCODE, "0:0:ConnectCode");
    devConfigItems.insert(BINETIOTIMEOUT, "0:0:NetTimeout");
    devConfigItems.insert(BIPATTERNTRIGPORT, "0:0:PatternTrigPort");
    devConfigItems.insert(BISERIALNUM, "0:0:LegacySerNo");
    return devConfigItems;
}

QMap<int, QString> LibMisc::mccGetDevInfoItems()
{
    QMap<int, QString> devInfoItems;

    devInfoItems.insert(BIDEVUNIQUEID, "0:1:Unique ID");
    devInfoItems.insert(BINUMADCHANS, "0:0:Has AD Dev");
    devInfoItems.insert(BINUMDACHANS, "0:0:Has DA Dev");
    devInfoItems.insert(BIDINUMDEVS, "0:0:Has DIO Dev");
    devInfoItems.insert(BICINUMDEVS, "0:0:Has CTR Dev");
    devInfoItems.insert(BIUSESEXPS, "0:0:Has EXP Cap");
    devInfoItems.insert(CICTRTYPE, "0:0:Has TMR Dev");
    devInfoItems.insert(BIDAQINUMCHANTYPES, "0:0:Has DAQI Dev");
    devInfoItems.insert(BIDAQONUMCHANTYPES, "0:0:Has DAQO Dev");
    devInfoItems.insert(-1, "0:0:Has Events");
    devInfoItems.insert(-1, "0:0:Has MEM Regions");
    return devInfoItems;
}

QMap<int, QString> LibMisc::mccGetAiInfoItems()
{
    QMap<int, QString> aiInfoItems;

    aiInfoItems.insert(BIADRES, "0:0:Resolution");
    aiInfoItems.insert(BINUMADCHANS, "0:0:Num Chans");
    aiInfoItems.insert(BIADSCANOPTIONS, "0:0:Scan Options");
    aiInfoItems.insert(BIADNUMDIFFRANGES, "0:0:Num Diff Ranges");
    aiInfoItems.insert(BIADDIFFRANGE, "1:0:Diff Range");
    aiInfoItems.insert(BIADNUMSERANGES, "0:0:Num SE Ranges");
    aiInfoItems.insert(BIADSERANGE, "1:0:SE Ranges");
    aiInfoItems.insert(BINUMTEMPCHANS, "0:0:Num Temp Chans");
    aiInfoItems.insert(BIINPUTPACEROUT, "0:0:In Pacer Output");
    aiInfoItems.insert(BIADNUMCHANMODES, "0:0:Num Chan Modes");
    aiInfoItems.insert(BIADCHANMODE, "1:0:Chan Mode");
    aiInfoItems.insert(BIADNUMTRIGTYPES, "0:0:Num Trig Types");
    aiInfoItems.insert(BIADTRIGTYPE, "1:0:Trig Type");
    aiInfoItems.insert(BIADMAXRATE, "0:0:Max Rate");
    aiInfoItems.insert(BIADMAXTHROUGHPUT, "0:0:Max Thruput");
    aiInfoItems.insert(BIADCHANTYPES, "0:0:Chan Types");
    aiInfoItems.insert(BIADMAXSEQUEUELENGTH, "0:0:Queue SE Length");
    aiInfoItems.insert(BIADMAXDIFFQUEUELENGTH, "0:0:Queue Diff Length");
    aiInfoItems.insert(BIADQUEUETYPES, "0:0:Queue Types");
    aiInfoItems.insert(BIADQUEUELIMITS, "0:0:Queue Limits");
    return aiInfoItems;
}

QMap<int, QString> LibMisc::mccGetAiCfgItems()
{
    QMap<int, QString> aiCfgItems;

    aiCfgItems.insert(BINUMADCHANS, "0:0:NumChans");
    aiCfgItems.insert(BIADAIMODE, "0:0:Input Mode");
    aiCfgItems.insert(BINUMADCHANS, "0:0:Num Chans");
    aiCfgItems.insert(BIRANGE, "0:0:HW Range");
    aiCfgItems.insert(BIADTRIGCOUNT, "0:0:Trig Count");
    aiCfgItems.insert(BIADTRIGSRC, "0:0:Trig Source");
    aiCfgItems.insert(BIADXFERMODE, "0:0:AD Xfer Mode");
    aiCfgItems.insert(BIADCSETTLETIME, "0:0:AD Settling");
    aiCfgItems.insert(BIADTIMINGMODE, "0:0:AD Tmg Mode");
    aiCfgItems.insert(BIADCHANTYPE, "1:0:Chan Type");
    aiCfgItems.insert(BIADCHANAIMODE, "1:0:Chan Mode");
    aiCfgItems.insert(BIADDATARATE, "1:0:Data Rate");
    aiCfgItems.insert(BICALTABLETYPE, "0:0:Cal Table");
    aiCfgItems.insert(BICALOUTPUT, "0:0:Cal Output");
    aiCfgItems.insert(BICHANRTDTYPE, "1:0:ChanRTDType");
    aiCfgItems.insert(BICHANTCTYPE, "1:0:ChanRTDType");
    aiCfgItems.insert(BIDETECTOPENTC, "1:0:OTCDetect"); //base or EXP
    aiCfgItems.insert(BITEMPREJFREQ, "0:0:TempRejFreq"); //0, 50, 60
    return aiCfgItems;
}

QMap<int, QString> LibMisc::mccGetAoInfoItems()
{
    QMap<int, QString> aoInfoItems;

    aoInfoItems.insert(BIDACRES, "0:0:Resolution");
    aoInfoItems.insert(BINUMDACHANS, "0:0:Num Chans");
    aoInfoItems.insert(BIOUTPUTPACEROUT, "0:0:Out Pacer Output");
    aoInfoItems.insert(BIDACSCANOPTIONS, "0:0:Scan Options");
    aoInfoItems.insert(BIDACHASPACER, "0:0:Has Pacer");
    aoInfoItems.insert(BIDACFIFOSIZE, "0:0:FIFO Size");
    aoInfoItems.insert(BIDACNUMRANGES, "0:0:Num Ranges");
    aoInfoItems.insert(BIDACDEVRANGE, "1:0:DAC Range");
    aoInfoItems.insert(BIDACNUMTRIGTYPES, "0:0:Num Trig Types");
    aoInfoItems.insert(BIDACTRIGTYPE, "1:0:Trig Type");
    return aoInfoItems;
}

QMap<int, QString> LibMisc::mccGetAoCfgItems()
{
    QMap<int, QString> aoCfgItems;

    aoCfgItems.insert(BISYNCMODE, "0:0:Sync Mode");
    aoCfgItems.insert(BIDACUPDATEMODE, "0:0:Update Mode");
    aoCfgItems.insert(BIDACSTARTUP, "0:0:Startup Mode");
    aoCfgItems.insert(BIDACTRIGCOUNT, "0:0:Trig Count");
    aoCfgItems.insert(BIDACFORCESENSE, "0:0:Sense Cfg");
    aoCfgItems.insert(BIDACUPDATECMD, "0:0:UpdateCmd");
    //aoCfgItems.insert(BIDACSETTLETIME, "0:0:HW Range");
    aoCfgItems.insert(BIDACRANGE, "0:0:HW Range");
    return aoCfgItems;
}

QMap<int, QString> LibMisc::mccGetDioInfoItems()
{
    QMap<int, QString> dioInfoItems;

    dioInfoItems.insertMulti(BIDINUMDEVS, "0:0:NumPorts");
    dioInfoItems.insertMulti(DIDEVTYPE, "1:0:PortType");
    dioInfoItems.insertMulti(DINUMBITS, "1:0:NumBits");
    dioInfoItems.insertMulti(DIINMASK, "1:0:InputMask");
    dioInfoItems.insertMulti(DIOUTMASK, "1:0:OutputMask");
    dioInfoItems.insertMulti(DICONFIG, "1:0:Config");
    dioInfoItems.insertMulti(DICURVAL, "1:0:CurVal");
    dioInfoItems.insertMulti(BIDISCANOPTIONS, "0:0:DiScanOptions");
    dioInfoItems.insertMulti(BIDOSCANOPTIONS, "0:0:DoScanOptions");
    dioInfoItems.insertMulti(BIRELAYLOGIC, "1:0:RelayLogic");
    dioInfoItems.insertMulti(BIOPENRELAYLEVEL, "1:0:OpenRelayLevel");
    return dioInfoItems;
}

QMap<int, QString> LibMisc::mccGetDioCfgItems()
{
    QMap<int, QString> dioCfgItems;

    dioCfgItems.insert(BIDITRIGCOUNT, "0:0:DITrigCount");
    dioCfgItems.insert(BIDOTRIGCOUNT, "0:0:DOTrigCount");
    dioCfgItems.insert(BIDISOFILTER, "1:0:IsoFilter");
    dioCfgItems.insert(DIDISABLEDIRCHECK, "0:0:DisableDirCheck");
    return dioCfgItems;
}

QMap<int, QString> LibMisc::mccGetCtrInfoItems()
{
    QMap<int, QString> ctrInfoItems;

    ctrInfoItems.insert(BICINUMDEVS, "0:0:NumCtrs");
    ctrInfoItems.insert(BICTRZACTIVEMODE, "1:0:IndexMode");
    ctrInfoItems.insert(CICTRTYPE, "1:0:CtrType");
    ctrInfoItems.insert(BICTRSCANOPTIONS, "0:0:ScanOptions");
    return ctrInfoItems;
}

QMap<int, QString> LibMisc::mccGetCtrCfgItems()
{
    QMap<int, QString> ctrCfgItems;

    ctrCfgItems.insert(BICTRZACTIVEMODE, "0:0:CtrIndexActiveMode");
    ctrCfgItems.insert(BICTRTRIGCOUNT, "0:0:TrigCount");
    ctrCfgItems.insert(BITERMCOUNTSTATBIT, "1:0:TermCntBit");   //0=enable? index=bit
    return ctrCfgItems;
}

QMap<int, QString> LibMisc::mccGetTmrInfoItems()
{
    QMap<int, QString> tmrInfoItems;

    tmrInfoItems.clear();
    return tmrInfoItems;
}

QMap<int, QString> LibMisc::mccGetDaqInInfoItems()
{
    QMap<int, QString> daqInInfoItems;

    daqInInfoItems.insert(BIDAQISCANOPTIONS, "0:0:DaqInOptions");
    daqInInfoItems.insert(BIDAQITRIGCOUNT, "0:0:DaqInTrigCount");
    daqInInfoItems.insert(BIDAQINUMCHANTYPES, "0:0:DaqINumChanTypes");
    daqInInfoItems.insert(BIDAQICHANTYPE, "1:0:DaqIChanType");
    return daqInInfoItems;
}

QMap<int, QString> LibMisc::mccGetDaqOutInfoItems()
{
    QMap<int, QString> daqOutInfoItems;

    daqOutInfoItems.insert(BIDAQOSCANOPTIONS, "0:0:DaqOutOptions");
    daqOutInfoItems.insert(BIDAQONUMCHANTYPES, "0:0:DaqONumChanTypes");
    daqOutInfoItems.insert(BIDAQOCHANTYPE, "1:0:DaqOChanType");
    return daqOutInfoItems;
}

