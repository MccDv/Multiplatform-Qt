#include "digitalutility.h"

DigitalUtility::DigitalUtility(LibMisc *miscFuncs)
{
    libMiscFuncs = miscFuncs;
}

int DigitalUtility::findPortsOfType(DaqDeviceHandle devHandle, int portType, int &progAbility, int &defaultPort, int &defaultNumBits, int &firstBit)
{
    int thisType, numPorts;
    int portsFound, numBits;
    int configVal, typeNum, i;
    int inMask;
    int curPort, err;
    int dioDev;
    bool portIsCompatible;
    bool digTypeExists;
    long long infoValue, configValue;
    QString params, connectionConflict;

    portsFound = 0;
    err = libMiscFuncs->mccDioGetInfo(params, devHandle, MCC_DIG_NUMDEVS, 0, infoValue);
    numPorts = infoValue;
    if (err != MCC_NOERRORS)
        return 0;

    firstBit = 0;
    defaultPort = -1;
    connectionConflict = "This network device is in use by another process or user."
       "\n\nCheck for other users on the network and close any applications "
       "\n(such as Instacal) that may be accessing the network device.";

    if ((portType == PORTOUTSCAN) | (portType == PORTINSCAN)) {
        if (numPorts > 0) {
            //check scan capability by trial and error with error handling disabled
            if (portType == PORTOUTSCAN) {
                err = libMiscFuncs->mccDioGetCfg(params, devHandle, MCC_DIG_DAQONUMCHANTYPES, 0, configValue);
                configVal = configValue;
                digTypeExists = false;
                if (configVal == 0)
                    numPorts = 0;
                else {
                    for (i = 0; i < configVal; i++) {
                        err = libMiscFuncs->mccDioGetCfg(params, devHandle, MCC_DIG_DAQOCHANTYPE, 0, configValue);
                        typeNum = configValue;
                        if (typeNum == 1)
                            digTypeExists = true;
                        if (typeNum == 2)
                            digTypeExists = true;
                        if (typeNum == 16)
                            digTypeExists = true;
                    }
                    if (!digTypeExists)
                        numPorts = 0;
                }
            } else {
                if (err != MCC_NOERRORS)
                    numPorts = 0;
            }
        }
        portType = portType & (PORTOUT | PORTIN);
    }
    for (dioDev = 0; dioDev < numPorts; dioDev++) {
        progAbility = -1;
        err = libMiscFuncs->mccDioGetCfg(params, devHandle, MCC_DIG_PORTIOTYPE, dioDev, configValue);
        inMask = configValue;
        if ((inMask == DPIOT_IN) | (inMask == DPIOT_OUT) | (inMask == DPIOT_NONCONFIG))
            progAbility = FIXEDPORT;
        err = libMiscFuncs->mccDioGetCfg(params, devHandle, MCC_DIG_DEVTYPE, dioDev, configValue);
        thisType = configValue;
        if (err != MCC_NOERRORS)
            curPort = thisType;
        if ((dioDev == 0) & (curPort = MCC_FIRSTPORTCL))
            /* a few devices (USB-SSR08 for example)
             * start at FIRSTPORTCL and number the bits
             * as if FIRSTPORTA and FIRSTPORTB exist for
             * compatibility with older digital peripherals */
            firstBit = 16;

        /* check if port is set for requested direction
         * or can be programmed for requested direction */
        portIsCompatible = false;
        if (inMask == DPIOT_NONCONFIG) {
            portIsCompatible = true;
        } else {
            if ((inMask == DPIOT_IO) | (inMask == DPIOT_BITIO))
                portIsCompatible = true;
            switch (portType) {
            case PORTOUT:
                if (inMask == DPIOT_OUT)
                    portIsCompatible = true;
                break;
            case PORTIN:
                if (inMask == DPIOT_IN)
                    portIsCompatible = true;
                break;
            }
        }
        if (portIsCompatible) {
            portsFound++;
            if (defaultPort == -1) {
                params = "";
                infoValue = portType;
                if (progAbility == FIXEDPORT)
                    params = "FIXEDPORT";
                libMiscFuncs->setPortDirInfo(portType);
                err = libMiscFuncs->mccDioGetInfo(params, devHandle, dioDev, MCC_DIG_NUMBITS, infoValue);
                numBits = infoValue;
                defaultNumBits = numBits;
                defaultPort = curPort;
            }
        }
        if (progAbility == PROGBIT)
            break;
    }
    return portsFound;
}

int DigitalUtility::getBitOffset(DaqDeviceHandle devHandle, int portIndex)
{

    int offset, err;
    unsigned int index;
    long long infoValue;
    QString params;

    offset = 0;
    if (portIndex < 2) {
        err = libMiscFuncs->mccDioGetInfo(params, devHandle, MCC_DIG_DEVTYPE, portIndex, infoValue);
       if (infoValue == MCC_FIRSTPORTCL)
           return 16;
       if (infoValue == MCC_FIRSTPORTCH)
           return 20;
    }
    for (index = 0; index < (unsigned int)portIndex; index++) {
        err = libMiscFuncs->mccDioGetInfo(params, devHandle, MCC_DIG_NUMBITS, index, infoValue);
        if (err == MCC_NOERRORS)
            offset += infoValue;
    }
    return offset;
}
