#ifndef ULENUM_H
#define ULENUM_H

#include "uldaq.h"

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
    MCC_BIP3VOLTS       = BIP3VOLTS,
    MCC_BIPPT312VOLTS   = BIPPT312VOLTS,
    MCC_BIPPT156VOLTS   = BIPPT156VOLTS,

    MCC_UNI60VOLTS		= UNI60VOLTS,
    MCC_UNI30VOLTS		= UNI30VOLTS,
    MCC_UNI15VOLTS		= UNI15VOLTS,
    MCC_UNI20VOLTS      = UNI20VOLTS,
    MCC_UNI10VOLTS      = UNI10VOLTS,
    MCC_UNI5VOLTS       = UNI5VOLTS,
    MCC_UNI4VOLTS       = UNI4VOLTS,
    MCC_UNI2PT5VOLTS    = UNI2PT5VOLTS,
    MCC_UNI2VOLTS       = UNI2VOLTS,
    MCC_UNI1PT25VOLTS   = UNI1PT25VOLTS,
    MCC_UNI1VOLTS       = UNI1VOLTS,
    MCC_UNIPT625VOLTS   = UNIPT625VOLTS,
    MCC_UNIPT5VOLTS     = UNIPT5VOLTS,
    MCC_UNIPT25VOLTS    = UNIPT25VOLTS,
    MCC_UNIPT125VOLTS   = UNIPT125VOLTS,
    MCC_UNIPT2VOLTS     = UNIPT2VOLTS,
    MCC_UNIPT1VOLTS     = UNIPT1VOLTS,

    MCC_UNIPT078VOLTS   = UNIPT078VOLTS,
    MCC_UNIPT05VOLTS    = UNIPT05VOLTS,
    MCC_UNIPT01VOLTS    = UNIPT01VOLTS,
    MCC_UNIPT005VOLTS   = UNIPT005VOLTS,
    MCC_MA0TO20         = MA0TO20,
    MCC_MA4TO20         = 200,            /* 4 to 20 ma */
    MCC_MA2TO10         = 201,            /* 2 to 10 ma */
    MCC_MA1TO5          = 202,            /* 1 to 5 ma */
    MCC_MAPT5TO2PT5     = 203,            /* .5 to 2.5 ma */
    MCC_BIPPT025AMPS    = 205,            /* -0.025 to 0.025 ma */

}MccRange;

#define MCC_DIG_NUMDEVS         DIO_INFO_NUM_PORTS
#define MCC_DIG_DEVTYPE         DIO_INFO_PORT_TYPE
#define MCC_DIG_NUMBITS         DIO_INFO_NUM_BITS
#define MCC_DIG_PORTIOTYPE      DIO_INFO_PORT_IO_TYPE
#define MCC_DIG_DIRIN           DD_INPUT
#define MCC_DIG_DIROUT          DD_OUTPUT

#define MCC_DIG_DAQINUMCHANTYPES    DAQI_INFO_CHAN_TYPES
#define MCC_DIG_DAQICHANTYPE        0
#define MCC_DIG_DAQONUMCHANTYPES    DAQO_INFO_CHAN_TYPES
#define MCC_DIG_DAQOCHANTYPE        0

