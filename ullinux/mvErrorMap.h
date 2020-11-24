#ifndef MVERRORMAP_H
#define MVERRORMAP_H

//#include "ulPlatform.h"

#ifdef MV_WINDOWS

#define MCC_ERRSTRLEN               ERRSTRLEN

#define MCC_NOERRORS                NOERRORS            /* No error occurred */
#define MCC_BADBOARD                BADBOARD            /* Invalid board number specified */
#define MCC_DEADDIGITALDEV          DEADDIGITALDEV      /* Digital I/O device is not responding  */
#define MCC_DEADCOUNTERDEV          DEADCOUNTERDEV      /* Counter I/O device is not responding */
#define MCC_DEADDADEV               DEADDADEV           /* D/A is not responding */
#define MCC_DEADADDEV               DEADADDEV           /* A/D is not responding */
#define MCC_NOTDIGITALCONF          NOTDIGITALCONF      /* Specified board does not have digital I/O */
#define MCC_NOTCOUNTERCONF          NOTCOUNTERCONF      /* Specified board does not have a counter */
#define MCC_NOTDACONF               NOTDACONF           /* Specified board is does not have D/A */
#define MCC_NOTADCONF               NOTADCONF           /* Specified board does not have A/D */
#define MCC_NOTMUXCONF              NOTMUXCONF          /* Specified board does not have thermocouple inputs */
#define MCC_BADPORTNUM              BADPORTNUM          /* Invalid port number specified */
#define MCC_BADCOUNTERDEVNUM        BADCOUNTERDEVNUM    /* Invalid counter device */
#define MCC_BADDADEVNUM             BADDADEVNUM         /* Invalid D/A device */
#define MCC_BADSAMPLEMODE           BADSAMPLEMODE       /* Invalid sampling mode option specified */
#define MCC_BADINT                  BADINT              /* Board configured for invalid interrupt level */
#define MCC_BADADCHAN               BADADCHAN           /* Invalid A/D channel Specified */
#define MCC_BADCOUNT                BADCOUNT            /* Invalid count specified */
#define MCC_BADCNTRCONFIG           BADCNTRCONFIG       /* invalid counter configuration specified */
#define MCC_BADDAVAL                BADDAVAL            /* Invalid D/A output value specified */
#define MCC_BADDACHAN               BADDACHAN           /* Invalid D/A channel specified */
#define MCC_ALREADYACTIVE           ALREADYACTIVE       /* A background process is already in progress */
#define MCC_PAGEOVERRUN             PAGEOVERRUN         /* DMA transfer crossed page boundary, may have gaps in data */
#define MCC_BADRATE                 BADRATE             /* Inavlid sampling rate specified */
#define MCC_COMPATMODE              COMPATMODE          /* Board switches set for "compatible" mode */
#define MCC_TRIGSTATE               TRIGSTATE           /* Incorrect intial trigger state D0 must=TTL low) */
#define MCC_ADSTATUSHUNG            ADSTATUSHUNG        /* A/D is not responding */
#define MCC_TOOFEW                  TOOFEW              /* Too few samples before trigger occurred */
#define MCC_OVERRUN                 OVERRUN             /* Data lost due to overrun, rate too high */
#define MCC_BADRANGE                BADRANGE            /* Invalid range specified */
#define MCC_NOPROGGAIN              NOPROGGAIN          /* Board does not have programmable gain */
#define MCC_BADFILENAME             BADFILENAME         /* Not a legal DOS filename */
#define MCC_DISKISFULL              DISKISFULL          /* Couldn't complete, disk is full */
#define MCC_COMPATWARN              COMPATWARN          /* Board is in compatible mode, so DMA will be used */
#define MCC_BADPOINTER              BADPOINTER          /* Invalid pointer (NULL) */
#define MCC_TOOMANYGAINS            TOOMANYGAINS        /* Too many gains */
#define MCC_RATEWARNING             RATEWARNING         /* Rate may be too high for interrupt I/O */
#define MCC_CONVERTDMA              CONVERTDMA          /* CONVERTDATA cannot be used with DMA I/O */
#define MCC_DTCONNECTERR            DTCONNECTERR        /* Board doesn't have DT Connect */
#define MCC_FORECONTINUOUS          FORECONTINUOUS      /* CONTINUOUS can only be used with BACKGROUND */
#define MCC_BADBOARDTYPE            BADBOARDTYPE        /* This function can not be used with this board */
#define MCC_WRONGDIGCONFIG          WRONGDIGCONFIG      /* Digital I/O is configured incorrectly */
#define MCC_NOTCONFIGURABLE         NOTCONFIGURABLE     /* Digital port is not configurable */
#define MCC_BADPORTCONFIG           BADPORTCONFIG       /* Invalid port configuration specified */
#define MCC_BADFIRSTPOINT           BADFIRSTPOINT       /* First point argument is not valid */
#define MCC_ENDOFFILE               ENDOFFILE           /* Attempted to read past end of file */
#define MCC_NOT8254CTR              NOT8254CTR          /* This board does not have an 8254 counter */
#define MCC_NOT9513CTR              NOT9513CTR          /* This board does not have a 9513 counter */
#define MCC_BADTRIGTYPE             BADTRIGTYPE         /* Invalid trigger type */
#define MCC_BADTRIGVALUE            BADTRIGVALUE        /* Invalid trigger value */
#define MCC_BADOPTION               BADOPTION           /* Invalid option specified for this function */
#define MCC_BADPRETRIGCOUNT         BADPRETRIGCOUNT     /* Invalid pre-trigger count sepcified */
#define MCC_BADDIVIDER              BADDIVIDER          /* Invalid fout divider value */
#define MCC_BADSOURCE               BADSOURCE           /* Invalid source value  */
#define MCC_BADCOMPARE              BADCOMPARE          /* Invalid compare value */
#define MCC_BADTIMEOFDAY            BADTIMEOFDAY        /* Invalid time of day value */
#define MCC_BADGATEINTERVAL         BADGATEINTERVAL     /* Invalid gate interval value */
#define MCC_BADGATECNTRL            BADGATECNTRL        /* Invalid gate control value */
#define MCC_BADCOUNTEREDGE          BADCOUNTEREDGE      /* Invalid counter edge value */
#define MCC_BADSPCLGATE             BADSPCLGATE         /* Invalid special gate value */
#define MCC_BADRELOAD               BADRELOAD           /* Invalid reload value */
#define MCC_BADRECYCLEFLAG          BADRECYCLEFLAG      /* Invalid recycle flag value */
#define MCC_BADBCDFLAG              BADBCDFLAG          /* Invalid BCD flag value */
#define MCC_BADDIRECTION            BADDIRECTION        /* Invalid count direction value */
#define MCC_BADOUTCONTROL           BADOUTCONTROL       /* Invalid output control value */
#define MCC_BADBITNUMBER            BADBITNUMBER        /* Invalid bit number */
#define MCC_NONEENABLED             NONEENABLED         /* None of the counter channels are enabled */
#define MCC_BADCTRCONTROL           BADCTRCONTROL       /* Element of control array not ENABLED/DISABLED */
#define MCC_BADEXPCHAN              BADEXPCHAN          /* Invalid EXP channel */
#define MCC_WRONGADRANGE            WRONGADRANGE        /* Wrong A/D range selected for cbtherm */
#define MCC_OUTOFRANGE              OUTOFRANGE          /* Temperature input is out of range */
#define MCC_BADTEMPSCALE            BADTEMPSCALE        /* Invalid temperate scale */
#define MCC_BADERRCODE              BADERRCODE          /* Invalid error code specified */
#define MCC_NOQUEUE                 NOQUEUE             /* Specified board does not have chan/gain queue */
#define MCC_CONTINUOUSCOUNT         CONTINUOUSCOUNT     /* CONTINUOUS can not be used with this count value */
#define MCC_UNDERRUN                UNDERRUN            /* D/A FIFO hit empty while doing output */
#define MCC_BADMEMMODE              BADMEMMODE          /* Invalid memory mode specified */
#define MCC_FREQOVERRUN             FREQOVERRUN         /* Measured frequency too high for gating interval */
#define MCC_NOCJCCHAN               NOCJCCHAN           /* Board does not have CJC chan configured */
#define MCC_BADCHIPNUM              BADCHIPNUM          /* Invalid chip number used with cbC9513Init */
#define MCC_DIGNOTENABLED           DIGNOTENABLED       /* Digital I/O not enabled */
#define MCC_CONVERT16BITS           CONVERT16BITS       /* CONVERT option not allowed with 16 bit A/D */
#define MCC_NOMEMBOARD              NOMEMBOARD          /* EXTMEMORY option requires memory board */
#define MCC_DTACTIVE                DTACTIVE            /* Memory I/O while DT Active */
#define MCC_NOTMEMCONF              NOTMEMCONF          /* Specified board is not a memory board */
#define MCC_ODDCHAN                 ODDCHAN             /* First chan in queue can not be odd */
#define MCC_CTRNOINIT               CTRNOINIT           /* Counter was not initialized */
#define MCC_NOT8536CTR              NOT8536CTR          /* Specified counter is not an 8536 */
#define MCC_FREERUNNING             FREERUNNING         /* A/D sampling is not timed */
#define MCC_INTERRUPTED             INTERRUPTED         /* Operation interrupted with CTRL-C */
#define MCC_NOSELECTORS             NOSELECTORS         /* Selector could not be allocated */
#define MCC_NOBURSTMODE             NOBURSTMODE         /* Burst mode is not supported on this board */
#define MCC_NOTWINDOWSFUNC          NOTWINDOWSFUNC      /* This function not available in Windows lib */
#define MCC_NOTSIMULCONF            NOTSIMULCONF        /* Not configured for simultaneous update */
#define MCC_EVENODDMISMATCH         EVENODDMISMATCH     /* Even channel in odd slot in the queue */
#define MCC_M1RATEWARNING           M1RATEWARNING       /* DAS16/M1 sample rate too fast */
#define MCC_NOTRS485                NOTRS485            /* Board is not an RS-485 board */
#define MCC_NOTDOSFUNC              NOTDOSFUNC          /* This function not avaliable in DOS */
#define MCC_RANGEMISMATCH           RANGEMISMATCH       /* Unipolar and Bipolar can not be used together in A/D que */
#define MCC_CLOCKTOOSLOW            CLOCKTOOSLOW        /* Sample rate too fast for clock jumper setting */
#define MCC_BADCALFACTORS           BADCALFACTORS       /* Cal factors were out of expected range of values */
#define MCC_BADCONFIGTYPE           BADCONFIGTYPE       /* Invalid configuration type information requested */
#define MCC_BADCONFIGITEM           BADCONFIGITEM       /* Invalid configuration item specified */
#define MCC_NOPCMCIABOARD           NOPCMCIABOARD       /* Can't acces PCMCIA board */
#define MCC_NOBACKGROUND            NOBACKGROUND        /* Board does not support background I/O */
#define MCC_STRINGTOOSHORT          STRINGTOOSHORT      /* String passed to cbGetBoardName is to short */
#define MCC_CONVERTEXTMEM           CONVERTEXTMEM       /* Convert data option not allowed with external memory */
#define MCC_BADEUADD                BADEUADD            /* e_ToEngUnits addition error */
#define MCC_DAS16JRRATEWARNING      DAS16JRRATEWARNING  /* use 10 MHz clock for rates > 125KHz */
#define MCC_DAS08TOOLOWRATE         DAS08TOOLOWRATE     /* DAS08 rate set too low for AInScan warning */
#define MCC_AMBIGSENSORONGP         AMBIGSENSORONGP     /* more than one sensor type defined for EXP-GP */
#define MCC_NOSENSORTYPEONGP        NOSENSORTYPEONGP    /* no sensor type defined for EXP-GP */
#define MCC_NOCONVERSIONNEEDED      NOCONVERSIONNEEDED  /* 12 bit board without chan tags - converted in ISR */
#define MCC_NOEXTCONTINUOUS         NOEXTCONTINUOUS     /* External memory cannot be used in CONTINUOUS mode */
#define MCC_INVALIDPRETRIGCONVERT   INVALIDPRETRIGCONVERT   /* cbAConvertPretrigData was called after failure in cbAPretrig */
#define MCC_BADCTRREG               BADCTRREG           /* bad arg to CLoad for 9513 */
#define MCC_BADTRIGTHRESHOLD        BADTRIGTHRESHOLD    /* Invalid trigger threshold specified in cbSetTrigger */
#define MCC_BADPCMSLOTREF           BADPCMSLOTREF       /* No PCM card in specified slot */
#define MCC_AMBIGPCMSLOTREF         AMBIGPCMSLOTREF     /* More than one MCC PCM card in slot */
#define MCC_BADSENSORTYPE           BADSENSORTYPE       /* Bad sensor type selected in Instacal */
#define MCC_DELBOARDNOTEXIST        DELBOARDNOTEXIST    /* tried to delete board number which doesn't exist */
#define MCC_NOBOARDNAMEFILE         NOBOARDNAMEFILE     /* board name file not found */
#define MCC_CFGFILENOTFOUND         CFGFILENOTFOUND     /* configuration file not found */
#define MCC_NOVDDINSTALLED          NOVDDINSTALLED      /* CBUL.386 device driver not installed */
#define MCC_NOWINDOWSMEMORY         NOWINDOWSMEMORY     /* No Windows memory available */
#define MCC_OUTOFDOSMEMORY          OUTOFDOSMEMORY      /* ISR data struct alloc failure */
#define MCC_OBSOLETEOPTION          OBSOLETEOPTION      /* Obsolete option for cbGetConfig/cbSetConfig */
#define MCC_NOPCMREGKEY             NOPCMREGKEY         /* No registry entry for this PCMCIA board */
#define MCC_NOCBUL32SYS             NOCBUL32SYS         /* CBUL32.SYS device driver is not loaded */
#define MCC_NODMAMEMORY             NODMAMEMORY         /* No DMA buffer available to device driver */
#define MCC_IRQNOTAVAILABLE         IRQNOTAVAILABLE     /* IRQ in being used by another device */
#define MCC_NOT7266CTR              NOT7266CTR          /* This board does not have an LS7266 counter */
#define MCC_BADQUADRATURE           BADQUADRATURE       /* Invalid quadrature specified */
#define MCC_BADCOUNTMODE            BADCOUNTMODE        /* Invalid counting mode specified */
#define MCC_BADENCODING             BADENCODING         /* Invalid data encoding specified */
#define MCC_BADINDEXMODE            BADINDEXMODE        /* Invalid index mode specified */
#define MCC_BADINVERTINDEX          BADINVERTINDEX      /* Invalid invert index specified */
#define MCC_BADFLAGPINS             BADFLAGPINS         /* Invalid flag pins specified */
#define MCC_NOCTRSTATUS             NOCTRSTATUS         /* This board does not support cbCStatus() */
#define MCC_NOGATEALLOWED           NOGATEALLOWED       /* Gating and indexing not allowed simultaneously */
#define MCC_NOINDEXALLOWED          NOINDEXALLOWED      /* Indexing not allowed in non-quadratue mode */
#define MCC_OPENCONNECTION          OPENCONNECTION      /* Temperature input has open connection */
#define MCC_BMCONTINUOUSCOUNT       BMCONTINUOUSCOUNT   /* Count must be integer multiple of packetsize for recycle mode. */
#define MCC_BADCALLBACKFUNC         BADCALLBACKFUNC     /* Invalid pointer to callback function passed as arg */
#define MCC_MBUSINUSE               MBUSINUSE           /* MetraBus in use */
#define MCC_MBUSNOCTLR              MBUSNOCTLR          /* MetraBus I/O card has no configured controller card */
#define MCC_BADEVENTTYPE            BADEVENTTYPE        /* Invalid event type specified for this board. */
#define MCC_ALREADYENABLED          ALREADYENABLED      /* An event handler has already been enabled for this event type */
#define MCC_BADEVENTSIZE            BADEVENTSIZE        /* Invalid event count specified. */
#define MCC_CANTINSTALLEVENT        CANTINSTALLEVENT	/* Unable to install event handler */
#define MCC_BADBUFFERSIZE           BADBUFFERSIZE       /* Buffer is too small for operation */
#define MCC_BADAIMODE               BADAIMODE           /* Invalid analog input mode(RSE, NRSE, or DIFF) */
#define MCC_BADSIGNAL               BADSIGNAL           /* Invalid signal type specified. */
#define MCC_BADCONNECTION           BADCONNECTION       /* Invalid connection specified. */
#define MCC_BADINDEX                BADINDEX            /* Invalid index specified, or reached end of internal connection list. */
#define MCC_NOCONNECTION            NOCONNECTION        /* No connection is assigned to specified signal. */
#define MCC_BADBURSTIOCOUNT         BADBURSTIOCOUNT     /* Count cannot be greater than the FIFO size for BURSTIO mode. */
#define MCC_DEADDEV                 DEADDEV             /* Device has stopped responding. Please check connections. */

