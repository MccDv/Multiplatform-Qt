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
    connect(ui->optPort, SIGNAL(toggled(bool)), this, SLOT(optPortBitClicked()));
    callClassConstructors();

    ui->txtFirstBit->setVisible(false);
    ui->txtLastBit->setVisible(false);
    ui->lblFirstBit->setVisible(false);
    ui->lblLastBit->setVisible(false);
    ui->cmbBoardSelect->setVisible(false);
    ui->chkErrors->setVisible(false);
    ui->lblBoardNumber->setVisible(false);
}

FormDigitalOut::~FormDigitalOut()
{
    delete digitalFuncs;
    delete libMiscFunctions;
    delete ui;
}

void FormDigitalOut::flashLED()
{
    QString params;
    int err;

    err = libMiscFunctions->mccFlashLed(params, mDevHandle, 4);
    if (err != MCC_NOERRORS)
        ui->lblStatus->setText(libMiscFunctions->mccGetUlErrorText(err));
}

void FormDigitalOut::cmdStartClicked()
{
    QString params, msg, formatString;
    int err, iterations, bitPort, curBit;
    int numBits, i, arrayElement, lastArrayPort;
    bool spanPorts;
    double outputRate, elapsedTime, rateDivisor;
    double rateInSeconds;
    QElapsedTimer funcTimer;

    numBits = (mLastBit - mFirstBit) + 1;
    spanPorts = false;
    ui->cmdStart->setEnabled(false);
    ui->txtResult->clear();
    iterations = ui->leRateEstimate->text().toInt();
    elapsedTime = 0;

    if (mbDoBits) {
        bitPort = MCC_FIRSTPORTA;
        if (mPortNum < 10)
            bitPort = MCC_AUXPORT;
        err = digitalFuncs->mccDBitOut(params, mDevHandle, bitPort, mFirstBit, mDataValLow);
        if (err != MCC_NOERRORS) {
            ui->lblStatus->setText(libMiscFunctions->mccGetUlErrorText(err));
            return;
        }
        funcTimer.start();
        for (i = 0; i < iterations; i++) {
            for (curBit = mFirstBit; curBit <= mLastBit; curBit++) {
                err = digitalFuncs->mccDBitOut(params, mDevHandle, bitPort, curBit, 1);
            }
            for (curBit = mFirstBit; curBit <= mLastBit; curBit++) {
                err = digitalFuncs->mccDBitOut(params, mDevHandle, bitPort, curBit, 0);
            }
        }
        elapsedTime = (funcTimer.elapsed()) / (numBits * 2);
    } else {
        if (spanPorts) {
            unsigned long long  outArrayHigh[mNumArrayPorts];
            unsigned long long  outArrayLow[mNumArrayPorts];
            for (arrayElement = 0; arrayElement < mNumArrayPorts; arrayElement++) {
                outArrayLow[arrayElement] = mDataValLow;
                outArrayHigh[arrayElement] = mDataValHigh;
            }
            params = msProductID;
            lastArrayPort = mPortNum + mNumArrayPorts + 1;
            err = digitalFuncs->mccDOutArray(params, mDevHandle, mPortNum, lastArrayPort, outArrayLow);
            if (err != MCC_NOERRORS)
                return;
            funcTimer.start();
            for (i = 0; i < iterations; i++) {
                err = digitalFuncs->mccDOutArray(params, mDevHandle, mPortNum, lastArrayPort, outArrayHigh);
                err = digitalFuncs->mccDOutArray(params, mDevHandle, mPortNum, lastArrayPort, outArrayLow);
            }
            elapsedTime = funcTimer.elapsed() / 2;
        } else {
            params = msProductID;
            err = digitalFuncs->mccDOut(params, mDevHandle, mPortNum, mDataValLow);
            if (err != MCC_NOERRORS) {
                msg = libMiscFunctions->mccGetUlErrorText(err);
                ui->lblStatus->setText(msg);
                return;
            }
            funcTimer.start();
            for (int i = 0; i < iterations; i++) {
                params = msProductID;
                digitalFuncs->mccDOut(params, mDevHandle, mPortNum, mDataValHigh);
                params = msProductID;
                digitalFuncs->mccDOut(params, mDevHandle, mPortNum, mDataValLow);
            }
            elapsedTime = (funcTimer.elapsed()) / 2;
        }
    }
    rateInSeconds = elapsedTime /1000;
    ui->cmdStart->setEnabled(true);
    outputRate = 1 / (rateInSeconds / iterations);
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
        break;
    case IPARAM_RANGE:
        break;
    case IPARAM_AINMODE:
        break;
    case IPARAM_FLAGS:
        break;
    case IPARAM_OPTIONS:
        mCurOptions = paramValue;
        break;
    case IPARAM_WAITDATA:
        break;
    case IPARAM_PLOTTYPE:
        break;
    default:
        break;
    }
}

