#ifndef ULENUMWINDOWS_H
#define ULENUMWINDOWS_H

#include "cbw.h"

#define MVULVERSION             777
#define BIADSCANOPTIONS         326
#define BIADNUMDIFFRANGES       314
#define BIADDIFFRANGE           315
#define BIADNUMSERANGES         316
#define BIADSERANGE             317
#define BIDAQINUMCHANTYPES      376
#define BIDAQONUMCHANTYPES      378
#define BIADNUMCHANMODES        312
#define BIADCHANMODE            313
#define BIADNUMTRIGTYPES        318
#define BIADTRIGTYPE            319
#define BIADMAXRATE             320
#define BIADMAXTHROUGHPUT       321
#define BIADMAXBURSTRATE        322
#define BIADMAXBURSTTHROUGHPUT  323
#define BIADHASPACER            324
#define BIADCHANTYPES           325
#define BIADMAXSEQUEUELENGTH    327
#define BIADMAXDIFFQUEUELENGTH  328
#define BIADQUEUETYPES          329
#define BIADQUEUELIMITS         330
#define BIDACSCANOPTIONS        332
#define BIDACHASPACER           331
#define BIDACFIFOSIZE           333
#define BIDACNUMRANGES          334
#define BIDACDEVRANGE           335
#define BIDACNUMTRIGTYPES       336
#define BIDACTRIGTYPE           337
#define BINETBIOSNAME           366
#define BIDEVIPADDR             374
#define BICTRZACTIVEMODE        380
#define BIDISCANOPTIONS         367
#define BIDOSCANOPTIONS         368
#define BICTRSCANOPTIONS        369
#define BIRELAYLOGIC            228
#define BIOPENRELAYLEVEL        229
#define BIDAQISCANOPTIONS       370
#define BIDAQOSCANOPTIONS       371
#define BIDAQINUMCHANTYPES      376
#define BIDAQICHANTYPE          377
#define BIDAQONUMCHANTYPES      378
#define BIDAQOCHANTYPE          379
#define BINETCONNECTIONCODE     341
#define BINETIOTIMEOUT          247

typedef enum
{
    AI_DIFFERENTIAL = DIFFERENTIAL,
    AI_SINGLE_ENDED = SINGLE_ENDED,
    AI_PSEUDO_DIFFERENTIAL = 3
}AiInputMode;

typedef enum
{
    DAQI_ANALOG_DIFF = ANALOG_DIFF,
    DAQI_ANALOG_SE = ANALOG_SE,
    DAQI_DIGITAL = DIGITAL,
    DAQI_CTR16 = CTR16,
    DAQI_CTR32 = CTR32LOW
}DaqChanTypes;