#define MCC_INVALIDACCESS           INVALIDACCESS       /* Invalid access or privilege for specified operation */
#define MCC_UNAVAILABLE             UNAVAILABLE         /* Device unavailable at time of request. Please repeat operation. */
#define MCC_NOTREADY                NOTREADY            /* Device is not ready to send data. Please repeat operation. */
#define MCC_BITUSEDFORALARM         BITUSEDFORALARM     /* The specified bit is used for alarm. */
#define MCC_PORTUSEDFORALARM        PORTUSEDFORALARM    /* One or more bits on the specified port are used for alarm. */
#define MCC_PACEROVERRUN            PACEROVERRUN        /* Pacer overrun, external clock rate too fast. */
#define MCC_BADCHANTYPE             BADCHANTYPE         /* Invalid channel type specified. */
#define MCC_BADTRIGSENSE            BADTRIGSENSE        /* Invalid trigger sensitivity specified. */
#define MCC_BADTRIGCHAN             BADTRIGCHAN         /* Invalid trigger channel specified. */
#define MCC_BADTRIGLEVEL            BADTRIGLEVEL        /* Invalid trigger level specified. */
#define MCC_NOPRETRIGMODE           NOPRETRIGMODE       /* Pre-trigger mode is not supported for the specified trigger type. */
#define MCC_BADDEBOUNCETIME	        BADDEBOUNCETIME     /* Invalid debounce time specified. */
#define MCC_BADDEBOUNCETRIGMODE     BADDEBOUNCETRIGMODE /* Invalid debounce trigger mode specified. */
#define MCC_BADMAPPEDCOUNTER        BADMAPPEDCOUNTER    /* Invalid mapped counter specified. */
#define MCC_BADCOUNTERMODE          BADCOUNTERMODE      /* This function can not be used with the current mode of the specified counter. */
#define MCC_BADTCCHANMODE           BADTCCHANMODE       /* Single-Ended mode can not be used for temperature input. */
#define MCC_BADFREQUENCY            BADFREQUENCY        /* Invalid frequency specified. */
#define MCC_BADEVENTPARAM           BADEVENTPARAM       /* Invalid event parameter specified. */
#define MCC_NONETIFC                NONETIFC            /* No interface devices were found with required PAN ID and/or RF Channel. */
#define MCC_DEADNETIFC              DEADNETIFC          /* The interface device(s) with required PAN ID and RF Channel has failed. Please check connection. */
#define MCC_NOREMOTEACK             NOREMOTEACK         /* The remote device is not responding to commands and queries. Please check device. */
#define MCC_INPUTTIMEOUT            INPUTTIMEOUT		/* The device acknowledged the operation, but has not completed before the timeout. */
#define MCC_MISMATCHSETPOINTCOUNT	MISMATCHSETPOINTCOUNT		/* Number of Setpoints not equal to number of channels with setpoint flag set */
#define MCC_INVALIDSETPOINTLEVEL	INVALIDSETPOINTLEVEL		/* Setpoint Level is outside channel range */
#define MCC_INVALIDSETPOINTOUTPUTTYPE	INVALIDSETPOINTOUTPUTTYPE		/* Setpoint Output Type is invalid*/
#define MCC_INVALIDSETPOINTOUTPUTVALUE 	INVALIDSETPOINTOUTPUTVALUE		/* Setpoint Output Value is outside channel range */
#define MCC_INVALIDSETPOINTLIMITS		INVALIDSETPOINTLIMITS		/* Setpoint Comparison limit B greater than Limit A */
#define MCC_STRINGTOOLONG			STRINGTOOLONG       /* The string entered is too long for the operation and/or device. */
#define MCC_INVALIDLOGIN			INVALIDLOGIN        /* The account name and/or password entered is incorrect. */
#define MCC_SESSIONINUSE			SESSIONINUSE        /* The device session is already in use. */
#define MCC_NOEXTPOWER				NOEXTPOWER          /* External power is not connected. */
#define MCC_BADDUTYCYCLE			BADDUTYCYCLE        /* Invalid duty cycle specified. */
#define MCC_BADINITIALDELAY			BADINITIALDELAY     /* Invalid initial delay specified */
#define MCC_NOTEDSSENSOR			NOTEDSSENSOR        /* No TEDS sensor was detected on the specified channel. */
#define MCC_INVALIDTEDSSENSOR		INVALIDTEDSSENSOR   /* Connected TEDS sensor to the specified channel is not supported */
#define MCC_CALIBRATIONFAILED		CALIBRATIONFAILED   /* Calibration failed */
#define MCC_BITUSEDFORTERMINALCOUNTSTATUS   BITUSEDFORTERMINALCOUNTSTATUS   /* The specified bit is used for terminal count stauts. */
#define MCC_PORTUSEDFORTERMINALCOUNTSTATUS  PORTUSEDFORTERMINALCOUNTSTATUS    /* One or more bits on the specified port are used for terminal count stauts. */
#define MCC_BADEXCITATION			BADEXCITATION       /* Invalid excitation specified */
#define MCC_BADBRIDGETYPE			BADBRIDGETYPE       /* Invalid bridge type specified */
#define MCC_BADLOADVAL				BADLOADVAL          /* Invalid load value specified */
#define MCC_BADTICKSIZE				BADTICKSIZE         /* Invalid tick size specified */
#define MCC_BTHCONNECTIONFAILED		BTHCONNECTIONFAILED	/* Bluetooth connection failed */
#define MCC_INVALIDBTHFRAME			INVALIDBTHFRAME     /* Invalid Bluetooth frame */
#define	MCC_BADTRIGEVENT			BADTRIGEVENT        /* Invalid trigger event specified */
#define MCC_NETCONNECTIONFAILED		NETCONNECTIONFAILED	/* Network connection failed */
#define MCC_DATASOCKETCONNECTIONFAILED		DATASOCKETCONNECTIONFAILED	/* Data socket connection failed */
#define MCC_INVALIDNETFRAME			INVALIDNETFRAME     /* Invalid Network frame */
#define MCC_NETTIMEOUT				NETTIMEOUT          /* Network device did not respond within expected time */
#define MCC_NETDEVNOTFOUND			NETDEVNOTFOUND      /* Network device not found */
#define MCC_INVALIDCONNECTIONCODE	INVALIDCONNECTIONCODE	/* Invalid connection code */
#define MCC_CONNECTIONCODEIGNORED	CONNECTIONCODEIGNORED	/* Connection code ignored */
#define MCC_NETDEVINUSE				NETDEVINUSE         /* Network device already in use */
#define MCC_NETDEVINUSEBYANOTHERPROC	NETDEVINUSEBYANOTHERPROC	/* Network device already in use by another process */
#define MCC_SOCKETDISCONNECTED		SOCKETDISCONNECTED	/* Socket Disconnected */
#define MCC_BOARDNUMINUSE			BOARDNUMINUSE       /* Board Number already in use */
#define MCC_DEVALREADYCREATED		DEVALREADYCREATED	/* Specified DAQ device already created */
#define MCC_BOARDNOTEXIST			BOARDNOTEXIST       /* Tried to release a board which doesn't exist */
#define MCC_INVALIDNETHOST			INVALIDNETHOST      /* Invalid host specified */
#define MCC_INVALIDNETPORT			INVALIDNETPORT      /* Invalid port specified */
#define MCC_INVALIDIFC				INVALIDIFC          /* Invalid interface specified */
#define MCC_INVALIDAIINPUTMODE		INVALIDAIINPUTMODE	/* Invalid input mode specified */
#define MCC_AIINPUTMODENOTCONFIGURABLE		AIINPUTMODENOTCONFIGURABLE    /* Input mode not configurable */
#define MCC_INVALIDEXTPACEREDGE		INVALIDEXTPACEREDGE	/* Invalid external pacer edge */
#define MCC_CMREXCEEDED				CMREXCEEDED         /* Common-mode voltage range exceeded */


