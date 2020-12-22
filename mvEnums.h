#ifndef MVENUMS_H
#define MVENUMS_H

#define MV_WIN      1
#define MV_LINUX    2
#define MV_RPI      3

typedef enum
{
    FORM_NONE    =-1,
    FORM_DISC    =0,
    FORM_AIN     =1,
    FORM_AOUT    =2,
    FORM_AIO     =1,
    FORM_DIN     =3,
    FORM_DOUT    =4,
    FORM_DIO     =3,
    FORM_CTR     =5,
    FORM_MISC    =6,
    FORM_CONF    =7,
    FORM_HIST    =8
}FormTypes;

typedef enum
{
    MENU_RANGE  = 1,
    MENU_PLOT   = 2
}MenuTypes;

typedef enum
{
    DevParams   = 1,
    AInParams   = 2

}NameParams;

typedef enum
{
    IPARAM_RANGE            = 1,
    IPARAM_AINMODE          = 2,
    IPARAM_FLAGS            = 3,
    IPARAM_OPTIONS          = 4,
    IPARAM_INPUTMODE        = 5,

    IPARAM_WAITDATA         = 6,
    IPARAM_GETDATA          = 7,

    IPARAM_AOUTRANGE        = 20,
    IPARAM_AOFLAGS          = 21,

    IPARAM_PLOTTYPE         = 100,
    IPARAM_FUNCTYPE         = 101
}IntParams;

#define MCC_SETQUEUE        777

typedef enum {
    tjNone,
    tjSplash,
    tjStart,
    tjChildStatus,
    tjInitVars
}TimerJob;

typedef enum
{
    UL_AIN              = 1,
    UL_AINSCAN          = 2,
    UL_LOAD_QUEUE       = 3,
    UL_AIN_SET_TRIGGER  = 4,
    UL_DAQ_INSCAN       = 5,
    UL_TIN              = 6,
    UL_TINARRAY         = 7,
    UL_AOUT             = 10,
    UL_AOUTSCAN         = 11,
    UL_DAQ_OUTSCAN      = 12,
    UL_DCONFIG_PORT     = 20,
    UL_DCONFIG_BIT      = 21,
    UL_DIN              = 22,
    UL_DIN32            = 23,
    UL_DINARRAY         = 24,
    UL_DBITIN           = 25,
    UL_DINSCAN          = 26,
    UL_GET_INFO         = 101,
    UL_GET_CONF         = 102,
    UL_SET_CONF         = 103
}MvFunctionTypes;


typedef enum
{
    GRP_LIBRARY,
    GRP_DEVICE,
    GRP_AIN,
    GRP_AOUT,
    GRP_DIO,
    GRP_CTR,
    GRP_TMR,
    GRP_DAQIN,
    GRP_DAQOUT,
    GRP_MEMORY
}InfoGroup;

#endif // MVENUMS_H
