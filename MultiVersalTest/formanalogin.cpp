#include "formanalogin.h"
#include "ui_formanalogin.h"
#include "../mvtest.h"

FormAnalogIn::FormAnalogIn(QWidget *parent) :
    FormMvDevice(parent),
    ui(new Ui::FormAnalogIn)
{
    QString curRangeVolts;

    ui->setupUi(this);
    pacerEmulator = new QTimer(this);
    oneShotTimer = new QTimer(this);
    oneShotTimer->setSingleShot(true);
    ui->stackedWidget->setCurrentIndex(0);
    qCustomPlot = ui->plotOutput;
    initializePlotControls();

    connect(oneShotTimer, SIGNAL(timeout()), this, SLOT(singleShotTimeout()));
    connect(pacerEmulator, SIGNAL(timeout()), this, SLOT(intervalTimeout()));

    connect(this, SIGNAL(deviceChanged()), this, SLOT(updateDevice()));
    connect(ui->cmdStart, SIGNAL(clicked(bool)), this, SLOT(cmdStartClicked()));
    connect(ui->cmdStop, SIGNAL(clicked(bool)), this, SLOT(cmdStopClicked()));
    connect(this, SIGNAL(intEnumChanged(int, int)), this, SLOT(updateIntValue(int, int)));
    connect(ui->leRate, SIGNAL(textEdited(QString)), this, SLOT(rateValueChanged(QString)));
    connect(ui->spnHighChan, SIGNAL(valueChanged(int)), this, SLOT(chanValueChanged(int)));
    connect(ui->spnLowChan, SIGNAL(valueChanged(int)), this, SLOT(chanValueChanged(int)));
    connect(ui->cmdSetPlotX, SIGNAL(clicked(bool)), this, SLOT(setPlotXLength()));

    ui->lblError->clear();
    ui->lblArgs->clear();
    ui->lblFunction->clear();
    ui->lblCount->setEnabled(false);
    ui->leSampsPerChan->setEnabled(false);
    ui->lblLoopInterval->setEnabled(false);
    ui->leLoopInterval->setEnabled(false);
    ui->spnHighChan->setObjectName("HighChan");
    ui->spnLowChan->setObjectName("LowChan");
    dblBuffer = NULL;
    mDoubleData = true;
    mCurFunction = UL_AIN;
    ui->leSampsPerChan->setText(QString::number(mBufSize));
    mRange = (MccRange)0;
    curRangeVolts = libTestUtils->getRangeNomo(mRange);
    ui->lblRange0->setText(curRangeVolts);
    callClassConstructors();
}

FormAnalogIn::~FormAnalogIn()
{
    if (dblBuffer)
        delete[] dblBuffer;
    delete aInFunctions;
}

void FormAnalogIn::keyPressEvent(QKeyEvent *event)
{
    int keyCode = event->key();
    /*if (keyCode == Qt::Key_F6)
        if (!mPlot)
            updateData();   */
    if (keyCode == Qt::Key_Escape) {
        cmdStopClicked();
    }
    if ((keyCode == Qt::Key_Plus)  && (QApplication::keyboardModifiers() & Qt::AltModifier)) {
        mPrintResolution += 1;
        ui->lblFunction->setText(QString("Text resolution %1").arg(mPrintResolution));
    }
    if ((keyCode == Qt::Key_Minus)  && (QApplication::keyboardModifiers() & Qt::AltModifier)) {
        mPrintResolution -= 1;
        if (mPrintResolution < 0)
            mPrintResolution = 0;
        ui->lblFunction->setText(QString("Text resolution %1").arg(mPrintResolution));
    }
    if ((keyCode == Qt::Key_X) && (QApplication::keyboardModifiers() & Qt::AltModifier)) {
        mShowHex = !mShowHex;
        ui->lblFunction->setText(QString("Print hex %1").arg(mShowHex));
    }
    /* if ((keyCode == Qt::Key_Period)  && (QApplication::keyboardModifiers() & Qt::AltModifier)) {
        if(mDevName.startsWith("DT9837"))
            mCalcPeriod = true;
        else
            mCalcTime = true;
        ui->lblInfo->setText(QString("Enabled pulse/period calculation"));
    }
    if ((keyCode == Qt::Key_Slash)  && (QApplication::keyboardModifiers() & Qt::AltModifier)) {
        mCalcTime = false;
        mCalcPeriod = false;
        ui->lblInfo->setText(QString("Disabled pulse/period calculation"));
    }   */
}

void FormAnalogIn::cmdStartClicked()
{
    ui->lblError->clear();
    mCurLoopCount = 0;
    switch (mCurFunction) {
    case UL_AIN:
        aInStart();
        break;
    case UL_TIN:
        tInStart();
        break;
    case UL_TINARRAY:
        tInStart();
        break;
    case UL_AINSCAN:
        aInScanStart();
        break;
    default:
        break;
    }
}