#else

#define MCC_ERRSTRLEN               ERR_MSG_LEN

#define MCC_NOERRORS                ERR_NO_ERROR
#define MCC_UNHANDLED_EXCEPTION     ERR_UNHANDLED_EXCEPTION
#define MCC_BADBOARD                ERR_BAD_DEV_HANDLE
#define MCC_NOTDIGITALCONF          ERR_BAD_DEV_TYPE
#define MCC_NOTCOUNTERCONF          ERR_BAD_DEV_TYPE
#define MCC_NOTDACONF               ERR_BAD_DEV_TYPE
#define MCC_NOTADCONF               ERR_BAD_DEV_TYPE
#define MCC_NOTMUXCONF              ERR_BAD_DEV_TYPE
#define MCC_BADBOARDTYPE            ERR_BAD_DEV_TYPE
//    ERR_USB_DEV_NO_PERMISSION		= 4,
//    ERR_USB_INTERFACE_CLAIMED 		= 5,
//    ERR_DEV_NOT_FOUND 				= 6,
//    ERR_DEV_NOT_CONNECTED 			= 7,
#define MCC_DEADDEV                 ERR_DEAD_DEV
//    ERR_BAD_BUFFER_SIZE 			= 9,
//    ERR_BAD_BUFFER 					= 10,

    /** Invalid memory type */