typedef enum
{
    MCC_AUXPORT = AUXPORT,
    MCC_AUXPORT0 = AUXPORT0,
    MCC_AUXPORT1 = AUXPORT1,
    MCC_AUXPORT2 = AUXPORT2,
    MCC_FIRSTPORTA = FIRSTPORTA,
    MCC_FIRSTPORTB = FIRSTPORTB,
    MCC_FIRSTPORTC = FIRSTPORTC,
    MCC_FIRSTPORTCL = FIRSTPORTCL,
    MCC_FIRSTPORTCH = FIRSTPORTCH,
    MCC_SECONDPORTA = SECONDPORTA,
    MCC_SECONDPORTB = SECONDPORTB,
    MCC_SECONDPORTCL = SECONDPORTCL,
    MCC_SECONDPORTCH = SECONDPORTCH,
    MCC_THIRDPORTA = THIRDPORTA,
    MCC_THIRDPORTB = THIRDPORTB,
    MCC_THIRDPORTCL = THIRDPORTCL,
    MCC_THIRDPORTCH = THIRDPORTCH,
    MCC_FOURTHPORTA = FOURTHPORTA,
    MCC_FOURTHPORTB = FOURTHPORTB,
    MCC_FOURTHPORTCL = FOURTHPORTCL,
    MCC_FOURTHPORTCH = FOURTHPORTCH,
    MCC_FIFTHPORTA = FIFTHPORTA,
    MCC_FIFTHPORTB = FIFTHPORTB,
    MCC_FIFTHPORTCL = FIFTHPORTCL,
    MCC_FIFTHPORTCH = FIFTHPORTCH,
    MCC_SIXTHPORTA = SIXTHPORTA,
    MCC_SIXTHPORTB = SIXTHPORTB,
    MCC_SIXTHPORTCL = SIXTHPORTCL,
    MCC_SIXTHPORTCH = SIXTHPORTCH,
    MCC_SEVENTHPORTA = SEVENTHPORTA,
    MCC_SEVENTHPORTB = SEVENTHPORTB,
    MCC_SEVENTHPORTCL = SEVENTHPORTCL,
    MCC_SEVENTHPORTCH = SEVENTHPORTCH,
    MCC_EIGHTHPORTA = EIGHTHPORTA,
    MCC_EIGHTHPORTB = EIGHTHPORTB,
    MCC_EIGHTHPORTCL = EIGHTHPORTCL,
    MCC_EIGHTHPORTCH = EIGHTHPORTCH
} MccDigitalPortType;

typedef enum
{
    MCC_SO_DEFAULTIO            = SO_DEFAULTIO,
    MCC_SO_BACKGROUND           = SO_DEFAULTIO,
    MCC_SO_SINGLEIO             = SO_SINGLEIO,
    MCC_SO_BLOCKIO              = SO_BLOCKIO,
    MCC_SO_BURSTIO              = SO_BURSTIO,
    MCC_SO_CONTINUOUS           = SO_CONTINUOUS,
    MCC_SO_EXTCLOCK             = SO_EXTCLOCK,
    MCC_SO_EXTTRIGGER           = SO_EXTTRIGGER,
    MCC_SO_RETRIGGER            = SO_RETRIGGER,
    MCC_SO_BURSTMODE            = SO_BURSTMODE,
    MCC_SO_PACEROUT             = SO_PACEROUT,
    MCC_SO_EXTTIMEBASE          = SO_EXTTIMEBASE,
    MCC_SO_TIMEBASEOUT          = SO_TIMEBASEOUT,
    MCC_SO_CONVERTDATA          = SO_DEFAULTIO,
    MCC_SO_SCALEDATA            = SO_DEFAULTIO,
    MCC_SO_DMAIO                = SO_DEFAULTIO,
    MCC_SO_NONSTREAMEDIO        = SO_DEFAULTIO,
    MCC_SO_ADCCLOCKTRIG         = SO_DEFAULTIO,
    MCC_SO_ADCCLOCK             = SO_DEFAULTIO,
    MCC_SO_HIGHRESRATE          = SO_DEFAULTIO,
    MCC_SO_SHUNTCAL             = SO_DEFAULTIO,
    MCC_SO_WORDXFER             = SO_DEFAULTIO,
    MCC_SO_DWORDXFER            = SO_DEFAULTIO,
    MCC_SO_SIMULTANEOUS         = SO_DEFAULTIO,
    MCC_SO_NOFILTER             = SO_DEFAULTIO,
    MCC_SO_NOCLEAR              = SO_DEFAULTIO,
    MCC_SO_WAITFORNEWDATA       = SO_DEFAULTIO,
    MCC_SO_NOCALIBRATEDATA      = SO_DEFAULTIO
}MccScanOption;


#endif // ULENUM_H