void FormAnalogIn::aInScanStart()
{
    int err, range;
    int flags, status, sampleMultiplier;
    long curIndex, curCount;
    QString params;
    double rate, perCentage;

    mPerChanDisplayed = ui->lePerChanDisplayed->text().toLong();
    mPerChanRead = 0;
    mPlotIndex = 0;
    mPlotOffset = 0;
    sampleMultiplier = 1;
    mFirstChan = ui->spnLowChan->value();
    mLastChan = ui->spnHighChan->value();
    mChanCount = (mLastChan - mFirstChan) + 1;
    if (USING_WINDOWS) {
        sampleMultiplier = mChanCount;
    }
    if(mChanCount < 1) mChanCount = 1;
    mSamplesPerChan = (ui->leSampsPerChan->text().toInt());
    mScanCountArg = mSamplesPerChan * sampleMultiplier;
    rate = ui->leRate->text().toDouble();
    flags = mAiFlags;
    range = mRange;
    mCurChanCount = mChanCount;
    mPacerInterval = 100;

    long long bufSize = mChanCount * mSamplesPerChan;
    mBufSize = bufSize;
    perCentage = (ui->leLoopInterval->text().toDouble()) / 100;
    if (perCentage > 100) {
        perCentage = 100;
        ui->lblLoopInterval->setText("100");
    }
    mBlockSize = perCentage * mBufSize;
    if (mBlockSize < 2 * mChanCount)
        mBlockSize = 2 * mChanCount;

    if(mPlot)
        setupPlot(qCustomPlot);

    if (!USING_WINDOWS) {
        if (dblBuffer) {
            delete[] dblBuffer;
            dblBuffer = NULL;
        }

        dblBuffer = new double[bufSize];
        memset(dblBuffer, 0, mBufSize * sizeof(*dblBuffer));

        err = aInFunctions->mccAInScan(params, mDevHandle, mFirstChan, mLastChan,
                                       mAiMode, mSamplesPerChan, rate, range, mCurOptions, flags, dblBuffer);
    } else {
        mDoublePointer = false;
        mDoubleData = false;
        if (mCurOptions & MCC_SO_SCALEDATA) {
            mDoubleData = true;
        }
        if (intBuffer) {
            delete[] intBuffer;
            intBuffer = NULL;
        }
        if (dblBuffer) {
            delete[] dblBuffer;
            dblBuffer = NULL;
        }

        if (mDoubleData) {
            dblBuffer = new double[bufSize];
            mHandle = dblBuffer;
        } else {
            intBuffer = new int[bufSize];
            mHandle = intBuffer;
        }

        err = aInFunctions->mccAInScan(params, mDevHandle, mFirstChan, mLastChan,
                                       mAiMode, mScanCountArg, rate, range, mCurOptions, flags, mHandle);
    }

    if (err != MCC_NOERRORS) {
        ui->lblError->setText(libMiscFunctions->mccGetUlErrorText(err));
        cmdStopClicked();
        return;
    }
    err = aInFunctions->mccAInScanStatus(params, mDevHandle, status, curIndex, curCount);
    if (err == MCC_NOERRORS)
        mRunning = true;
    pacerEmulator->start(mPacerInterval);
}

void FormAnalogIn::checkScanStatus()
{
    int err, status, samplesAvailable;
    long curIndex, curCount, curPlotIndex, residual;
    QString params;
    bool resetIndex;

    resetIndex = false;
    pacerEmulator->stop();
    err = aInFunctions->mccAInScanStatus(params, mDevHandle, status, curIndex, curCount);
    if (err != MCC_NOERRORS) {
        ui->lblError->setText(libMiscFunctions->mccGetUlErrorText(err));
    }
    ui->lblFunction->setText(params.mid(0, params.indexOf("\n")));
    ui->lblArgs->setText(params.mid(params.indexOf("\n") + 1));

    residual = curIndex;
    curPlotIndex = mPerChanRead;
    if (curIndex > -1) {
        samplesAvailable = residual - curPlotIndex;
        if (curIndex < mPerChanRead) {
            residual = curIndex + (mBufSize - mBlockSize);
            samplesAvailable = residual;
            resetIndex = true;
        }
        if (status == 0) {
            mBlockSize = (samplesAvailable) + 1;
            if (mPlot)
                plotData();
            else
                printData();
            stopScan();
            mPerChanRead += mBlockSize;
            mRunning = false;
            return;
        } else {
            if ((samplesAvailable) >= (mBlockSize)) {
                if (mPlot)
                    plotData();
                else
                    printData();
                mPerChanRead += mBlockSize;
                if ((curIndex < mPerChanRead) & resetIndex) {
                    mPerChanRead = 0;
                    mPlotOffset = 0;
                }
            }
        }
    }
    pacerEmulator->start(mPacerInterval);
}

void FormAnalogIn::aInStart()
{
    int err, key, firstChan, lastChan, curRange;
    QString curRangeVolts;
    QString params, msg;
    bool isDoublePointer;

    ui->lblError->clear();
    firstChan = ui->spnLowChan->value();
    lastChan = ui->spnHighChan->value();
    mPerChanDisplayed = ui->lePerChanDisplayed->text().toLong();
    mSamplesPerChan = mPerChanDisplayed;

    mDoubleData = (mAiFlags != AIN_FF_NOSCALEDATA);
    //if ((!USING_WINDOWS) | (mCurFunction != UL_AINSCAN))
    isDoublePointer = true;

    if (!mRunning) {
        mPerChanRead = 0;
        if (!mQueueInUse) {
            key = 0;
            mChanCount = (lastChan - firstChan) + 1;
            mChanList.clear();
            for (int chan = firstChan; chan <= lastChan; chan++) {
                mChanList.insert(key, chan);
                mRangeList.insert(key, mRange);
                key++;
            }
            curRangeVolts = libTestUtils->getRangeNomo(mRange);
            ui->lblRange0->setText(curRangeVolts);
        } else {
            mChanCount = mChanList.count();
            for (int chan = 0; chan < mChanCount; chan++) {
                curRange = mRangeList.value(chan);
                curRangeVolts = libTestUtils->getRangeNomo(curRange);
                rbRangeLabels[chan]->setText(curRangeVolts);
            }
        }
        mChanIndex = 0;
        long long bufSize = mChanCount * mPerChanDisplayed;
        mBufSize = bufSize;
        if (isDoublePointer) {
            mDoublePointer = true;
            if (dblBuffer) {
                delete[] dblBuffer;
                dblBuffer = NULL;
            }
            dblBuffer = new double[bufSize];
            memset(dblBuffer, 0, mBufSize * sizeof(*dblBuffer));
        } else {
            mDoublePointer = false;
            if (intBuffer) {
                delete[] intBuffer;
                intBuffer = NULL;
            }
            if (dblBuffer) {
                delete[] dblBuffer;
                dblBuffer = NULL;
            }
            if (mDoubleData) {
                dblBuffer = new double[bufSize];
                memset(dblBuffer, 0, mBufSize * sizeof(*dblBuffer));
                mHandle = dblBuffer;
            } else {
                intBuffer = new int[bufSize];
                memset(intBuffer, 0, mBufSize * sizeof(*intBuffer));
                mHandle = intBuffer;
            }
        }
        err = aInCheckParameters(params);
        ui->lblFunction->setText(params.mid(0, params.indexOf("\n")));
        ui->lblArgs->setText(params.mid(params.indexOf("\n") + 1));
        if (err != MCC_NOERRORS) {
            msg = libMiscFunctions->mccGetUlErrorText(err);
            ui->lblError->setText(msg);
            return;
        }
        mPerChanDisplayed = ui->lePerChanDisplayed->text().toLong();
        if(mPlot) {
            setupPlot(qCustomPlot);
        }
        mPlotIndex = 0;
        mSampleIndex = -1;
        inputReadInitialize();
    } else {
        functionIteration();
    }
}