//    ERR_BAD_MEM_TYPE 				= 11,

    /** Invalid memory region */
//    ERR_BAD_MEM_REGION 				= 12,

#define MCC_BADRANGE                ERR_BAD_RANGE
#define MCC_BADADCHAN               ERR_BAD_AI_CHAN
#define MCC_BADAIMODE               ERR_BAD_INPUT_MODE
#define MCC_ALREADYACTIVE           ERR_ALREADY_ACTIVE
#define MCC_BADTRIGTYPE             ERR_BAD_TRIG_TYPE
#define MCC_OVERRUN                 ERR_OVERRUN
#define MCC_UNDERRUN                ERR_UNDERRUN

    /** Operation timed out */
//    ERR_TIMEDOUT					= 20,

#define MCC_BADSAMPLEMODE           ERR_BAD_OPTION
#define MCC_BADRATE                ERR_BAD_RATE

    /** Sample count cannot be greater than FIFO size for BURSTIO scans */
//    ERR_BAD_BURSTIO_COUNT			= 23,

    /** Configuration not supported */
//    ERR_CONFIG_NOT_SUPPORTED		= 24,

#define MCC_BADCONFIGTYPE           ERR_BAD_CONFIG_VAL

    /** Invalid analog input channel type specified */
//    ERR_BAD_AI_CHAN_TYPE			= 26,

    /** ADC overrun occurred */
