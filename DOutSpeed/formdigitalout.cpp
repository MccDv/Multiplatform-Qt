#include "formdigitalout.h"
#include "ui_formdigitalout.h"

FormDigitalOut::FormDigitalOut(QWidget *parent) :
    FormMvDevice(parent),
    ui(new Ui::FormDigitalOut)
{
    ui->setupUi(this);

    connect(this, SIGNAL(deviceChanged()), this, SLOT(updateDevice()));
    connect(ui->cmdFlashLED, SIGNAL(clicked(bool)), this, SLOT(flashLED()));
    connect(ui->cmdStart, SIGNAL(clicked(bool)), this, SLOT(cmdStartClicked()));
    callClassConstructors();
}

FormDigitalOut::~FormDigitalOut()
{
    delete digitalFuncs;
    delete ui;
}

void FormDigitalOut::flashLED()
{
    QString params;

    libMiscFunctions->mccFlashLed(params, mDevHandle, 4);
}

void FormDigitalOut::cmdStartClicked()
{
    QString params, msg, formatString;
    int err, iterations;
    bool spanPorts;
    double outputRate, elapsedTime, rateDivisor;
    QElapsedTimer funcTimer;

    spanPorts = false;
    ui->cmdStart->setEnabled(false);
    ui->txtResult->clear();
    iterations = ui->leRateEstimate->text().toInt();
    elapsedTime = 0;

    mDataValHigh = 255;
    mDataValLow = 0;

    if (mbDoBits) {
        err = digitalFuncs->mccDOut(params, mDevHandle, mPortNum, mDataValLow);
    } else {
        if (spanPorts) {
           /*ReDim OutArrayLow(mlNumArrayPorts - 1) As Long
           ReDim OutArrayHigh(mlNumArrayPorts - 1) As Long
           For arrayElement& = 0 To mlNumArrayPorts - 1
              OutArrayLow(arrayElement&) = mnDataValLow
              OutArrayHigh(arrayElement&) = mnDataValHigh
           Next
           LastArrayPort& = mlPortNum + (mlNumArrayPorts - 1)
           ULStat& = cbDOutArray(mlBoardNum, mlPortNum, _
              LastArrayPort&, OutArrayLow(0))
           If ULStat& <> 0 Then
              ErrMessage$ = GetULError(ULStat&)
              txtResult.Text = ErrMessage$
              Exit Sub
           End If
           StartTime! = Timer
           For i& = 0 To Iterations&
              ULStat& = cbDOutArray(mlBoardNum, mlPortNum, _
                 LastArrayPort&, OutArrayHigh(0))
              ULStat& = cbDOutArray(mlBoardNum, mlPortNum, _
                 LastArrayPort&, OutArrayLow(0))
           Next
           elapsedTime! = (Timer - StartTime!) / 2 */
        } else {
            err = digitalFuncs->mccDOut(params, mDevHandle, mPortNum, mDataValLow);
            if (err != MCC_NOERRORS) {
                msg = libMiscFunctions->mccGetUlErrorText(err);
                ui->lblStatus->setText(msg);
                return;
            }
            funcTimer.start();
            for (int i = 0; i < iterations; i++) {
                err = digitalFuncs->mccDOut(params, mDevHandle, mPortNum, mDataValHigh);
                err = digitalFuncs->mccDOut(params, mDevHandle, mPortNum, mDataValLow);
            }
            elapsedTime = (funcTimer.elapsed()) / 2;
        }
    }
    ui->cmdStart->setEnabled(true);
    outputRate = 1 / (elapsedTime / iterations);
    formatString = "Hz";
    rateDivisor = 1.00;
    if (outputRate > 999) {
        formatString = "kHz";
        rateDivisor = 1000.0;
     }
     ui->txtResult->setText(QString("Update rate: %1" + formatString).arg(outputRate / rateDivisor));
}