int FormAnalogIn::aInCheckParameters(QString &params)
{
    int err, chan, range;
    double dataValue;

    chan = mChanList.value(0);
    range = mRangeList.value(0);
    params = msProductID;
    err = aInFunctions->mccAIn(params, mDevHandle,
                chan, mAiMode, mAiFlags, range, dataValue);
    if (err != MCC_NOERRORS)
        return err;

    chan = mChanList.value(mChanList.count() - 1);
    range = mRangeList.value(mRangeList.count() - 1);
    params = msProductID;
    err = aInFunctions->mccAIn(params, mDevHandle,
                chan, mAiMode, mAiFlags, range, dataValue);

    return err;
}

void FormAnalogIn::inputReadInitialize()
{
    double pacerRate;
    int pacedChanCount, optValue;
    bool arrayScan = false;
    mNumScans = ui->leSampsPerChan->text().toInt();

    mAcqMode = AcqStandardMode;
    mPaceMode = ManualMode;
    mEmulateBurstMode = false;
    pacerRate = ui->leRate->text().toDouble();
    mUpdateBlock = (pacerRate / 10) * mChanCount;
    if ((mUpdateBlock < mChanCount) | (mUpdateBlock > mPerChanDisplayed))
        mUpdateBlock = mChanCount;

    mNumPacedChans = mChanCount;
    if (intParams.contains(IPARAM_OPTIONS)) {
        optValue = intParams.value(IPARAM_OPTIONS);
    } else
        optValue = MCC_SO_DEFAULTIO;
    if (optValue & MCC_SO_BURSTMODE)
        mEmulateBurstMode = true;

    if (mCurFunction == UL_TINARRAY) {
        arrayScan = true;
        mNumPacedChans = 1;
        mEmulateBurstMode = true;
    }

    /*  Single sample at a time incrementing on
     *  each iteration - Stop command resets    */
    mCurFirstChan = mChanList.value(0);
    mCurLastChan = mChanList.value(0);
    if (mEmulateBurstMode)
        mCurLastChan = mChanList.value(mChanCount - 1);
    mCurScanCount = 0;
    mCurChanCount = 0;

    if (!mEmulateBurstMode) {
        mNumPacedChans = 1;
    }

    msData.clear();
    ui->teOutput->clear();
    mRunning = true;
    if (pacerRate > 0) {
        /*  Pace either scans or samples based on
         *  BurstMode emulation setting     */
        mPaceMode = PacedMode;
        pacedChanCount = mChanList.count();
        if (mEmulateBurstMode | arrayScan) {
            pacedChanCount = 1;
        }
        if (((1000 / pacerRate) / pacedChanCount) < 1) {
            mAcqMode = AcqFreeScan;
            functionIteration();
        } else {
            mPacerInterval = (1000 / pacerRate) / pacedChanCount;
            pacerEmulator->start(100);
        }
    } else {
        functionIteration();
    }
}

void FormAnalogIn::tInStart()
{
    int err, key, firstChan, lastChan;
    QString params, msg;

    ui->lblError->clear();
    //mLastChan = ui->spnHighChan->value();
    firstChan = ui->spnLowChan->value();
    lastChan = ui->spnHighChan->value();
    mPerChanDisplayed = ui->lePerChanDisplayed->text().toLong();
    mSamplesPerChan = mPerChanDisplayed;

    mDoubleData = (mTempScale != TS_NOSCALE);

    if (!mRunning) {
        mPerChanRead = 0;
        if (!mQueueInUse) {
            key = 0;
            mChanList.clear();
            for (int chan = firstChan; chan <= lastChan; chan++) {
                mChanList.insert(key, chan);
                key++;
            }
        }
        mChanCount = mChanList.count();
        mChanIndex = 0;
        long long bufSize = mChanCount * mPerChanDisplayed;
        mBufSize = bufSize;
        if (!USING_WINDOWS) {
            mDoublePointer = true;
            if (dblBuffer) {
                delete[] dblBuffer;
                dblBuffer = NULL;
            }
            dblBuffer = new double[bufSize];
            memset(dblBuffer, 0, mBufSize * sizeof(*dblBuffer));
        } else {
            mDoublePointer = false;
            if (intBuffer) {
                delete[] intBuffer;
                intBuffer = NULL;
            }
            if (dblBuffer) {
                delete[] dblBuffer;
                dblBuffer = NULL;
            }
            if (mDoubleData) {
                dblBuffer = new double[bufSize];
                memset(dblBuffer, 0, mBufSize * sizeof(*dblBuffer));
                mHandle = dblBuffer;
            } else {
                intBuffer = new int[bufSize];
                memset(intBuffer, 0, mBufSize * sizeof(*intBuffer));
                mHandle = intBuffer;
            }
        }
        err = tInCheckParameters(params);
        ui->lblFunction->setText(params.mid(0, params.indexOf("\n")));
        ui->lblArgs->setText(params.mid(params.indexOf("\n") + 1));
        if (err != MCC_NOERRORS) {
            if (err != MCC_OPENCONNECTION) {
                msg = libMiscFunctions->mccGetUlErrorText(err);
                ui->lblError->setText("Error: " + msg);
                return;
            }
        }
        if(mPlot) {
            setupPlot(qCustomPlot);
        }
        mPlotIndex = 0;
        mSampleIndex = -1;
        inputReadInitialize();
    } else {
        functionIteration();
    }
}