//    ERR_ADC_OVERRUN					= 27,

    /** Invalid thermocouple type specified */
//    ERR_BAD_TC_TYPE					= 28,

    /** Invalid unit specified */
//    ERR_BAD_UNIT					= 29,

    /** Invalid queue size */
//    ERR_BAD_QUEUE_SIZE				= 30,

#define MCC_BADCONFIGITEM           ERR_BAD_CONFIG_ITEM

    /** Invalid info item specified */
//    ERR_BAD_INFO_ITEM				= 32,

    /** Invalid flag specified */
//    ERR_BAD_FLAG					= 33,

    /** Invalid sample count specified */
//    ERR_BAD_SAMPLE_COUNT			= 34,

    /** Internal error */
//    ERR_INTERNAL					= 35,

    /** Invalid coupling mode */
//    ERR_BAD_COUPLING_MODE			= 36,

    /** Invalid sensor sensitivity */
//    ERR_BAD_SENSOR_SENSITIVITY		= 37,

    /** Invalid IEPE mode */
//    ERR_BAD_IEPE_MODE				= 38,

    /** Invalid channel queue specified */
//    ERR_BAD_AI_CHAN_QUEUE			= 39,

    /** Invalid gain queue specified */
//    ERR_BAD_AI_GAIN_QUEUE			= 40,

    /** Invalid mode queue specified */
