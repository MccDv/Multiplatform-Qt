#include "formmvdevice.h"
#include "ui_formmvdevice.h"
#include "mvtest.h"
#include "childwindow.h"

FormMvDevice::FormMvDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMvDevice)
{
    ui->setupUi(this);
    msFormID = qobject_cast<ChildWindow*>(parent)->getFormTypeName();
    msAppName = QApplication::applicationName();
}

FormMvDevice::~FormMvDevice()
{
    delete ui;
}

void FormMvDevice::closeEvent(QCloseEvent *event)
{

    event->accept();
}

MvTest* FormMvDevice::getMainWindow()
{
    foreach (QWidget *w, QApplication::topLevelWidgets())
        if (QMainWindow* mainWin = qobject_cast<QMainWindow*>(w))
            return qobject_cast<MvTest *>(mainWin);
    return nullptr;
}

void FormMvDevice::setCurDevice(DaqDeviceHandle devHandle, QString uID, QString pID, QString bdName)
{
    mDevHandle = devHandle;
    msUniqueID = uID;
    msProductID = pID;
    msDevName = bdName;
    if (mDevHandle < 0)
        this->setWindowTitle("No Device");
    else
        this->setWindowTitle(QString("%1  [%2]").arg(bdName).arg(devHandle));
    getDevProperties();
    emit deviceChanged();
}

void FormMvDevice::getCurDevice(DaqDeviceHandle &devHandle, QString &uID, QString &pID, QString &bdName)
{
    devHandle = mDevHandle;
    uID = msUniqueID;
    pID = msProductID;
    bdName = msDevName;
}

void FormMvDevice::setIntParam(int paramEnum, int paramValue)
{
    if (intParams.contains(paramEnum)) {
        if ((paramEnum == IPARAM_RANGE) & (paramValue == MCC_SETQUEUE)) {
            // don't save - just set
            emit intEnumChanged(paramEnum, paramValue);
            return;
        }
        intParams.remove(paramEnum);
        intParams.insert(paramEnum, paramValue);
    } else
        intParams.insert(paramEnum, paramValue);

    emit intEnumChanged(paramEnum, paramValue);

}

int FormMvDevice::getIntParam(int paramEnum)
{
    return intParams.value(paramEnum, 0);
}

void FormMvDevice::initPlotCtlProps()
{
    mFontHTML[0] = " <font color=blue>";
    mFontHTML[1] = " <font color=red>";
    mFontHTML[2] = " <font color=green>";
    mFontHTML[3] = " <font color=cyan>";
    mFontHTML[4] = " <font color=darkCyan>";
    mFontHTML[5] = " <font color=magenta>";
    mFontHTML[6] = " <font color=gray>";
    mFontHTML[7] = " <font color=black>";

    for (int i = 0; i < 8; i++) {
        connect(rbPlotSel[i], SIGNAL(clicked(bool)), this, SLOT(plotSelect()));
        rbPlotSel[i]->setVisible(false);
        rbPlotLabels[i]->setVisible(false);
    }
}

void FormMvDevice::setupPlot(QCustomPlot *dataPlot)
{
    QColor penColor;
    QPalette brushColor;
    int ctlIndex;
    long plotSize;
    int chanCycle;
    int curChanCount;

    xValues.clear();
    plotSize = mPerChanDisplayed;
    xValues.resize(plotSize);
    double *xData = xValues.data();
    for (int smpl = 0; smpl < plotSize; smpl++)
        xData[smpl] = smpl;

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

        if(chanCycle > 7)
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
        dataPlot->graph(ctlIndex)->setVisible(rbPlotSel[ctlIndex]->isChecked());
    }
    for (int i = curChanCount; i < 8; i++) {
        rbPlotSel[i]->setVisible(false);
        rbPlotLabels[i]->setVisible(false);
    }

    dataPlot->axisRect(0)->setAutoMargins(QCP::msLeft|QCP::msBottom);
    dataPlot->axisRect(0)->setMargins(QMargins(0,2,2,0));
    dataPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    dataPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    dataPlot->xAxis->setTickLabelColor(Qt::blue);
    dataPlot->yAxis->setTickLabelColor(Qt::blue);
    dataPlot->xAxis->setRangeLower(0);
    dataPlot->xAxis->setRangeUpper(mPerChanDisplayed - 1);
    dataPlot->replot();
    dataPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    dataPlot->setInteraction(QCP::iRangeDrag, true);
}

