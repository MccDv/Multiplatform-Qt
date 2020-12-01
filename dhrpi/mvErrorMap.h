#ifndef MVERRORMAP_H
#define MVERRORMAP_H

#include "daqhats.h"
#include "libenum.h"

#define MCC_ERRSTRLEN               ERR_MSG_LEN

#define MCC_NOERRORS                RESULT_SUCCESS
#define MCC_BADBOARD                RESULT_INVALID_DEVICE
#define MCC_NOTDIGITALCONF          RESULT_BAD_PARAMETER
#define MCC_NOTCOUNTERCONF          RESULT_BAD_PARAMETER
#define MCC_NOTDACONF               RESULT_BAD_PARAMETER
#define MCC_NOTADCONF               RESULT_BAD_PARAMETER
#define MCC_NOTMUXCONF              RESULT_BAD_PARAMETER
#define MCC_BADBOARDTYPE            ERR_BAD_DEV_TYPE
//    ERR_USB_DEV_NO_PERMISSION		= 4,
//    ERR_USB_INTERFACE_CLAIMED 		= 5,
//    ERR_DEV_NOT_FOUND 				= 6,
//    ERR_DEV_NOT_CONNECTED 			= 7,
#define MCC_DEADDEV                 RESULT_COMMS_FAILURE
//    ERR_BAD_BUFFER_SIZE 			= 9,
//    ERR_BAD_BUFFER 					= 10,

    /** Invalid memory type */
//    ERR_BAD_MEM_TYPE 				= 11,

    /** Invalid memory region */
//    ERR_BAD_MEM_REGION 				= 12,

#define MCC_BADRANGE                RESULT_BAD_PARAMETER
#define MCC_BADADCHAN               RESULT_BAD_PARAMETER
#define MCC_BADAIMODE               RESULT_BAD_PARAMETER
#define MCC_ALREADYACTIVE           RESULT_BUSY
#define MCC_BADTRIGTYPE             ERR_BAD_TRIG_TYPE
#define MCC_OVERRUN                 RESULT_TIMEOUT
#define MCC_UNDERRUN                RESULT_TIMEOUT

    /** Operation timed out */
//    ERR_TIMEDOUT					= 20,

#define MCC_BADSAMPLEMODE           RESULT_BAD_PARAMETER
#define MCC_BADRATE                 RESULT_BAD_PARAMETER

    /** Sample count cannot be greater than FIFO size for BURSTIO scans */
//    ERR_BAD_BURSTIO_COUNT			= 23,

    /** Configuration not supported */
//    ERR_CONFIG_NOT_SUPPORTED		= 24,

#define MCC_BADCONFIGTYPE           RESULT_BAD_PARAMETER

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

#define MCC_BADCONFIGITEM           RESULT_BAD_PARAMETER

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
#define MCC_WRONGDIGCONFIG          RESULT_BAD_PARAMETER
#define MCC_BADBITNUMBER            RESULT_BAD_PARAMETER

    /** Invalid port value specified */
//    ERR_BAD_PORT_VAL				= 53,

    /** Invalid re-trigger count */
//    ERR_BAD_RETRIG_COUNT			= 54,

#define MCC_BADDACHAN                   RESULT_BAD_PARAMETER
#define MCC_BADDAVAL                    RESULT_BAD_PARAMETER

    /** Invalid timer specified */
//    ERR_BAD_TMR						= 57,

    /** Invalid frequency specified */
//    ERR_BAD_FREQUENCY				= 58,

    /** Invalid duty cycle specified */
//    ERR_BAD_DUTY_CYCLE				= 59,

    /** Invalid initial delay specified */
//    ERR_BAD_INITIAL_DELAY			= 60,

#define MCC_BADCOUNTERDEVNUM        RESULT_BAD_PARAMETER

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

#define MCC_BADCOUNTMODE            RESULT_BAD_PARAMETER

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

#define MCC_BADPORTNUM              RESULT_BAD_PARAMETER
#define MCC_OPENCONNECTION          RESULT_BAD_PARAMETER

    /** Device is not ready to send data */
//    ERR_DEV_NOT_READY				= 86,

#define MCC_PACEROVERRUN            RESULT_BAD_PARAMETER

    /** Invalid trigger channel specified */
//    ERR_BAD_TRIG_CHANNEL			= 88,

#define MCC_BADTRIGVALUE            RESULT_BAD_PARAMETER

    /** Invalid channel order */
//    ERR_BAD_CHAN_ORDER				= 90,

#define MCC_OUTOFRANGE              RESULT_BAD_PARAMETER
#define MCC_BADTRIGTHRESHOLD        RESULT_BAD_PARAMETER

//    ERR_INCOMPATIBLE_FIRMWARE 		= 93

#endif // MVERRORMAP_H