//    ERR_BAD_AI_MODE_QUEUE			= 41,

    /** FPGA file not found */
//    ERR_FPGA_FILE_NOT_FOUND			= 42,

    /** Unable to read FPGA file */
//    ERR_UNABLE_TO_READ_FPGA_FILE	= 43,

    /** FPGA not loaded */
//    ERR_NO_FPGA						= 44,

    /** Invalid argument */
//    ERR_BAD_ARG						= 45,

    /** Minimum slope value reached */
//    ERR_MIN_SLOPE_VAL_REACHED		= 46,

    /** Maximum slope value reached */
//    ERR_MAX_SLOPE_VAL_REACHED		= 47,

    /** Minimum offset value reached */
//    ERR_MIN_OFFSET_VAL_REACHED		= 48,

    /** Maximum offset value reached */
//    ERR_MAX_OFFSET_VAL_REACHED		= 49,

//    ERR_BAD_PORT_TYPE
#define MCC_WRONGDIGCONFIG          ERR_WRONG_DIG_CONFIG
#define MCC_BADBITNUMBER            ERR_BAD_BIT_NUM					= 52,

    /** Invalid port value specified */
//    ERR_BAD_PORT_VAL				= 53,

    /** Invalid re-trigger count */
//    ERR_BAD_RETRIG_COUNT			= 54,

