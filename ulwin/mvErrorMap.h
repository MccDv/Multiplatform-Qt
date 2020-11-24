#ifndef MVERRORMAP_H
#define MVERRORMAP_H

//#include "ulPlatform.h"

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

#endif // MVERRORMAP_H
