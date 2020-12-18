#ifndef DIGITALUTILITY_H
#define DIGITALUTILITY_H

#include "libdigital.h"
#include "libmisc.h"

#define PORTOUT     1
#define PORTIN      2
#define PORTOUTSCAN 5
#define PORTINSCAN  10
#define BITOUT      17
#define BITIN       34
#define FIXEDPORT   0
#define PROGPORT    1
#define PROGBIT     2

#define BIDAQINUMCHANTYPES	376
#define BIDAQICHANTYPE		377
#define BIDAQONUMCHANTYPES	378
#define BIDAQOCHANTYPE		379

class DigitalUtility
{
public:
    DigitalUtility(LibMisc *miscFuncs);

    int findPortsOfType(DaqDeviceHandle devHandle, int portType, int &progAbility, int &defaultPort, int &defaultNumBits, int &firstBit);
    int getBitOffset(DaqDeviceHandle devHandle, int portIndex);

private:
    LibDigital *libDigitalFuncs;
    LibMisc *libMiscFuncs;

};

#endif // DIGITALUTILITY_H