#define MCC_BADDACHAN                   ERR_BAD_AO_CHAN
#define MCC_BADDAVAL                    ERR_BAD_DA_VAL

    /** Invalid timer specified */
//    ERR_BAD_TMR						= 57,

    /** Invalid frequency specified */
//    ERR_BAD_FREQUENCY				= 58,

    /** Invalid duty cycle specified */
//    ERR_BAD_DUTY_CYCLE				= 59,

    /** Invalid initial delay specified */
//    ERR_BAD_INITIAL_DELAY			= 60,

#define MCC_BADCOUNTERDEVNUM        ERR_BAD_CTR

    /** Invalid counter value specified */
//    ERR_BAD_CTR_VAL					= 62,

    /** Invalid DAQ input channel type specified */
//    ERR_BAD_DAQI_CHAN_TYPE			= 63,

    /** Invalid number of channels specified */
//    ERR_BAD_NUM_CHANS				= 64,

    /** Invalid counter register specified */
//    ERR_BAD_CTR_REG					= 65,

    /** Invalid counter measurement type specified */
//    ERR_BAD_CTR_MEASURE_TYPE		= 66,

#define MCC_BADCOUNTMODE            ERR_BAD_CTR_MEASURE_MODE

    /** Invalid debounce time specified */
//    ERR_BAD_DEBOUNCE_TIME			= 68,

    /** Invalid debounce mode specified */