void FormDigitalOut::updateDevice()
{
    bool addBoard;

    if (mDevHandle == -1) {
        ui->fraMain->setEnabled(false);
        return;
    }
    ui->fraMain->setEnabled(true);
    addBoard = checkForDigital();
    if (addBoard) {
        ui->cmdStart->setEnabled(true);
        getPortType();
        if (mNumPorts > 0) {
            configureOutputs(true);
            configureData();
        }
    }
}

void FormDigitalOut::getPortType()
{
    int err;
    bool arrayEnabled;
    int devType, devNum, numDevs, numBits;
    int prevDevType, curFirst, offset;
    long long infoValue;
    QString sPortList, params, bitList;

    prevDevType = 0;
    arrayEnabled = ui->chkArray->isChecked();
    ui->lblPortType->clear();

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
                    sPortList = sPortList + ", " + libTestUtils->getDioPortTypeName(devType);
                } else {
                    ui->txtLastBit->setText(QString("%1").arg(mTotalBits - 1));
                }
            } else {
                mNumArrayPorts = 1;
                mNumBits = numBits;
                prevDevType = devType;
                sPortList = libTestUtils->getDioPortTypeName(devType);
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
            msPortList = libTestUtils->getDioPortTypeName(devType);
            ui->cmdStart->setEnabled(true);
        }
        err = libMiscFunctions->mccDioGetInfo(params, mDevHandle, MCC_DIG_NUMBITS, mPortIndex, infoValue);
        numBits = infoValue;
        mLastBit = numBits - 1;
        ui->txtLastBit->setText(QString("%1").arg(mLastBit));
        curFirst = ui->txtFirstBit->text().toInt();
        if (curFirst > mLastBit) {
            mFirstBit = 0;
            ui->txtFirstBit->setText("0");
        }
    }

    offset = 0;
    offset = digitalUtils->getBitOffset(mDevHandle, mPortIndex);
    mFirstBit = ui->txtFirstBit->text().toInt() + offset;
    mLastBit = ui->txtLastBit->text().toInt() + offset;
    bitList = "";
    if (mbDoBits)
        bitList = QString(" (Bit %1 to %2)").arg(mFirstBit).arg(mLastBit);
    ui->lblPortType->setText(msPortList + bitList);

}

bool FormDigitalOut::checkForDigital()
{
    bool validBoard;
    int firstBit, defaultPort, defaultNumBits;
    int channelType, numDIChans, portIOType;
    QString params;

    validBoard = false;
    numDIChans = 1;
    channelType = PORTOUT;
    portIOType = PROGPORT;
    params = msProductID;
    numDIChans = digitalUtils->findPortsOfType(params, mDevHandle, channelType, portIOType, defaultPort, defaultNumBits, firstBit);
    mNumPorts = numDIChans;
    if(numDIChans != 0) {
       validBoard = true;
       mPortNum = defaultPort;
       mResolution = defaultNumBits;
    } else {
       ui->txtResult->setText("");
    }
    ui->cmdStart->setEnabled(validBoard);
    return validBoard;
}

void FormDigitalOut::optPortBitClicked()
{
    mbDoBits = ui->optBit->isChecked();
    if (mbDoBits)
       ui->chkArray->setText("Span ports");
    else
       ui->chkArray->setText("Use DOutArray");

    ui->txtFirstBit->setVisible(mbDoBits);
    ui->txtLastBit->setVisible(mbDoBits);
    ui->lblFirstBit->setVisible(mbDoBits);
    ui->lblLastBit->setVisible(mbDoBits);
    getPortType();
}

void FormDigitalOut::configureOutputs(bool setOutputs)
{
    int direction, portNum, i, err;
    long long infoValue;
    QString params;

    params = msProductID;
    direction = MCC_DIG_DIRIN;
    if (setOutputs)
        direction = MCC_DIG_DIROUT;
    for (i = 0; i < mNumPorts; i++) {
        if (LIB_PLATFORM == MV_RPI) {
            params = msProductID;
            portNum = DIO_CFG_PORT_DIRECTION_MASK;
        } else {
            portNum = 0;
            err = libMiscFunctions->mccDioGetInfo(params, mDevHandle, MCC_DIG_DEVTYPE, i, infoValue);
            if (err == MCC_NOERRORS)
                portNum = infoValue;
        }
        err = digitalFuncs->mccDConfigPort(params, mDevHandle, portNum, direction);
        if (err != MCC_NOERRORS)
            ui->lblStatus->setText(libMiscFunctions->mccGetUlErrorText(err));
    }
}

void FormDigitalOut::configureData()
{
    int FS, HS;

    FS = pow(2, mResolution);
    HS = FS / 2;
    mDataValHigh = (HS + (HS) - 1);  //ULongValToInt
    mDataValLow = (HS - (HS));       //ULongValToInt
}

void FormDigitalOut::callClassConstructors()
{
    libMiscFunctions = new LibMisc();
    digitalUtils = new DigitalUtility(libMiscFunctions);
    digitalFuncs = new LibDigital();
}