void FormDigitalOut::updateIntValue(int paramEnum, int paramValue)
{
    switch (paramEnum) {
    case IPARAM_FUNCTYPE:
        mCurFunction = paramValue;
        //setUiForFunction();
        break;
    case IPARAM_RANGE:
        if (paramValue == MCC_SETQUEUE)
            //showQueueConfig();
            break;
        else {
            mRange = (MccRange)paramValue;
            //curRangeVolts = libTestUtils->getRangeNomo(mRange);
            //ui->lblRange0->setText(curRangeVolts);
        }
        break;
    case IPARAM_AINMODE:
        //mAiMode = (AiInputMode)paramValue;
        break;
    case IPARAM_FLAGS:
        //mAiFlags = (AInFlag)paramValue;
        break;
    case IPARAM_OPTIONS:
        mCurOptions = paramValue;
        //ui->lblFunction->setText("Options set to: " + libTestUtils->getOptionNames(mCurOptions));
        break;
    case IPARAM_WAITDATA:
        //mTiFlags = TIN_FF_DEFAULT;
        //if (paramValue)
        //    mTiFlags = TIN_FF_WAIT_FOR_NEW_DATA;
        break;
    case IPARAM_PLOTTYPE:
        //enablePlot(paramValue);
        break;
    default:
        break;
    }
    //cmdStopClicked();
}

void FormDigitalOut::updateDevice()
{
    if (mDevHandle == -1) {
        ui->fraMain->setEnabled(false);
        return;
    }
    ui->fraMain->setEnabled(true);
    getPortType();
}

void FormDigitalOut::getPortType()
{
    int err;
    bool overBit;
    bool arrayEnabled;
    int trimVal, devType, devNum, numDevs, numBits;
    int prevDevType, curLast, curFirst, offset;
    long long infoValue;
    QString sPortList, params, bitList;
    LibUtilities *libUtils;

    prevDevType = 0;
    arrayEnabled = ui->chkArray->isChecked();
    if (arrayEnabled) {
        mTotalBits = 0;
        err = libMiscFunctions->mccDioGetInfo(params, mDevHandle, MCC_DIG_NUMDEVS, 0, infoValue);
        numDevs = infoValue;
        for (devNum = mPortIndex; devNum < numDevs; devNum++) {
            err = libMiscFunctions->mccDioGetInfo(params, mDevHandle, MCC_DIG_DEVTYPE, mPortIndex, infoValue);
            devType = infoValue;
            err = libMiscFunctions->mccDioGetInfo(params, mDevHandle, MCC_DIG_NUMBITS, devNum, infoValue);
            numBits = infoValue;
            mTotalBits += numBits;
            if (prevDevType > 0) {
                mNumArrayPorts++;
                if (mNumBits != numBits) {
                    mNumArrayPorts = 1;
                    break;
                }
                if (!mbDoBits) {
                    sPortList = sPortList + ", " + libUtils->getDioPortTypeName(devType);
                } else {
                    ui->txtLastBit->setText(QString("%1").arg(mTotalBits - 1));
                }
            } else {
                mNumArrayPorts = 1;
                mNumBits = numBits;
                prevDevType = devType;
                sPortList = libUtils->getDioPortTypeName(devType);
            }
        }
        msPortList = sPortList;
    } else {
        err = libMiscFunctions->mccDioGetInfo(params, mDevHandle, MCC_DIG_DEVTYPE, mPortIndex, infoValue);
        devType = infoValue;
        if (err != MCC_NOERRORS) {
            msPortList = "Invalid Port";
            ui->cmdStart->setEnabled(false);
        } else {
            mPortNum = devType;
            msPortList = libUtils->getDioPortTypeName(devType);
            ui->cmdStart->setEnabled(true);
        }
        err = libMiscFunctions->mccDioGetInfo(params, mDevHandle, MCC_DIG_NUMBITS, mPortIndex, infoValue);
        numBits = infoValue;
        curLast = ui->txtLastBit->text().toInt();
        overBit = !(curLast < numBits);
        mLastBit = numBits - 1;
        ui->txtLastBit->setText(QString("%1").arg(mLastBit));
        curFirst = ui->txtFirstBit->text().toInt();
        if (curFirst > mLastBit) {
            mFirstBit = 0;
            ui->txtFirstBit->setText("0");
        }
    }

    offset = 0;
    //offset = GetBitOffset(mDevHandle, mPortIndex);
    mFirstBit = ui->txtFirstBit->text().toInt() + offset;
    mLastBit = ui->txtLastBit->text().toInt() + offset;
    bitList = "";
    if (mbDoBits)
        bitList = QString(" (Bit %1 to %2)").arg(mFirstBit).arg(mLastBit);
    ui->lblPortType->setText(msPortList + bitList);

}

void FormDigitalOut::callClassConstructors()
{
    digitalFuncs = new LibDigital();
}
