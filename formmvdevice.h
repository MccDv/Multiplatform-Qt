#ifndef FORMMVDEVICE_H
#define FORMMVDEVICE_H

//#include "../ulPlatform.h"
#include "mvErrorMap.h"
#include "qcustomplot.h"

#include "libmisc.h"
#include "libutilities.h"

#include <QMainWindow>
#include <QWidget>
#include <QSettings>
#include <QHash>
#include "libTypes.h"
//#include "mvEnums.h"
//#include "mvtest.h"
#include "libenum.h"

class MvTest;

namespace Ui {
class FormMvDevice;
}

class FormMvDevice : public QWidget
{
    Q_OBJECT

public:
    explicit FormMvDevice(QWidget *parent = nullptr);
    ~FormMvDevice();
    void closeEvent(QCloseEvent *event);

    int getFormInstance();
    void setIntParam(int paramEnum, int paramValue);
    int getIntParam(int paramEnum);
    void setCurDevice(DaqDeviceHandle devHandle, QString uID, QString pID, QString bdName);
    void getCurDevice(DaqDeviceHandle &devHandle, QString &uID, QString &pID, QString &bdName);

private:
    void getAiProperties();
    void getAoProperties();
    void getDevProperties();

protected:
    LibMisc *libMiscFunctions;
    LibUtilities *libTestUtils;

    Ui::FormMvDevice *ui;
    MvTest* getMainWindow();

    QString msUniqueID = "";
    QString msProductID = "";
    QString msDevName = "";
    const QChar plusMinus = 0x00B1;

    DaqDeviceHandle mDevHandle = -1;
    QString msAppName, msFormID;
    QHash<int, int> intParams;

    int mCurFunction;
    int mSubSysResolution;    //generic resolution - depends on form type: aout, ain, dio, etc
    int mAiResolution;
    int mAoResolution;
    int mAoRange;
    int mCurOptions = MCC_SO_DEFAULTIO;
    int mCurIOMode = MCC_SO_DEFAULTIO;
    MccRange mRange = MCC_BIP5VOLTS;

    int                         mFirstChan = 0;
    int                         mLastChan = 0;
    int                         mChanCount = 1;
    long                        mSamplesPerChan;
    long                        mPerChanDisplayed = 8;

    bool                        mPlot;
    int                         mPlotChan;
    int                         mPlotOffset = 0;
    long                        mSampleIndex;
    long                        mPerChanRead;
    QRadioButton                *rbPlotSel[8]={};
    QLabel                      *rbPlotLabels[8]={};
    QLabel                      *rbRangeLabels[8]={};
    QString                     mFontHTML[8];
    QVector<double>             xValues;

    QHash<int, int>             mChanList;
    QHash<int, int>             mRangeList;

    bool                        mDoubleData;

    void setupPlot(QCustomPlot *dataPlot);
    void updatePlot(QCustomPlot *dataPlot, bool autoScale);
    void initPlotCtlProps();
    void replot(QCustomPlot *dataPlot, bool autoScale);
    void plotXLengthConfig(QCustomPlot *dataPlot, bool autoScale);

protected slots:
    //void plotSelect(QCustomPlot *dataPlot, bool autoScale);

signals:
    void intEnumChanged(int paramEnum, int paramValue);
    void deviceChanged();

};

#endif // FORMMVDEVICE_H