int FormAnalogIn::tInCheckParameters(QString &params)
{
    int err, lowChan,highChan;
    double dataValue;
    double *valueArray;

    lowChan = mChanList.value(0);
    highChan = mChanList.value(mChanList.count() - 1);
    valueArray = new double[mChanCount];
    if (mCurFunction == UL_TIN) {
        err = aInFunctions->mccTIn(params, mDevHandle,
                    lowChan, mTempScale, mTiFlags, dataValue);
        if (err != MCC_NOERRORS) {
            if (err != MCC_OPENCONNECTION)
                return err;
        }

        err = aInFunctions->mccTIn(params, mDevHandle,
                    highChan, mTempScale, mTiFlags, dataValue);
    } else {
        err = aInFunctions->mccTInArray(params, mDevHandle, lowChan, highChan, mTempScale, mTiArrayFlags, valueArray);
    }
    delete[] valueArray;
    return err;
}

void FormAnalogIn::functionIteration()
{
    /*  If ManualMode, called from cmdStart
     *  Otherwise, called from pacer timer  */
    if ((mCurFirstChan == mChanList.value(0)) | (mEmulateBurstMode)) {
        mCurChanCount = 0;
        pacerEmulator->setInterval(mPacerInterval);
    }
    if (mSampleIndex > mBufSize)
        mSampleIndex = -1;
    readInput();
    if (!mEmulateBurstMode) {
        mChanIndex++;
        if (mChanIndex == mChanCount) {
            mChanIndex = 0;
            mCurScanCount++;
        }
        mCurFirstChan = mChanList.value(mChanIndex);
        mBlockSize = mUpdateBlock;
        if (mPlot) {
            if (mCurScanCount > 0) {
                if ((mSampleIndex  + 1) % mUpdateBlock == 0) {
                    plotData();
                    mPerChanRead += mUpdateBlock;
                }
            }
        } else {
            printData();
            mPerChanRead += mUpdateBlock;
        }
    } else {
        mCurScanCount++;
        mBlockSize = mCurScanCount * mChanCount;
        mBlockSize = mUpdateBlock;
        if (mPlot) {
            if (mCurScanCount > 0) {
                if ((mSampleIndex  + 1) % mUpdateBlock == 0) {
                    plotData();
                    mPerChanRead += mUpdateBlock;
                }
            }
        } else {
            printData();
        }
    }
    if (mCurScanCount >= mSamplesPerChan) {
        pacerEmulator->stop();
        mRunning = false;
        mPerChanRead = 0;
        mCurLoopCount++;
    }

    if (!mRunning) {
        if ((mCurLoopCount < mNumScans) | (mNumScans == 0)){
            if (mPaceMode == PacedMode) {
                oneShotTimeout = ui->leLoopInterval->text().toInt() * 1000;
                if (oneShotTimeout < 50) {
                    iterateLoop();
                } else {
                    mCurTimerJob = tjStart;
                    oneShotTimer->start(oneShotTimeout);
                }
            }
        }
    } else {
        if (mAcqMode == AcqFreeScan)
            functionIteration();
    }
}

void FormAnalogIn::iterateLoop()
{
    switch (mCurFunction) {
    case UL_AIN:
        aInStart();
        break;
    case UL_TIN:
    case UL_TINARRAY:
        tInStart();
        break;
    default:
        break;
    }
}

void FormAnalogIn::readInput()
{
    QString params, errStr;
    int err, chan, chanIndex;
    int firstChan, lastChan;
    double dataValue;
    double *valueArray;
    int range, flagOpts;

    flagOpts = mAiFlags;
    if (LIB_PLATFORM == 3) {
        flagOpts = mCurOptions;
    }
    valueArray = new double[mChanCount];
    for (chanIndex = mChanIndex; chanIndex < mChanIndex + mNumPacedChans; chanIndex++) {
        chan = mChanList.value(chanIndex);
        range = mRangeList.value(chanIndex);
        params = msProductID;
        switch (mCurFunction) {
        case UL_AIN:
            mSampleIndex++;
            err = aInFunctions->mccAIn(params, mDevHandle,
                    chan, mAiMode, flagOpts, range, dataValue);
            if (mDoublePointer)
                dblBuffer[mSampleIndex] = dataValue;
            else
                intBuffer[mSampleIndex] = dataValue;
            break;
        case UL_TIN:
            mSampleIndex++;
            err = aInFunctions->mccTIn(params, mDevHandle,
                    chan, mTempScale, mTiFlags, dataValue);
            if (err == MCC_OPENCONNECTION) {
                errStr = "Open";
                //valuesAreFloat = false;
            }
            if (mDoublePointer)
                dblBuffer[mSampleIndex] = dataValue;
            else
                intBuffer[mSampleIndex] = dataValue;
            break;
        case UL_TINARRAY:
            //arrayReturned = true;
            firstChan = mChanList.value(0);
            lastChan = mChanList.value(mChanCount - 1);
            err = aInFunctions->mccTInArray(params, mDevHandle, firstChan, lastChan, mTempScale, mTiArrayFlags, valueArray);
            for (int ch = 0; ch < mChanCount; ch++) {
                mSampleIndex++;
                if (mDoubleData)
                    dblBuffer[mSampleIndex] = dataValue;
                else
                    intBuffer[mSampleIndex] = dataValue;
            }
            mCurChanCount = mChanCount - 1;
            break;
        default:
            break;
        }
        mCurChanCount++;
    }
    //ui->lblError->setText(QString("%1").arg(mCurScanCount));
    delete[] valueArray;
}