//    ERR_BAD_DEBOUNCE_MODE			= 69,

    /** Invalid edge detection mode specified */
//    ERR_BAD_EDGE_DETECTION			= 70,

    /** Invalid tick size specified */
//    ERR_BAD_TICK_SIZE				= 71,

    /** Invalid DAQ output channel type specified */
//    ERR_BAD_DAQO_CHAN_TYPE			= 72,

    /** No connection established */
//    ERR_NO_CONNECTION_ESTABLISHED	= 73,

    /** Invalid event type specified */
//    ERR_BAD_EVENT_TYPE				= 74,

    /** An event handler has already been enabled for this event type */
//    ERR_EVENT_ALREADY_ENABLED		= 75,

    /** Invalid event parameter specified */
//    ERR_BAD_EVENT_PARAMETER			= 76,

    /** Invalid callback function specified */
//    ERR_BAD_CALLBACK_FUCNTION		= 77,

    /** Invalid memory address */
//    ERR_BAD_MEM_ADDRESS				= 78,

    /** Memory access denied */
//    ERR_MEM_ACCESS_DENIED			= 79,

    /** Device is not available at time of request */
//    ERR_DEV_UNAVAILABLE				= 80,

    /** Re-ger option is not supported for the specified trigger type */
//    ERR_BAD_RETRIG_TRIG_TYPE		= 81,

    /** This function cannot be used with this version of the device */
//    ERR_BAD_DEV_VER 				= 82,

    /** This digital operation is not supported on the specified port */
//    ERR_BAD_DIG_OPERATION			= 83,

#define MCC_BADPORTNUM              ERR_BAD_PORT_INDEX
#define MCC_OPENCONNECTION          ERR_OPEN_CONNECTION

    /** Device is not ready to send data */
//    ERR_DEV_NOT_READY				= 86,

#define MCC_PACEROVERRUN            ERR_PACER_OVERRUN

    /** Invalid trigger channel specified */
//    ERR_BAD_TRIG_CHANNEL			= 88,

#define MCC_BADTRIGVALUE            ERR_BAD_TRIG_LEVEL				= 89,

    /** Invalid channel order */
//    ERR_BAD_CHAN_ORDER				= 90,

#define MCC_OUTOFRANGE              ERR_TEMP_OUT_OF_RANGE
#define MCC_BADTRIGTHRESHOLD        ERR_TRIG_THRESHOLD_OUT_OF_RANGE	= 92,

//    ERR_INCOMPATIBLE_FIRMWARE 		= 93

#endif // MV_WINDOWS

#endif // MVERRORMAP_H
