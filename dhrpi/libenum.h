#ifndef ULENUM_H
#define ULENUM_H

#include "daqhats.h"

typedef enum
{
    MCC_BIP10VOLTS      = A_IN_RANGE_BIP_10V,
    MCC_BIP5VOLTS       = A_IN_RANGE_BIP_5V,
    MCC_BIP2VOLTS       = A_IN_RANGE_BIP_2V,
    MCC_BIP1VOLTS       = A_IN_RANGE_BIP_1V,

    MCC_BIP60VOLTS		= 101,
    MCC_BIP30VOLTS		= 102,
    MCC_BIP15VOLTS		= 103,
    MCC_BIP20VOLTS      = 104,
    MCC_BIP4VOLTS       = 107,
    MCC_BIP2PT5VOLTS    = 108,
    MCC_BIP1PT25VOLTS   = 110,
    MCC_BIPPT625VOLTS   = 112,
    MCC_BIPPT5VOLTS     = 113,
    MCC_BIPPT25VOLTS    = 114,
    MCC_BIPPT125VOLTS   = 115,
    MCC_BIPPT2VOLTS     = 116,
    MCC_BIPPT1VOLTS     = 117,
    MCC_BIPPT078VOLTS   = 118,
    MCC_BIPPT05VOLTS    = 119,
    MCC_BIPPT01VOLTS    = 120,
    MCC_BIPPT005VOLTS   = 121,
    MCC_BIP3VOLTS       = 122,
    MCC_BIPPT312VOLTS   = 123,
    MCC_BIPPT156VOLTS   = 124,

    MCC_UNI60VOLTS		= 1001,
    MCC_UNI30VOLTS		= 1002,
    MCC_UNI15VOLTS		= 1003,
    MCC_UNI20VOLTS      = 1004,
    MCC_UNI10VOLTS      = 1005,
    MCC_UNI5VOLTS       = 1006,
    MCC_UNI4VOLTS       = 1007,
    MCC_UNI2PT5VOLTS    = 1008,
    MCC_UNI2VOLTS       = 1009,
    MCC_UNI1PT25VOLTS   = 1010,
    MCC_UNI1VOLTS       = 1011,

    MCC_UNIPT625VOLTS   = 1012,
    MCC_UNIPT5VOLTS     = 1013,
    MCC_UNIPT25VOLTS    = 1014,
    MCC_UNIPT125VOLTS   = 1015,
    MCC_UNIPT2VOLTS     = 1016,
    MCC_UNIPT1VOLTS     = 1017,
    MCC_UNIPT078VOLTS   = 1018,
    MCC_UNIPT05VOLTS    = 1019,
    MCC_UNIPT01VOLTS    = 1020,
    MCC_UNIPT005VOLTS   = 1021,
    MCC_MA0TO20 = 2000
}MccRange;


typedef enum
{
    MCC_SO_DEFAULTIO            = OPTS_DEFAULT,
    MCC_SO_CONTINUOUS           = OPTS_CONTINUOUS,
    MCC_SO_EXTCLOCK             = OPTS_EXTCLOCK,
    MCC_SO_EXTTRIGGER           = OPTS_EXTTRIGGER,
    MCC_SO_SCALEDATA            = OPTS_NOSCALEDATA,
    MCC_SO_NOCALIBRATEDATA      = OPTS_NOCALIBRATEDATA,

    MCC_SO_BURSTMODE            = 1 << 16,
    MCC_SO_BACKGROUND           = 1 << 16,
    MCC_SO_SINGLEIO             = 1 << 16,
    MCC_SO_BLOCKIO              = 1 << 16,
    MCC_SO_BURSTIO              = 1 << 16,
    MCC_SO_DMAIO                = 1 << 16,
    MCC_SO_HIGHRESRATE          = 1 << 16,
    MCC_SO_CONVERTDATA          = 1 << 16,
    MCC_SO_ADCCLOCKTRIG         = 1 << 16,
    MCC_SO_NOFILTER             = 1 << 16,
    MCC_SO_WAITFORNEWDATA       = 1 << 16,
    MCC_SO_ADCCLOCK             = 1 << 16,
    MCC_SO_RETRIGGER            = 1 << 16,
    MCC_SO_PACEROUT             = 1 << 16,
    MCC_SO_TIMEBASEOUT          = 1 << 16,
    MCC_SO_EXTTIMEBASE          = 1 << 16
}MccScanOption;

typedef enum
{
    DAQI_ANALOG_DIFF 	= 1 << 0,
    DAQI_ANALOG_SE 		= 1 << 1,
    DAQI_DIGITAL 		= 1 << 2,
    DAQI_CTR16			= 1 << 3,
    DAQI_CTR32			= 1 << 4,
    DAQI_CTR48			= 1 << 5,
    DAQI_DAC			= 1 << 7
}DaqInChanType;

#endif // ULENUM_H
