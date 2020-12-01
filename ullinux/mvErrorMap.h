#ifndef MVERRORMAP_H
#define MVERRORMAP_H

//#include "ulPlatform.h"
#include "libenum.h"

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
#define MCC_BADRATE                 ERR_BAD_RATE

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

#endif // MVERRORMAP_H
