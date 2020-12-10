#ifndef FORMANALOGIN_H
#define FORMANALOGIN_H

#include <QTimer>
#include <QLabel>
#include "formmvdevice.h"
#include "queuedialog.h"

#include "libanalog.h"

namespace Ui {
class FormAnalogIn;
}

class FormAnalogIn : public FormMvDevice
{
    Q_OBJECT

public:
    FormAnalogIn(QWidget *parent = nullptr);
    ~FormAnalogIn();
    void keyPressEvent(QKeyEvent *event);
    //void closeEvent(QCloseEvent *event);

    static int stNumFormTypeInstances;

private:
    LibAnalog                   *aInFunctions;
    bool                        USING_WINDOWS = true;

    Ui::FormAnalogIn            *ui;
    AiInputMode                 mAiMode = AI_DIFFERENTIAL;
    AInFlag                     mAiFlags = AIN_FF_DEFAULT;
    QTimer                      *pacerEmulator;
    QTimer                      *oneShotTimer;
    QueueDialog                 *queueSetup;
    QCustomPlot                 *qCustomPlot;

    typedef enum
    {
        AcqStandardMode    = 0,
        AcqFreeScan        = 1 << 0
    }AcquisitionMode;

    typedef enum
    {
        ManualMode  = 0,
        PacedMode   = 1
    }PacingMode;

    QString                     msData;
    int                         mNumScans = 1;
    int                         mChanIndex = 0;
    int                         mNumPacedChans;
    AcquisitionMode             mAcqMode = AcqStandardMode;
    PacingMode                  mPaceMode = ManualMode;
    int                         mPacerInterval = 1;
    int                         mUpdateBlock = 1;

    TempScale                   mTempScale = TS_CELSIUS;
    TInFlag                     mTiFlags = TIN_FF_DEFAULT;
    TInArrayFlag                mTiArrayFlags = TINARRAY_FF_DEFAULT;

    bool                        mRunning = false;
    bool                        mEmulateBurstMode = false;
    int                         mCurFirstChan, mCurLastChan;
    int                         mCurScanCount, mCurChanCount;
    int                         mCurLoopCount;
    TimerJob                    mCurTimerJob;
    int                         oneShotTimeout = 3000;
    bool                        mBreakScan;

    long long                   mPlotIndex;
    long long                   mPlotCount;
    int                         mPrintResolution = 5;
    int                         mHexResolution = 4;
    bool                        mShowHex = false;
    /*
    int                         mFirstChan = 0;
    int                         mLastChan = 0;
    int                         mChanCount = 1;
    long                        mSamplesPerChan;
    long                        mPerChanDisplayed = 5;

    long                        mSampleIndex;
    long                        mPerChanRead;
    bool                        mPlot;
    int                         mPlotChan;
    int                         mPlotOffset = 0;
    QRadioButton                *rbPlotSel[8]={};
    QLabel                      *rbPlotLabels[8]={};
    QLabel                      *rbRangeLabels[8]={};
    QString                     mFontHTML[8];
    QVector<double>             xValues;

    QHash<int, int>             mChanList;
    QHash<int, int>             mRangeList;

    bool                        mDoubleData = true;
    */

    double                      *dblBuffer = NULL;
    int                         *intBuffer = NULL;
    HGLOBAL                     mHandle;
    int                         mBlockSize = 5;
    long                        mScanCountArg;
    long long                   mBufSize = 10;
    long long                   mFinalCount;
    bool                        mDoublePointer = true;

    bool                        mQueueInUse = false;
    QHash<int, int>             mChanTypeList;
    QHash<int, int>             mModeList;
    QHash<int, int>             mResolution;
    QHash<int, double>          mFSRange;
    QHash<int, bool>            mBipolar;
    QHash<int, int>             mDataScale;

    void callClassConstructors();
    void aInStart();
    void aInScanStart();
    void checkScanStatus();
    int aInCheckParameters(QString &params);
    void stopScan();

    void tInStart();
    int tInCheckParameters(QString &params);

    void readInput();
    void inputReadInitialize();
    void iterateLoop();
    void functionIteration();

    void printData();
    void plotData();
    void initializePlotControls();
    void enablePlot(int paramValue);
    void setUiForFunction();
    void setupQueue();
    /*
    void setupPlot();
    void updatePlot();
    */

private slots:
    void cmdStartClicked();
    void cmdStopClicked();
    void singleShotTimeout();
    void intervalTimeout();
    void rateValueChanged(QString newValue);
    void chanValueChanged(int chanVal);
    void queueDialogResponse();
    void showQueueConfig();
    void setPlotXLength();
    void setAutoScale();
    //void plotSelect();

    /*
    void replot();
    */

protected slots:
    void updateIntValue(int paramEnum, int paramValue);
    void updateDevice();
};

#endif // FORMANALOGIN_H