void FormAnalogIn::intervalTimeout()
{
    switch (mCurFunction) {
    case UL_AIN:
    case UL_TIN:
    case UL_TINARRAY:
        aInStart();
        break;
    case UL_AINSCAN:
        checkScanStatus();
        break;
    default:
        break;
    }
}

void FormAnalogIn::singleShotTimeout()
{
    switch (mCurTimerJob) {
    case tjStart:
        oneShotTimer->stop();
        mCurTimerJob = tjNone;
        QCoreApplication::processEvents();
        iterateLoop();
        break;
    default:
        break;
    }
}

void FormAnalogIn::cmdStopClicked()
{
    mPerChanRead = 0;
    stopScan();
}

void FormAnalogIn::stopScan()
{
    int err;
    QString params;

    pacerEmulator->stop();
    mRunning = false;
    mCurFirstChan = mChanList.value(0);
    mChanIndex = 0;
    mCurScanCount = 0;
    mNumScans = 1;
    oneShotTimer->stop();
    if (mCurFunction == UL_AINSCAN) {
        err = aInFunctions->mccAInScanStop(params, mDevHandle);
        if (err != MCC_NOERRORS)
            ui->lblError->setText(libMiscFunctions->mccGetUlErrorText(err));
        mRunning = false;
    }
}

void FormAnalogIn::printData()
{
    double *bufData;
    int *intData;
    if(mCurFunction == UL_AINSCAN) {
        bufData = (double*)mHandle;
        intData = (int*)mHandle;
    } else {
        bufData = dblBuffer;
        intData = intBuffer;
    }

    int chIndex = 0;
    int samp, afterDecimal, ch;
    double valRead;
    QString showSign = "+";
    QString valFormatted, fontHTML;

    fontHTML = " <font color=blue>";
    samp = 0;
    afterDecimal = mPrintResolution;
    if (!mDoubleData) {
        afterDecimal = 0;
        showSign = "";
    }

    msData = "<style> th, td { padding-right: 10px;}</style><tr><td></td>";
    for (chIndex = 0; chIndex < mChanCount; chIndex++) {
        ch = mChanList.value(chIndex);
        if (mQueueInUse)
            fontHTML = mFontHTML[chIndex];
        msData.append("<td align=""center""> <u>"+ fontHTML + QString("CH%1").arg(ch) + "</font></u></td>");
    }
    msData.append("</tr><tr>");
    ch = 0;

    for (samp = 0; samp <= mSampleIndex; samp += mCurChanCount) {
        for (chIndex = 0; chIndex < mCurChanCount; chIndex++) {
            if (ch == 0)
                msData.append("</tr><tr><td>" + QString("%1)").arg(samp) + "</td>");
            if (mDoublePointer) {
                valRead = bufData[samp + chIndex];
            } else {
                valRead = intData[samp + chIndex];
            }
            if(mDoubleData) {
                valFormatted = QString("%1%2").arg((valRead < 0) ? "" : showSign).arg
                        (valRead, 1, 'f', afterDecimal, '0');
            } else {
                if (mShowHex)
                    valFormatted = QString("0x%1").arg((long)valRead, mHexResolution, 16, QLatin1Char('0'));
                else
                    valFormatted = QString("%1").arg(valRead);
            }
            msData.append("<td>" + valFormatted + "</td>");
            ch++;
            if (samp + chIndex >= mSampleIndex)
                break;
            if (ch >= mChanCount) {
                ch = 0;
            }
        }
    }
    mPerChanRead = samp;
    ui->teOutput->setHtml(msData);
}

void FormAnalogIn::plotData()
{

#ifdef Q_OS_WIN32
    double *bufData;
    bufData = (double*)mHandle;
    WORD *intData;
    intData = (WORD*)mHandle;
#else
    double *bufData;
    bufData = dblBuffer;
    int *intData;
    intData = intBuffer;
#endif

    int index, curIndex, curStart, bufIndex, chan, samp;
    index = 0;
    bool autoScale;
    double value;

    if (mPlotIndex >= (mBufSize / mChanCount))
        mPlotIndex = 0;
    if ((mPerChanRead == 0) & (mPlotIndex == 0))
        setupPlot(qCustomPlot);

    chan = 0;
    index = mPlotIndex;
    curStart = mPerChanRead;
    curIndex = (curStart + mBlockSize);
    for (samp = curStart; samp < curIndex; samp += mChanCount) {
        for (chan = 0; chan < mChanCount; chan++) {
            bufIndex = samp + chan;
            if (mDoublePointer)
                value = bufData[bufIndex];
            else
                value = intData[bufIndex];
            ui->plotOutput->graph(chan)->addData(index, value);
            if (mBufSize <= index) {
                index = 0;
            }
        }
        index++;
    }
    mPlotIndex = index;
    autoScale = ui->rbAutoScale->isChecked();
    updatePlot(qCustomPlot, autoScale);
}