void FormMvDevice::updatePlot(QCustomPlot *dataPlot, bool autoScale)
{
    QString params;
    bool setTCRange = false;
    bool bipolar;
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
    dataPlot->xAxis->setRange(rangeLower, rangeUpper);

    //autoScale = ui->rbAutoScale->isChecked();
    if(autoScale) {
        dataPlot->yAxis->rescale(true);
        double center = dataPlot->yAxis->range().center();
        dataPlot->yAxis->scaleRange(1.2, center);
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
            if (!mDoubleData) {
                long fsCount = qPow(2, mSubSysResolution);
                rangeBuf = fsCount / 10;
                rangeUpper = fsCount;
                rangeLower = 0;
            } else {
                bipolar = mRange < 100;
                double rangeVolts = libTestUtils->getRangeVolts(mRange);
                rangeBuf = rangeVolts / 10;
                rangeUpper = bipolar? rangeVolts / 2 : rangeVolts;
                rangeLower = bipolar? rangeUpper * -1 : 0;
            }
        }
        dataPlot->yAxis->setRangeLower(rangeLower - rangeBuf);
        dataPlot->yAxis->setRangeUpper(rangeUpper + rangeBuf);
    }
    dataPlot->replot();
}

void FormMvDevice::replot(QCustomPlot *dataPlot, bool autoScale)
{
    updatePlot(dataPlot, autoScale);
}

/*
void FormMvDevice::plotSelect(QCustomPlot *dataPlot, bool autoScale)
{
    int ctlIndex;

    for (int plotNum = 0; plotNum < mChanCount; plotNum++) {
        ctlIndex = plotNum % 8;
        dataPlot->graph(ctlIndex)->setVisible(rbPlotSel[ctlIndex]->isChecked());
    }
    updatePlot(dataPlot, autoScale);
}
*/

void FormMvDevice::plotXLengthConfig(QCustomPlot *dataPlot, bool autoScale)
{
    mPlotOffset = 0;
    if(mPlot) {
        xValues.resize(mPerChanDisplayed);
        double *xData = xValues.data();
        for (int smpl = 0; smpl < mPerChanDisplayed; smpl++)
            xData[smpl] = smpl;
        updatePlot(dataPlot, autoScale);
        mPerChanRead = 0;
    }
}

void FormMvDevice::getDevProperties()
{
    QString params;
    int err;
    long long configVal = -1;
    int configItem;
    int aiChanCount = 0;
    int aoChanCount = 0;
    QMap<int, QString> infoItems;

    infoItems = libMiscFunctions->mccGetAiInfoItems();
    foreach (QString itemName, infoItems.values()) {
        if (itemName == "0:0:Num Chans") {
            configItem = infoItems.key(itemName);
            break;
        }
    }
    mAiResolution = -1;
    mAoResolution = -1;

    err = libMiscFunctions->mccAiGetInfo(params, mDevHandle, configItem, 0, configVal);
    if (err == MCC_NOERRORS)
        aiChanCount = configVal;
    if (aiChanCount > 0)
        getAiProperties();

    infoItems = libMiscFunctions->mccGetAoInfoItems();
    foreach (QString itemName, infoItems.values()) {
        if (itemName == "0:0:Num Chans") {
            configItem = infoItems.key(itemName);
            break;
        }
    }
    err = libMiscFunctions->mccAoGetInfo(params, mDevHandle, configItem, 0, configVal);
    if (err == MCC_NOERRORS)
        aoChanCount = configVal;
    if (aoChanCount > 0)
        getAoProperties();
}

void FormMvDevice::getAiProperties()
{
    QString params;
    int err;
    long long configVal = -1;
    int configItem;
    QMap<int, QString> infoItems;

    infoItems = libMiscFunctions->mccGetAiInfoItems();
    foreach (QString itemName, infoItems.values()) {
        if (itemName == "0:0:Resolution") {
            configItem = infoItems.key(itemName);
            break;
        }
    }

    err = libMiscFunctions->mccAiGetInfo(params, mDevHandle, configItem, 0, configVal);
    if (err == MCC_NOERRORS)
        mAiResolution = configVal;
}

void FormMvDevice::getAoProperties()
{
    QString params;
    int err;
    long long configVal = -1;
    int resConfigItem, rangeConfigItem;
    QMap<int, QString> infoItems;

    infoItems = libMiscFunctions->mccGetAoInfoItems();
    foreach (QString itemName, infoItems.values()) {
        if (itemName == "0:0:Resolution")
            resConfigItem = infoItems.key(itemName);
        if (itemName == "0:0:Range")
            rangeConfigItem = infoItems.key(itemName);
    }

    err = libMiscFunctions->mccAoGetInfo(params, mDevHandle, resConfigItem, 0, configVal);
    if (err == MCC_NOERRORS)
        mAoResolution = configVal;
    err = libMiscFunctions->mccAoGetInfo(params, mDevHandle, rangeConfigItem, 0, configVal);
    if (err == MCC_NOERRORS)
        mAoRange = configVal;
}