typedef enum
{
    MCC_BIP60VOLTS		= BIP60VOLTS,
    MCC_BIP30VOLTS		= BIP30VOLTS,
    MCC_BIP15VOLTS		= BIP15VOLTS,
    MCC_BIP20VOLTS      = BIP20VOLTS,
    MCC_BIP10VOLTS      = BIP10VOLTS,
    MCC_BIP5VOLTS       = BIP5VOLTS,
    MCC_BIP4VOLTS       = BIP4VOLTS,
    MCC_BIP2PT5VOLTS    = BIP2PT5VOLTS,
    MCC_BIP2VOLTS       = BIP2VOLTS,
    MCC_BIP1PT25VOLTS   = BIP1PT25VOLTS,
    MCC_BIP1VOLTS       = BIP1VOLTS,
    MCC_BIPPT625VOLTS   = BIPPT625VOLTS,
    MCC_BIPPT5VOLTS     = BIPPT5VOLTS,
    MCC_BIPPT25VOLTS    = BIPPT25VOLTS,
    MCC_BIPPT125VOLTS   = BIPPT125VOLTS,
    MCC_BIPPT2VOLTS     = BIPPT2VOLTS,
    MCC_BIPPT1VOLTS     = BIPPT1VOLTS,
    MCC_BIPPT078VOLTS   = BIPPT078VOLTS,
    MCC_BIPPT05VOLTS    = BIPPT05VOLTS,
    MCC_BIPPT01VOLTS    = BIPPT01VOLTS,
    MCC_BIPPT005VOLTS   = BIPPT005VOLTS,
    //MCC_BIP3VOLTS       = 22,             same value as BIPPT125VOLTS
    MCC_BIPPT312VOLTS   = BIPPT312VOLTS,
    MCC_BIPPT156VOLTS   = BIPPT156VOLTS,

    MCC_UNI60VOLTS		= 1001,
    MCC_UNI30VOLTS		= 1002,
    MCC_UNI15VOLTS		= 1003,
    MCC_UNI20VOLTS      = 1004,
    MCC_UNI10VOLTS      = UNI10VOLTS,
    MCC_UNI5VOLTS       = UNI5VOLTS,
    MCC_UNI4VOLTS       = UNI4VOLTS,
    MCC_UNI2PT5VOLTS    = UNI2PT5VOLTS,
    MCC_UNI2VOLTS       = UNI2VOLTS,
    MCC_UNI1PT25VOLTS   = UNI1PT25VOLTS,
    MCC_UNI1VOLTS       = UNI1VOLTS,
    MCC_UNIPT625VOLTS   = 1012,
    MCC_UNIPT5VOLTS     = UNIPT5VOLTS,
    MCC_UNIPT25VOLTS    = UNIPT25VOLTS,
    MCC_UNIPT125VOLTS   = 1015,
    MCC_UNIPT2VOLTS     = UNIPT2VOLTS,
    MCC_UNIPT1VOLTS     = UNIPT1VOLTS,

    MCC_UNIPT078VOLTS   = 1018,
    MCC_UNIPT05VOLTS    = UNIPT05VOLTS,
    MCC_UNIPT01VOLTS    = UNIPT01VOLTS,
    MCC_UNIPT005VOLTS   = 1021,

    MCC_MA4TO20         = MA4TO20,         /* 4 to 20 ma */
    MCC_MA2TO10         = MA2TO10,         /* 2 to 10 ma */
    MCC_MA1TO5          = MA1TO5,          /* 1 to 5 ma */
    MCC_MAPT5TO2PT5     = MAPT5TO2PT5,     /* .5 to 2.5 ma */
    MCC_MA0TO20         = MA0TO20,         /* 0 to 20 ma */
    MCC_BIPPT025AMPS    = BIPPT025AMPS     /* -0.025 to 0.025 ma */
}MccRange;

#define NOSCALEDATA 		1 << 0
//#define NOCALIBRATEDATA 	1 << 1
//#define SIMULTANEOUS		1 << 2
//#define NOCLEAR				1 << 3

typedef enum
{
    MCC_SO_DEFAULTIO            = DEFAULTIO,
    MCC_SO_BACKGROUND           = BACKGROUND,
    MCC_SO_SINGLEIO             = SINGLEIO,
    MCC_SO_BLOCKIO              = BLOCKIO,
    MCC_SO_BURSTIO              = BURSTIO,
    MCC_SO_CONTINUOUS           = CONTINUOUS,
    MCC_SO_EXTCLOCK             = EXTCLOCK,
    MCC_SO_EXTTRIGGER           = EXTTRIGGER,
    MCC_SO_RETRIGGER            = RETRIGMODE,
    MCC_SO_BURSTMODE            = BURSTMODE,
    MCC_SO_PACEROUT             = 1 << 8,
    MCC_SO_EXTTIMEBASE          = 1 << 9,
    MCC_SO_TIMEBASEOUT          = 1 << 10,
    MCC_SO_CONVERTDATA          = CONVERTDATA,
    MCC_SO_SCALEDATA            = SCALEDATA,
    MCC_SO_DMAIO                = DMAIO,
    MCC_SO_NONSTREAMEDIO        = NONSTREAMEDIO,
    MCC_SO_ADCCLOCKTRIG         = ADCCLOCKTRIG,
    MCC_SO_ADCCLOCK             = ADCCLOCK,
    MCC_SO_HIGHRESRATE          = HIGHRESRATE,
    MCC_SO_SHUNTCAL             = SHUNTCAL,
    MCC_SO_WORDXFER             = WORDXFER,
    MCC_SO_DWORDXFER            = DWORDXFER,
    MCC_SO_SIMULTANEOUS         = SIMULTANEOUS,
    MCC_SO_NOFILTER             = NOFILTER,
    MCC_SO_NOCLEAR              = NOCLEAR,
    MCC_SO_WAITFORNEWDATA       = WAITFORNEWDATA,
    MCC_SO_NOCALIBRATEDATA      = NOCALIBRATEDATA
}ScanOption;