/*
void FormAnalogIn::setupPlot()
{
    QColor penColor;
    QPalette brushColor;
    int ctlIndex;
    long plotSize;
    xValues.clear();
    QCustomPlot *dataPlot = ui->plotOutput;

    plotSize = mPerChanDisplayed;
    xValues.resize(plotSize);
    double *xData = xValues.data();
    for (int smpl = 0; smpl < plotSize; smpl++)
        xData[smpl] = smpl;

    int chanCycle;
    int curChanCount;
    dataPlot->clearGraphs();
    dataPlot->setBackground(brushColor.window());
    dataPlot->axisRect()->setBackground(Qt::white);
    chanCycle = -1;

    if(mPlotChan == -1)
        curChanCount = mChanCount;
    else
        curChanCount = 1;

    for(int chan = 0; chan < curChanCount; chan++)
    {
        if(mPlotChan == -1)
            chanCycle += 1;
        else
            chanCycle = mPlotChan;
        if(chanCycle>7)
            chanCycle = chanCycle % 8;
        switch(chanCycle)
        {
        case 0:
            penColor = Qt::blue;
            mFontHTML[0] = " <font color=blue>";
            break;
        case 1:
            penColor = Qt::red;
            mFontHTML[1] = " <font color=red>";
            break;
        case 2:
            penColor = Qt::green;
            mFontHTML[2] = " <font color=green>";
            break;
        case 3:
            penColor = Qt::cyan;
            mFontHTML[3] = " <font color=cyan>";
            break;
        case 4:
            penColor = Qt::darkCyan;
            mFontHTML[4] = " <font color=darkCyan>";
            break;
        case 5:
            penColor = Qt::magenta;
            mFontHTML[5] = " <font color=magenta>";
            break;
        case 6:
            penColor = Qt::gray;
            mFontHTML[6] = " <font color=gray>";
            break;
        default:
            penColor = Qt::black;
            mFontHTML[7] = " <font color=black>";
            break;
        }
        dataPlot->addGraph();
        dataPlot->graph(chan)->setPen(penColor);
        ctlIndex = chan % 8;
        rbPlotSel[ctlIndex]->setVisible(true);
        rbPlotLabels[ctlIndex]->setVisible(true);
        rbPlotLabels[ctlIndex]->setText(QString("%1").arg(mFirstChan + chan));
        ui->plotOutput->graph(ctlIndex)->setVisible(rbPlotSel[ctlIndex]->isChecked());
    }
    for (int i = mChanCount; i<8; i++) {
        rbPlotSel[i]->setVisible(false);
        rbPlotLabels[i]->setVisible(false);
    }

    dataPlot->axisRect(0)->setAutoMargins(QCP::msLeft|QCP::msBottom);
    dataPlot->axisRect(0)->setMargins(QMargins(0,2,2,0));
    dataPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    dataPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    dataPlot->xAxis->setTickLabelColor(Qt::blue);
    dataPlot->yAxis->setTickLabelColor(Qt::blue);
    ui->plotOutput->xAxis->setRangeLower(0);
    ui->plotOutput->xAxis->setRangeUpper(mPerChanDisplayed - 1);
    ui->plotOutput->replot();
    ui->plotOutput->axisRect()->setRangeDrag(Qt::Horizontal);
    ui->plotOutput->setInteraction(QCP::iRangeDrag, true);
}

void FormAnalogIn::updatePlot()
{
    QString params;
    bool setTCRange = false;
    bool autoScale, bipolar;
    double rangeBuf;
    double rangeUpper, rangeLower;
    int err, configItem, startElement;
    QMap<int, QString> infoItems;
    double *xData = xValues.data();

    if (mChanList.count()) {
        foreach (int key, mChanList.keys()) {
            int chan = mChanList.value(key);
            rbPlotLabels[key]->setText(QString::number(chan));
        }
    }

    rangeLower = 0;
    startElement = (mPerChanRead / mChanCount);
    if (startElement >= mSamplesPerChan) {
        startElement = 0;
    }
    if (startElement >= (mPerChanDisplayed * (mPlotOffset + 1)))
        mPlotOffset++;

    rangeLower = mPlotOffset * mPerChanDisplayed;
    for (int smpl = startElement; smpl < mPerChanDisplayed; smpl++) {
        int xVal = smpl + rangeLower;
        xData[smpl] = xVal;
    }
    rangeUpper = (mPerChanDisplayed + rangeLower) - 1;
    ui->plotOutput->xAxis->setRange(rangeLower, rangeUpper);

    autoScale = ui->rbAutoScale->isChecked();
    if(autoScale) {
        ui->plotOutput->yAxis->rescale(true);
        double center = ui->plotOutput->yAxis->range().center();
        ui->plotOutput->yAxis->scaleRange(1.2, center);
    } else {
        if (mRange == MCC_BIPPT078VOLTS) {
            infoItems = libMiscFunctions->mccGetAiInfoItems();
            foreach (QString itemName, infoItems.values()) {
                if (itemName == "0:0:Resolution") {
                    configItem = infoItems.key(itemName);
                    break;
                }
            }
            unsigned int index = 0;
            long long configValue = -1;
            err = libMiscFunctions->mccAiGetInfo(params, mDevHandle,
                                              configItem, index, configValue);
            if ((err == MCC_NOERRORS) && (configValue == 2))
                setTCRange = true;
        }
        if (mCurFunction == UL_TIN)
            setTCRange = true;
        if (setTCRange) {
            rangeBuf = 0;
            rangeUpper = 50;
            rangeLower = 10;
        } else {
            if (mAiFlags & AIN_FF_NOSCALEDATA) {
                long fsCount = qPow(2, mAiResolution);
                rangeBuf = fsCount / 10;
                rangeUpper = fsCount;
                rangeLower = 0;
            } else {
                bipolar = mRange < 100;
                double rangeVolts = testUtils->getRangeVolts(mRange);
                rangeBuf = rangeVolts / 10;
                rangeUpper = bipolar? rangeVolts / 2 : rangeVolts;
                rangeLower = bipolar? rangeUpper * -1 : 0;
            }
        }
        ui->plotOutput->yAxis->setRangeLower(rangeLower - rangeBuf);
        ui->plotOutput->yAxis->setRangeUpper(rangeUpper + rangeBuf);
    }
    ui->plotOutput->replot();
}

void FormAnalogIn::replot()
{
    bool autoScale;

    autoScale = ui->rbAutoScale->isChecked();
    updatePlot(qCustomPlot, autoScale);
}

void FormAnalogIn::plotSelect()
{
** OBSOLETE? **
**
    int ctlIndex;
    bool autoScale;

    for (int plotNum = 0; plotNum < mChanCount; plotNum++) {
        ctlIndex = plotNum % 8;
        qCustomPlot->graph(ctlIndex)->setVisible(rbPlotSel[ctlIndex]->isChecked());
    }
    autoScale = ui->rbAutoScale->isChecked();
    updatePlot(qCustomPlot, autoScale);
}
*/

