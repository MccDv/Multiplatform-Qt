#ifndef FORMDIGITALOUT_H
#define FORMDIGITALOUT_H

#include <QWidget>
#include "formmvdevice.h"
#include "libdigital.h"
#include "digitalutility.h"

namespace Ui {
class FormDigitalOut;
}

class FormDigitalOut : public FormMvDevice
{
    Q_OBJECT

public:
    explicit FormDigitalOut(QWidget *parent = nullptr);
    ~FormDigitalOut();

private:
    Ui::FormDigitalOut *ui;
    LibDigital *digitalFuncs;
    DigitalUtility * digitalUtils;

    int mNumBits = 0;
    int mFirstBit = 0;
    int mLastBit = -1;
    int mNumPorts = 0;
    int mPortIndex = 0;
    int mPortNum = 0;
    int mNumArrayPorts = 0;
    bool mbDoBits = false;
    int mTotalBits = 0;
    QString msPortList;
    int mResolution = 1;
    int mDataValLow = 0;
    int mDataValHigh = 0;

    void callClassConstructors();
    void getPortType();
    bool checkForDigital();
    void configureOutputs(bool setOutputs);
    void configureData();

private slots:
    void updateIntValue(int paramEnum, int paramValue);
    void updateDevice();
    void flashLED();
    void cmdStartClicked();
    void optPortBitClicked();
};

#endif // FORMDIGITALOUT_H