typedef enum
{
    AINSCAN_FF_DEFAULT          = DEFAULTOPTION,
    AINSCAN_FF_NOSCALEDATA      = NOSCALEDATA,
    AINSCAN_FF_NOCALIBRATEDATA 	= 1 << 1
}AInScanFlag;

typedef enum
{
    AIN_FF_DEFAULT              = DEFAULTOPTION,
    AIN_FF_NOSCALEDATA          = NOSCALEDATA,
    AIN_FF_NOCALIBRATEDATA      = NOCALIBRATEDATA
}AInFlag;

typedef enum
{
    AOUTSCAN_FF_DEFAULT          = DEFAULTOPTION,
    AOUTSCAN_FF_NOSCALEDATA      = NOSCALEDATA,
    AOUTSCAN_FF_NOCALIBRATEDATA  = 1 << 1
}AOutScanFlag;

typedef enum
{
    AOUT_FF_DEFAULT              = DEFAULTOPTION,
    AOUT_FF_NOSCALEDATA          = NOSCALEDATA,
    AOUT_FF_NOCALIBRATEDATA      = NOCALIBRATEDATA
}AOutFlag;

typedef enum
{
    TS_CELSIUS  	= CELSIUS,
    TS_FAHRENHEIT 	= FAHRENHEIT,
    TS_KELVIN 		= KELVIN,
    TS_VOLTS 		= VOLTS,
    TS_NOSCALE 		= NOSCALE
}TempScale;

typedef enum
{
    TIN_FF_DEFAULT = 0,
    TIN_FF_WAIT_FOR_NEW_DATA = 1
}TInFlag;

typedef enum
{
    TINARRAY_FF_DEFAULT = 0,
    TINARRAY_FF_WAIT_FOR_NEW_DATA = 1
}TInArrayFlag;

typedef enum
{
    DEV_INFO_HAS_AI_DEV         = 1,
    DEV_INFO_HAS_AO_DEV         = 2,
    DEV_INFO_HAS_DIO_DEV        = 3,
    DEV_INFO_HAS_CTR_DEV        = 4,
    DEV_INFO_HAS_TMR_DEV        = 5,
    DEV_INFO_HAS_DAQI_DEV       = 6,
    DEV_INFO_HAS_DAQO_DEV       = 7,
    DEV_INFO_DAQ_EVENT_TYPES    = 8,
    DEV_INFO_MEM_REGIONS        = 9
}DevInfoItem;

typedef enum
{
    AI_INFO_RESOLUTION                  = 1,
    AI_INFO_NUM_CHANS                   = 2,
    AI_INFO_NUM_CHANS_BY_MODE           = 3,
    AI_INFO_NUM_CHANS_BY_TYPE           = 4,
    AI_INFO_CHAN_TYPES                  = 5,
    AI_INFO_SCAN_OPTIONS                = 6,
    AI_INFO_HAS_PACER                   = 7,
    AI_INFO_NUM_DIFF_RANGES             = 8,
    AI_INFO_NUM_SE_RANGES               = 9,
    AI_INFO_DIFF_RANGE                  = 10,
    AI_INFO_SE_RANGE                    = 11,
    AI_INFO_TRIG_TYPES                  = 12,
    AI_INFO_MAX_QUEUE_LENGTH_BY_MODE    = 13,
    AI_INFO_QUEUE_TYPES                 = 14,
    AI_INFO_QUEUE_LIMITS                = 15,
    AI_INFO_FIFO_SIZE                   = 16,
    AI_INFO_IEPE_SUPPORTED              = 17
}AiInfoItem;

#endif // ULENUMWINDOWS_H