void FormAnalogIn::initializePlotControls()
{
    connect(ui->rbAutoScale, SIGNAL(clicked(bool)), this, SLOT(setAutoScale()));
    connect(ui->rbFullScale, SIGNAL(clicked(bool)), this, SLOT(setAutoScale()));

    rbPlotSel[0] = ui->rbPlot0;
    rbPlotSel[1] = ui->rbPlot1;
    rbPlotSel[2] = ui->rbPlot2;
    rbPlotSel[3] = ui->rbPlot3;
    rbPlotSel[4] = ui->rbPlot4;
    rbPlotSel[5] = ui->rbPlot5;
    rbPlotSel[6] = ui->rbPlot6;
    rbPlotSel[7] = ui->rbPlot7;
    rbPlotLabels[0] = ui->lblRb0;
    rbPlotLabels[1] = ui->lblRb1;
    rbPlotLabels[2] = ui->lblRb2;
    rbPlotLabels[3] = ui->lblRb3;
    rbPlotLabels[4] = ui->lblRb4;
    rbPlotLabels[5] = ui->lblRb5;
    rbPlotLabels[6] = ui->lblRb6;
    rbPlotLabels[7] = ui->lblRb7;
    rbRangeLabels[0] = ui->lblRange0;
    rbRangeLabels[1] = ui->lblRange1;
    rbRangeLabels[2] = ui->lblRange2;
    rbRangeLabels[3] = ui->lblRange3;
    rbRangeLabels[4] = ui->lblRange4;
    rbRangeLabels[5] = ui->lblRange5;
    rbRangeLabels[6] = ui->lblRange6;
    rbRangeLabels[7] = ui->lblRange7;

    initPlotCtlProps();

    mPlot = false;
    mPlotChan = -1;
    mPlotCount = 0;
    ui->rbAutoScale->setVisible(false);
    ui->rbFullScale->setVisible(false);
    ui->fraPlotSel->setVisible(false);
    qCustomPlot->replot();
}

void FormAnalogIn::setAutoScale()
{
    bool autoScale;

     autoScale = ui->rbAutoScale->isChecked();
     if (!mRunning)
        replot(qCustomPlot, autoScale);
}

void FormAnalogIn::setPlotXLength()
{
    bool autoScale;

    mPerChanDisplayed = ui->lePerChanDisplayed->text().toLong();
    autoScale = ui->rbAutoScale->isChecked();
    plotXLengthConfig(qCustomPlot, autoScale);
}

void FormAnalogIn::enablePlot(int paramValue)
{
    bool bufferExists;

    mPlot = (paramValue == 1);
    ui->stackedWidget->setCurrentIndex(paramValue);
    ui->rbAutoScale->setVisible(mPlot);
    ui->rbFullScale->setVisible(mPlot);
    ui->fraPlotSel->setVisible(mPlot);
    if (mPlot)
        setupPlot(qCustomPlot);

    bufferExists = (dblBuffer != NULL);
    if (bufferExists) {
        mPerChanRead = 0;
        printData();
    }
}

void FormAnalogIn::rateValueChanged(QString newValue)
{
    bool rateCtlsEnabled = (newValue != "0");

    ui->lblCount->setEnabled(rateCtlsEnabled);
    ui->leSampsPerChan->setEnabled(rateCtlsEnabled);
    ui->lblLoopInterval->setEnabled(rateCtlsEnabled);
    ui->leLoopInterval->setEnabled(rateCtlsEnabled);
    cmdStopClicked();
}

void FormAnalogIn::chanValueChanged(int chanVal)
{
    if (sender()->objectName() == "HighChan") {
        if (ui->spnLowChan->value() > chanVal)
            ui->spnLowChan->setValue(chanVal);
    }
    if (sender()->objectName() == "LowChan") {
        if (ui->spnHighChan->value() < chanVal)
            ui->spnHighChan->setValue(chanVal);
    }
    cmdStopClicked();
}

void FormAnalogIn::updateIntValue(int paramEnum, int paramValue)
{
    QString curRangeVolts;

    switch (paramEnum) {
    case IPARAM_FUNCTYPE:
        mCurFunction = paramValue;
        setUiForFunction();
        break;
    case IPARAM_RANGE:
        if (paramValue == MCC_SETQUEUE)
            showQueueConfig();
        else {
            mRange = (MccRange)paramValue;
            curRangeVolts = libTestUtils->getRangeNomo(mRange);
            ui->lblRange0->setText(curRangeVolts);
        }
        break;
    case IPARAM_AINMODE:
        mAiMode = (AiInputMode)paramValue;
        break;
    case IPARAM_FLAGS:
        mAiFlags = (AInFlag)paramValue;
        break;
    case IPARAM_OPTIONS:
        mCurOptions = paramValue;
        ui->lblFunction->setText("Options set to: " + libTestUtils->getOptionNames(mCurOptions));
        break;
    case IPARAM_WAITDATA:
        mTiFlags = TIN_FF_DEFAULT;
        if (paramValue)
            mTiFlags = TIN_FF_WAIT_FOR_NEW_DATA;
        break;
    case IPARAM_PLOTTYPE:
        enablePlot(paramValue);
        break;
    default:
        break;
    }
    cmdStopClicked();
}

void FormAnalogIn::showQueueConfig()
{
    queueSetup = new QueueDialog(this);
    if (mChanList.count()) {
        queueSetup->setChanList(mChanList);
        queueSetup->setChanTypeList(mChanTypeList);
        queueSetup->setModeList(mModeList);
        queueSetup->setRangeList(mRangeList);
        queueSetup->setNumQueueElements(mChanList.count());
    }
    connect(queueSetup, SIGNAL(accepted()), this, SLOT(queueDialogResponse()));
    queueSetup->exec();
}

void FormAnalogIn::queueDialogResponse()
{
    mChanList = queueSetup->chanList();
    mChanTypeList = queueSetup->chanTypeList();
    mModeList = queueSetup->modeList();
    mRangeList = queueSetup->rangeList();

    disconnect(queueSetup);
    //delete queueSetup;
    //if (mCurFunction == UL_AINSCAN)
        setupQueue();
    /*else {
        unsigned int numElements = mChanList.count();
        ui->spnLowChan->setValue(0);
        ui->spnHighChan->setValue(numElements - 1);
    }*/
}

void FormAnalogIn::setupQueue()
{
    int err, lbl;
    QString params;
    int numElements = mChanList.count();

    for (lbl = 0; lbl < 8; lbl++)
        rbRangeLabels[lbl]->setText("");
    if ((mCurFunction == UL_AINSCAN) | (mCurFunction == UL_DAQ_INSCAN)) {
        err = aInFunctions->mccLoadQueue(params, mDevHandle, mChanList, mRangeList, mModeList, numElements);
        if (err != MCC_NOERRORS) {
            ui->lblError->setText(libMiscFunctions->mccGetUlErrorText(err));
            return;
        }
    }

    int chanAdjust = 0;
    if (numElements)
        chanAdjust = 1;
    ui->spnLowChan->setValue(0);
    ui->spnHighChan->setValue(numElements - chanAdjust);
    if (numElements == 0) {
        mQueueInUse = false;
        MvTest *mainForm = getMainWindow();
        if (mainForm) {
            mainForm->refreshChildMenu(this, MENU_RANGE);
        }
    } else {
        mQueueInUse = true;
    }
}

void FormAnalogIn::setUiForFunction()
{
    QString curOpts;
    MvTest *mainForm;

    switch (mCurFunction) {
    case UL_AIN:
        ui->lePerChanDisplayed->setText("5");
        ui->leRate->setText("0");
        ui->leLoopInterval->setText("3");
        ui->leSampsPerChan->setText("1");
        ui->lblLoopInterval->setText("Loop Interval");
        ui->lblCount->setText("NumScans");
        mCurOptions = 0;
        mCurOptions = MCC_SO_DEFAULTIO;
        intParams.insert(IPARAM_OPTIONS, mCurOptions);
        ui->lblFunction->setText("Current function: AIn()");
        setIntParam(IPARAM_PLOTTYPE, 0);
        mainForm = getMainWindow();
        if (mainForm) {
            mainForm->refreshChildMenu(this, MENU_PLOT);
            mainForm->refreshChildMenu(this, MENU_RANGE);
        }
        mBreakScan = true;
        break;
    case UL_AINSCAN:
        ui->lePerChanDisplayed->setText("500");
        ui->leRate->setText("200");
        ui->leSampsPerChan->setText("1000");
        ui->leLoopInterval->setText("50");
        ui->lblLoopInterval->setText("Update at (% of buffer)");
        ui->lblCount->setText("Samples");
        mCurOptions = MCC_SO_BACKGROUND | MCC_SO_SCALEDATA;
        intParams.insert(IPARAM_OPTIONS, mCurOptions);
        curOpts = libTestUtils->getOptionNames(mCurOptions);
        ui->lblFunction->setText("Current function: AInScan() [" + curOpts + "]");
        setIntParam(IPARAM_PLOTTYPE, 1);
        mainForm = getMainWindow();
        if (mainForm) {
            mainForm->refreshChildMenu(this, MENU_PLOT);
        }
        mBreakScan = false;
        break;
    default:
        break;
    }
    rateValueChanged(ui->leRate->text());
}

void FormAnalogIn::updateDevice()
{
    if (mDevHandle == -1) {
        ui->fraControl->setEnabled(false);
        return;
    }
    ui->fraControl->setEnabled(true);
    cmdStopClicked();
}

void FormAnalogIn::callClassConstructors()
{
    aInFunctions = new LibAnalog;
}
