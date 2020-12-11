#include "mvtest.h"
#include "ui_mvtest.h"
//#include "libsupport.h"
#include "mvEnums.h"
#include "formmvdevice.h"

/*#include "formanalogin.h"
#include "formdiscover.h"*/

MccDiscover* MvTest::discoveryObj;
ErrorDialog* MvTest::errDialogObj;

MvTest::MvTest(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MvTest)
{
    QString ulVersion, params;

    ui->setupUi(this);
    errDialog = new ErrorDialog(this);
    errDialogObj = errDialog;
    cDiscover = new MccDiscover;
    discoveryObj = cDiscover;
    callClassConstructors();
    mShowWindows = (LIB_PLATFORM == 1);
    mShowLinux = (LIB_PLATFORM == 2);
    mShowRpi = (LIB_PLATFORM == 3);

    msAppName = QApplication::applicationName();
    this->setWindowTitle(msAppName);
    readWindowPosition();
    boardGroup = new QActionGroup(this);
    functionGroup = new QActionGroup(this);
    rangeGroup = new QActionGroup(this);
    ioOptionGroup = new QActionGroup(this);
    scanOptionGroup = new QActionGroup(this);
    flagOptionGroup = new QActionGroup(this);
    aInputModeGroup = new QActionGroup(this);
    plotGroup = new QActionGroup(this);
    QCoreApplication::processEvents();

    if (ui->actionIgnore_Instacal->isChecked())
        cDiscover->ignoreInstacal(params);
    ulVersion = libMiscFunctions->mccGetUlVersion(params);
    ui->lblUlRev->setText("UL Rev: " + ulVersion);

    connect(boardGroup, SIGNAL(triggered(QAction*)), this, SLOT(setCurrentDevice(QAction*)));
    connect(ui->cmdDiscover, SIGNAL(clicked(bool)), this, SLOT(createDiscChild()));
    connect(ui->cmdAIn, SIGNAL(clicked(bool)), this, SLOT(createAInChild()));
    connect(ui->cmdAOut, SIGNAL(clicked(bool)), this, SLOT(createAOutChild()));
    connect(ui->cmdDIn, SIGNAL(clicked(bool)), this, SLOT(createDInChild()));
    connect(ui->cmdDOut, SIGNAL(clicked(bool)), this, SLOT(createDOutChild()));
    connect(ui->cmdCounters, SIGNAL(clicked(bool)), this, SLOT(createCtrChild()));
    connect(ui->cmdMisc, SIGNAL(clicked(bool)), this, SLOT(createMiscChild()));
    connect(ui->cmdConfig, SIGNAL(clicked(bool)), this, SLOT(createConfigChild()));
    connect(ui->cmdHistory, SIGNAL(clicked(bool)), this, SLOT(showHistory()));
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(activeChildChanged(QMdiSubWindow*)));

    configureRangeMenu();
    configureOptionsMenu();
    configureMiscMenus();
    activeChildSetVisibleMenus(FORM_NONE);
    mCurTimerJob = tjInitVars;
    oneShotTimer->start(100);
}

MvTest::~MvTest()
{
    delete ui;
}

void MvTest::keyPressEvent(QKeyEvent *event)
{
    int keyCode = event->key();
    if (keyCode == Qt::Key_F5) {
        mInterfaceType = (DaqDeviceInterface)(USB_IFC | BLUETOOTH_IFC);
        if (ui->actionNetwork_Detect->isChecked()) {
            mInterfaceType = ANY_IFC;
            if (event->modifiers()==Qt::ShiftModifier) {
                //enterRemoteParams();
            }
        }
        refreshDevices();
    }
}

void MvTest::closeEvent(QCloseEvent *event)
{
    QString params;

    foreach(DaqDeviceHandle dev, devList) {
        libDiscFunctions->mccDisconnectDaqDevice(params, dev);
    }

    writeWindowPosition();
    delete cDiscover;
    event->accept();
}

void MvTest::refreshDevices()
{
    QString uidKey;
    QString params, devsAdded, devsRemoved, temp;
    int err;
    UlNumDevs numFound;
    QHash<QString, DaqDeviceHandle> oldList;
    DaqDeviceHandle devHandle;

    ui->lblFunction->setText("Detecting devices...");
    ui->lblError->clear();
    QCoreApplication::processEvents();

    oldList = cDiscover->getListedDevices();
    err = cDiscover->updateInventory(params, mInterfaceType, numFound);
    if (err != MCC_NOERRORS) {
        if (params.contains("Error:")) {
            QStringList paramList;
            QString errNum, errText;
            paramList = params.split("@");
            errText = paramList[1];
            errNum = errText.mid(errText.indexOf(":") + 2);
            ui->lblError->setText(libMiscFunctions->mccGetUlErrorText(errNum.toInt()));
            ui->lblFunction->setText(paramList[0]);
            return;
        }
    }
    mnNumDevs = numFound;
    devList = cDiscover->getListedDevices();

    if (numFound == 0)
        ui->lblFunctionArgs->setText
                ("No devices detected (F5 to detect - File | "
                 "Network Detect for network devices)");
    temp = "";
    int numRemoved = 0;
    foreach (DaqDeviceHandle i, oldList.values()) {
        uidKey = oldList.key(i);
        if (!devList.contains(uidKey)) {
            //removed devices
            devHandle = oldList.value(uidKey);
            temp.append(QString("%1, ").arg(devHandle));
            libDiscFunctions->mccDisconnectDaqDevice(params, devHandle);
            numRemoved++;
        }
    }

    if (numRemoved > 0) {
        devsRemoved.append("  DevNums [" + temp + "] removed");
    }
    temp = "Devs added: ";
    foreach (DaqDeviceHandle i, devList.values()) {
        uidKey = devList.key(i);
        if (!oldList.contains(uidKey)) {
            //added devices
            devsAdded.append(temp + cDiscover->getBoardName(uidKey));
            temp = "; ";
        }
    }
    ui->lblFunction->setText(devsAdded + devsRemoved);
    updateBoardMenu();
}

void MvTest::updateBoardMenu()
{
    QString boardName, uidKey;

    ui->menuBoard->clear();
    if (boardGroup->actions().count())
        boardGroup->actions().clear();
    bool menuSelected = false;
    devList = cDiscover->getListedDevices();
    foreach (int i, devList.values()) {
        uidKey = devList.key(i);
        boardName = cDiscover->getBoardName(uidKey);
        bdAction = ui->menuBoard->addAction(boardName);
        bdAction->setCheckable(true);
        bdAction->setData(uidKey);
        boardGroup->addAction(bdAction);
        if (!menuSelected) {
            bdAction->setChecked(true);
            setCurrentDevice(bdAction);
            menuSelected = true;
        }
    }
}

void MvTest::refreshChildMenu(FormMvDevice *childForm, MenuTypes menuType)
{
    switch (menuType) {
    case MENU_RANGE:
        if (childForm) {
            int curRange = childForm->getIntParam(IPARAM_RANGE);
            foreach (QAction *rangeAction, rangeGroup->actions()) {
                if (rangeAction->data().toInt() == curRange) {
                    rangeAction->setChecked(true);
                    break;
                }
            }
        }
        break;
    case MENU_PLOT:
        if (childForm) {
            int plotType = childForm->getIntParam(IPARAM_PLOTTYPE);
            switch (plotType) {
            case 1:
                ui->actionVolts_vs_Time->setChecked(true);
                break;
            default:
                ui->actionText->setChecked(true);
                break;
            }
        }
        break;
    default:
        break;
    }
}

void MvTest::setCurrentDevice(QAction* curBoardMenu)
{
    QString hexKey, strDevNum;
    unsigned int prodID;
    QList <QString>paramList;

    paramList.clear();
    msUniqueID = curBoardMenu->data().toString();
    mDeviceHandle = devList.value(msUniqueID);
    prodID = cDiscover->getProductID(msUniqueID);
    msProductID = QString("type 0x%1").arg(prodID, 0, 16);
    msBoardName = curBoardMenu->text();
    ui->lblFunctionArgs->setText
            (QString("Current device [%1] %2 (DevType %3)")
             .arg(mDeviceHandle)
             .arg(msBoardName)
             .arg(msProductID));
    setChildDevice();
}

void MvTest::createDiscChild()
{
    FormTypes frmType = FORM_DISC;
    ChildWindow *childWindow = new ChildWindow(ui->mdiArea, frmType);
    childWindow->show();
}

void MvTest::createAInChild()
{
    ui->lblError->clear();
#ifdef USE_AIN
    FormTypes frmType = FORM_AIN;
    ChildWindow *childWindow = new ChildWindow(ui->mdiArea, frmType);
    childWindow->show();
    setChildDevice();
    setChildInt(IPARAM_FUNCTYPE, UL_AIN);
    mCurChild = childWindow;
    mCurTimerJob = tjChildStatus;
    oneShotTimer->start(100);
#else
    ui->lblError->setText("AIn is not defined in project");
#endif
}

void MvTest::createAOutChild()
{
    ui->lblError->clear();
#ifdef USE_AOUT
    FormTypes frmType = FORM_AOUT;
    ChildWindow *childWindow = new ChildWindow(ui->mdiArea, frmType);
    childWindow->show();
    setChildDevice();
    setChildInt(IPARAM_FUNCTYPE, UL_AOUT);
    mCurChild = childWindow;
    mCurTimerJob = tjChildStatus;
    oneShotTimer->start(100);
#else
    ui->lblError->setText("AOut is not defined in project");
#endif
}

void MvTest::createDInChild()
{
    ui->lblError->clear();
#ifdef USE_DIG
    FormTypes frmType = FORM_DIN;
    ChildWindow *childWindow = new ChildWindow(ui->mdiArea, frmType);
    childWindow->show();
    setChildDevice();
    setChildInt(IPARAM_FUNCTYPE, UL_DCONFIG_PORT);
    mCurChild = childWindow;
    mCurTimerJob = tjChildStatus;
    oneShotTimer->start(100);
#else
    ui->lblError->setText("DIO is not defined in project");
#endif
}

void MvTest::createDOutChild()
{
    ui->lblError->clear();
#ifdef USE_DIG
    FormTypes frmType = FORM_DOUT;
    ChildWindow *childWindow = new ChildWindow(ui->mdiArea, frmType);
    childWindow->show();
    setChildDevice();
    setChildInt(IPARAM_FUNCTYPE, UL_DCONFIG_PORT);
    mCurChild = childWindow;
    mCurTimerJob = tjChildStatus;
    oneShotTimer->start(100);
#else
    ui->lblError->setText("DIO is not defined in project");
#endif
}

void MvTest::createCtrChild()
{
    ui->lblError->clear();
#ifdef USE_CTR
    FormTypes frmType = FORM_CTR;
    ChildWindow *childWindow = new ChildWindow(ui->mdiArea, frmType);
    childWindow->show();
    setChildDevice();
    setChildInt(IPARAM_FUNCTYPE, UL_DCONFIG_PORT);
    mCurChild = childWindow;
    mCurTimerJob = tjChildStatus;
    oneShotTimer->start(100);
#else
    ui->lblError->setText("CTR is not defined in project");
#endif
}

void MvTest::createMiscChild()
{
    ui->lblError->clear();
#ifdef USE_MISC
    FormTypes frmType = FORM_MISC;
    ChildWindow *childWindow = new ChildWindow(ui->mdiArea, frmType);
    childWindow->show();
    setChildDevice();
    setChildInt(IPARAM_FUNCTYPE, UL_GET_INFO);
    mCurChild = childWindow;
    mCurTimerJob = tjChildStatus;
    oneShotTimer->start(100);
#else
    ui->lblError->setText("Misc is not defined in project");
#endif
}

void MvTest::createConfigChild()
{
    ui->lblError->clear();
#ifdef USE_CFG
    FormTypes frmType = FORM_CONF;
    ChildWindow *childWindow = new ChildWindow(ui->mdiArea, frmType);
    childWindow->show();
    setChildDevice();
    setChildInt(IPARAM_FUNCTYPE, UL_GET_INFO);
    mCurChild = childWindow;
    mCurTimerJob = tjChildStatus;
    oneShotTimer->start(100);
#else
    ui->lblError->setText("Info is not defined in project");
#endif
}

void MvTest::setChildDevice()
{
    ChildWindow *curChild;

    QMdiSubWindow *activeSub = ui->mdiArea->activeSubWindow();
    curChild = qobject_cast<ChildWindow*>(activeSub);
    if (curChild) {
        if ((curChild->getFormType() != FORM_DISC) & (curChild->getFormType() != FORM_HIST))
            qobject_cast<FormMvDevice*>(curChild->getChildForm())->
                setCurDevice(mDeviceHandle, msUniqueID, msProductID, msBoardName);
    }
}

void MvTest::setChildInt(int paramEnum, int paramValue)
{
    ChildWindow *curChild;
    FormMvDevice *curDevForm;
    FormTypes frmType;

    QMdiSubWindow *activeSub = ui->mdiArea->activeSubWindow();
    curChild = qobject_cast<ChildWindow*>(activeSub);
    if (curChild) {
        frmType = curChild->getFormType();
        if ((frmType == FORM_DISC) | (frmType == FORM_HIST)) {
            return;
        }
        curDevForm = qobject_cast<FormMvDevice*>(curChild->getChildForm());
        curDevForm->setIntParam(paramEnum, paramValue);
    }
}

int MvTest::getChildInt(int paramEnum)
{
    int paramVal = 0;
    ChildWindow *curChild;
    FormMvDevice *curDevForm;
    FormTypes frmType;

    QMdiSubWindow *activeSub = ui->mdiArea->activeSubWindow();
    curChild = qobject_cast<ChildWindow*>(activeSub);
    if (curChild) {
        frmType = curChild->getFormType();
        if ((frmType == FORM_DISC) | (frmType == FORM_HIST)) {
            return 0;
        }
        curDevForm = qobject_cast<FormMvDevice*>(curChild->getChildForm());
        paramVal = curDevForm->getIntParam(paramEnum);
    }
    return paramVal;
}

void MvTest::activeChildChanged(QMdiSubWindow* activeChild)
{
    ChildWindow *curChild;
    FormMvDevice *curDevForm;
    FormTypes curChildType;
    int curFuncSelected, curRangeSelected;

    curChild = qobject_cast<ChildWindow*>(activeChild);
    if (curChild) {
        curChildType = curChild->getFormType();
        if ((curChildType == FORM_DISC) | (curChildType == FORM_HIST)) {
            ui->lblFunctionArgs->setText("");
            return;
        }
        curDevForm = qobject_cast<FormMvDevice*>(curChild->getChildForm());
        curFuncSelected = curDevForm->getIntParam(IPARAM_FUNCTYPE);
        curRangeSelected = curDevForm->getIntParam(IPARAM_RANGE);
        activeChildRefreshDevice(curDevForm);
        activeChildSetVisibleMenus(curChildType);
        activeChildSetFuncMenuProps(curChildType, curFuncSelected);
        mCurChild = curChild;
        mCurTimerJob = tjChildStatus;
        oneShotTimer->start(100);
    } else
        curChildType = FORM_NONE;
    foreach (QAction *rangeAct, rangeGroup->actions()) {
        if (rangeAct->data().toInt() == curRangeSelected) {
            rangeAct->setChecked(true);
            break;
        }
    }
}

void MvTest::activeChildRefreshDevice(FormMvDevice *curDevForm)
{
    DaqDeviceHandle curHandle = 0;
    QString curUID, curPID, curBoardName;

    curDevForm->getCurDevice(curHandle, curUID, curPID, curBoardName);
    if (curHandle == -1) {
        if (!(mDeviceHandle < 0))
            setChildDevice();
        return;
    }
    mDeviceHandle = curHandle;
    msUniqueID = curUID;
    msProductID = curPID;
    msBoardName = curBoardName;
    if (mDeviceHandle < 0)
        ui->lblFunctionArgs->setText("No devices installed");
    else {
        ui->lblFunctionArgs->setText
            (QString("Current device [%1] %2 (DevType %3)")
             .arg(mDeviceHandle)
             .arg(msBoardName)
             .arg(msProductID));
        foreach (QAction *bdMenu, boardGroup->actions()) {
            if (bdMenu->data() == curUID) {
                bdMenu->setChecked(true);
                break;
            }
        }
    }
}

void MvTest::setChildFunction(QAction *curFuncMenu)
{
    int curFuncVal = curFuncMenu->data().toUInt();
    setChildInt(IPARAM_FUNCTYPE, curFuncVal);
}

void MvTest::setChildRange(QAction *curRangeMenu)
{
    int curRange = curRangeMenu->data().toUInt();
    setChildInt(IPARAM_RANGE, curRange);
}

void MvTest::setChildOption(QAction *curOptionMenu)
{
    int curOption = 0;

    mOptions = getChildInt(IPARAM_OPTIONS);
    curOption = curOptionMenu->data().toUInt();
    if (curOption == -1) {
        foreach (QAction *optMenu, scanOptionGroup->actions()) {
            optMenu->setChecked(false);
        }
        mOptions = 0;
    } else {
        if (curOptionMenu->isChecked())
            mOptions |= curOption;
        else
            mOptions ^= curOption;
    }

    setChildInt(IPARAM_OPTIONS, mOptions);
}

void MvTest::setChildIoMode(QAction *curIoOptionMenu)
{
    int mask = 0xFFFFFF ^ (MCC_SO_SINGLEIO | MCC_SO_BLOCKIO
                           | MCC_SO_BLOCKIO | MCC_SO_BURSTIO);
    mOptions = getChildInt(IPARAM_OPTIONS);
    mOptions &= mask;
    int curIoMode = curIoOptionMenu->data().toUInt();
    mOptions |= curIoMode;
    setChildInt(IPARAM_OPTIONS, mOptions);
}

void MvTest::setChildInputMode(QAction *inputModeMenu)
{
    int curInputMode = inputModeMenu->data().toUInt();
    setChildInt(IPARAM_AINMODE, curInputMode);
}

void MvTest::setChildFlags(QAction *aiFlagMenu)
{
    int curFlag = aiFlagMenu->data().toUInt();
    setChildInt(IPARAM_FLAGS, curFlag);
}

void MvTest::setChildTcFlags(bool enableFlag)
{
    int curTcWaitData = (int)enableFlag;
    setChildInt(IPARAM_WAITDATA, curTcWaitData);
}

void MvTest::setChildPlotType(QAction *plotChoice)
{
    int curPlotType = plotChoice->data().toUInt();
    setChildInt(IPARAM_PLOTTYPE, curPlotType);
}

void MvTest::setChildData()
{
    setChildInt(IPARAM_GETDATA, 0);
}

void MvTest::configureRangeMenu()
{
    ui->actionBip4Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionBip4Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionBip2_5Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionBip1_25Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionBip0_625Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionBip0_5Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionBip0_25Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionBip0_2Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionBip0_1Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionBip0_078Volts->setVisible(mShowWindows | mShowLinux);

    ui->actionUni2_5Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionUni10Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionUni5Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionUni4Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionUni2_5Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionUni2Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionUni1_25Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionUni1Volts->setVisible(mShowWindows | mShowLinux);
    ui->actionUni0_625Volts->setVisible(mShowWindows | mShowLinux);

    ui->actionOther_range->setVisible(mShowWindows | mShowLinux);

    ui->actionBip10Volts->setData(MCC_BIP10VOLTS);
    ui->actionBip5Volts->setData(MCC_BIP5VOLTS);
    ui->actionBip4Volts->setData(MCC_BIP4VOLTS);
    ui->actionBip2_5Volts->setData(MCC_BIP2PT5VOLTS);
    ui->actionBip2Volts->setData(MCC_BIP2VOLTS);
    ui->actionBip1_25Volts->setData(MCC_BIP1PT25VOLTS);
    ui->actionBip1Volts->setData(MCC_BIP1VOLTS);
    ui->actionBip0_625Volts->setData(MCC_BIPPT625VOLTS);
    ui->actionBip0_5Volts->setData(MCC_BIPPT5VOLTS);
    ui->actionBip0_25Volts->setData(MCC_BIPPT25VOLTS);
    ui->actionBip0_2Volts->setData(MCC_BIPPT2VOLTS);
    ui->actionBip0_1Volts->setData(MCC_BIPPT1VOLTS);
    ui->actionBip0_078Volts->setData(MCC_BIPPT078VOLTS);

    ui->actionUni10Volts->setData(MCC_UNI10VOLTS);
    ui->actionUni5Volts->setData(MCC_UNI5VOLTS);
    ui->actionUni4Volts->setData(MCC_UNI4VOLTS);
    ui->actionUni2_5Volts->setData(MCC_UNI2PT5VOLTS);
    ui->actionUni2Volts->setData(MCC_UNI2VOLTS);
    ui->actionUni1_25Volts->setData(MCC_UNI1PT25VOLTS);
    ui->actionUni1Volts->setData(MCC_UNI1VOLTS);
    ui->actionUni0_625Volts->setData(MCC_UNIPT625VOLTS);
    ui->actionLoad_Queue->setData(MCC_SETQUEUE);

    rangeGroup->addAction(ui->actionBip10Volts);
    rangeGroup->addAction(ui->actionBip5Volts);
    rangeGroup->addAction(ui->actionBip4Volts);
    rangeGroup->addAction(ui->actionBip2_5Volts);
    rangeGroup->addAction(ui->actionBip2Volts);
    rangeGroup->addAction(ui->actionBip1_25Volts);
    rangeGroup->addAction(ui->actionBip1Volts);
    rangeGroup->addAction(ui->actionBip0_625Volts);
    rangeGroup->addAction(ui->actionBip0_5Volts);
    rangeGroup->addAction(ui->actionBip0_25Volts);
    rangeGroup->addAction(ui->actionBip0_2Volts);
    rangeGroup->addAction(ui->actionBip0_1Volts);
    rangeGroup->addAction(ui->actionBip0_078Volts);
    rangeGroup->addAction(ui->actionLoad_Queue);

    rangeGroup->addAction(ui->actionUni10Volts);
    rangeGroup->addAction(ui->actionUni5Volts);
    rangeGroup->addAction(ui->actionUni4Volts);
    rangeGroup->addAction(ui->actionUni2_5Volts);
    rangeGroup->addAction(ui->actionUni2Volts);
    rangeGroup->addAction(ui->actionUni1_25Volts);
    rangeGroup->addAction(ui->actionUni1Volts);
    rangeGroup->addAction(ui->actionUni0_625Volts);

    connect(rangeGroup, SIGNAL(triggered(QAction*)), this, SLOT(setChildRange(QAction*)));
}

void MvTest::configureOptionsMenu()
{
    QString extTBText, tBaseOutText, pacerOutText;
    QString scaleText, hiResText;
    int extTBInt, tBaseOutInt, pacerOutInt;
    int resRateInt;

    extTBInt = MCC_SO_NOCALIBRATEDATA;
    tBaseOutInt = MCC_SO_TIMEBASEOUT;
    pacerOutInt = MCC_SO_PACEROUT;
    resRateInt = MCC_SO_HIGHRESRATE;

    if (mShowWindows) {
        scaleText = "ScaleData";
        extTBText = "ExtTimebase";
        tBaseOutText = "TimebaseOut";
        pacerOutText = "PacerOut";
        hiResText = "HighResRate";
    } else if (mShowLinux) {
        scaleText = "NoScaleData";
        extTBText = "NoCalibrateData";
        tBaseOutText = "ADCClock";
        pacerOutText = "RetrigMode";
        hiResText = "HighResRate";
        extTBInt = MCC_SO_EXTTIMEBASE;
        tBaseOutInt = MCC_SO_ADCCLOCK;
        pacerOutInt = MCC_SO_RETRIGGER;
        resRateInt = MCC_SO_HIGHRESRATE;
    } else {
        scaleText = "NoScaleData";
        hiResText = "NoCalData";
        resRateInt = MCC_SO_NOCALIBRATEDATA;
        ui->actionScaleData->setChecked(false);
    }

    ui->actionScaleData->setText(scaleText);
    ui->actionExtTimebase->setText(extTBText);
    ui->actionTimebaseOut->setText(tBaseOutText);
    ui->actionPacerOut->setText(pacerOutText);
    ui->actionHighResRate->setText(hiResText);

    ui->actionExtTimebase->setData(extTBInt);
    ui->actionTimebaseOut->setData(tBaseOutInt);
    ui->actionPacerOut->setData(pacerOutInt);
    ui->actionHighResRate->setData(resRateInt);

    ui->actionDefaultIO->setVisible(mShowWindows | mShowLinux);
    ui->actionSingleIO->setVisible(mShowWindows | mShowLinux);
    ui->actionBlockIO->setVisible(mShowWindows | mShowLinux);
    ui->actionBurstIO->setVisible(mShowWindows | mShowLinux);
    ui->actionDMAIo->setVisible(mShowWindows | mShowLinux);
    ui->actionBackground->setVisible(mShowWindows);
    ui->actionADCClockTrig->setVisible(mShowWindows);
    ui->actionNoFilter->setVisible(mShowWindows);
    ui->actionHighResRate->setVisible(mShowWindows | mShowRpi);
    ui->actionConvertData->setVisible(mShowWindows);
    ui->actionWaitForData->setVisible(mShowWindows);
    ui->actionDMAIo->setVisible(mShowWindows);
    ui->actionPacerOut->setVisible(mShowWindows);
    ui->actionTimebaseOut->setVisible(mShowWindows);
    ui->actionExtTimebase->setVisible(mShowWindows);

    ui->actionDefault_Flag->setVisible(mShowWindows | mShowLinux);
    ui->actionNoScaleData_Flag->setVisible(mShowWindows | mShowLinux);
    ui->actionNoCalDataFlag->setVisible(mShowWindows | mShowLinux);

    ui->actionDefaultIO->setData(MCC_SO_DEFAULTIO);
    ui->actionSingleIO->setData(MCC_SO_SINGLEIO);
    ui->actionBlockIO->setData(MCC_SO_BLOCKIO);
    ui->actionBurstIO->setData(MCC_SO_BURSTIO);
    ui->actionDMAIo->setData(MCC_SO_DMAIO);

    ui->actionResetOptions->setData(-1);
    ui->actionContinuous->setData(MCC_SO_CONTINUOUS);
    ui->actionExtClock->setData(MCC_SO_EXTCLOCK);
    ui->actionExtTrigger->setData(MCC_SO_EXTTRIGGER);
    ui->actionBurstMode->setData(MCC_SO_BURSTMODE);
    ui->actionBackground->setData(MCC_SO_BACKGROUND);
    ui->actionScaleData->setData(MCC_SO_SCALEDATA);
    ui->actionConvertData->setData(MCC_SO_CONVERTDATA);
    ui->actionADCClockTrig->setData(MCC_SO_ADCCLOCKTRIG);
    ui->actionNoFilter->setData(MCC_SO_NOFILTER);
    ui->actionWaitForData->setData(MCC_SO_WAITFORNEWDATA);

    ui->actionDefault_Flag->setData(AIN_FF_DEFAULT);
    ui->actionNoScaleData_Flag->setData(AIN_FF_NOSCALEDATA);
    ui->actionNoCalDataFlag->setData(AIN_FF_NOCALIBRATEDATA);

    ui->actionDifferential_Input->setData(AI_DIFFERENTIAL);
    ui->actionSingle_ended_Input->setData(AI_SINGLE_ENDED);
    ui->actionPsuedo_Differential->setData(AI_PSEUDO_DIFFERENTIAL);

    aInputModeGroup->addAction(ui->actionDifferential_Input);
    aInputModeGroup->addAction(ui->actionSingle_ended_Input);
    aInputModeGroup->addAction(ui->actionPsuedo_Differential);

    functionGroup->addAction(ui->actionF1);
    functionGroup->addAction(ui->actionF2);
    functionGroup->addAction(ui->actionF4);
    functionGroup->addAction(ui->actionF3);
    functionGroup->addAction(ui->actionF5);
    functionGroup->addAction(ui->actionF6);
    functionGroup->addAction(ui->actionF7);

    ioOptionGroup->addAction(ui->actionDefaultIO);
    ioOptionGroup->addAction(ui->actionSingleIO);
    ioOptionGroup->addAction(ui->actionBlockIO);
    ioOptionGroup->addAction(ui->actionBurstIO);
    ioOptionGroup->addAction(ui->actionDMAIo);

    scanOptionGroup->addAction(ui->actionResetOptions);
    scanOptionGroup->addAction(ui->actionContinuous);
    scanOptionGroup->addAction(ui->actionBackground);
    scanOptionGroup->addAction(ui->actionExtClock);
    scanOptionGroup->addAction(ui->actionExtTrigger);
    scanOptionGroup->addAction(ui->actionBurstMode);
    scanOptionGroup->addAction(ui->actionExtTimebase);
    scanOptionGroup->addAction(ui->actionTimebaseOut);
    scanOptionGroup->addAction(ui->actionADCClockTrig);
    scanOptionGroup->addAction(ui->actionWaitForData);
    scanOptionGroup->addAction(ui->actionPacerOut);
    scanOptionGroup->addAction(ui->actionNoFilter);
    scanOptionGroup->addAction(ui->actionScaleData);
    scanOptionGroup->addAction(ui->actionHighResRate);
    scanOptionGroup->addAction(ui->actionConvertData);
    scanOptionGroup->setExclusive(false);

    flagOptionGroup->addAction(ui->actionDefault_Flag);
    flagOptionGroup->addAction(ui->actionNoScaleData_Flag);
    flagOptionGroup->addAction(ui->actionNoCalDataFlag);

    connect(ioOptionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setChildIoMode(QAction*)));
    connect(scanOptionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setChildOption(QAction*)));
    connect(aInputModeGroup, SIGNAL(triggered(QAction*)), this, SLOT(setChildInputMode(QAction*)));
    connect(functionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setChildFunction(QAction*)));
    connect(flagOptionGroup, SIGNAL(triggered(QAction*)), this, SLOT(setChildFlags(QAction*)));
    connect(ui->actionWait_for_New_Data, SIGNAL(triggered(bool)), this, SLOT(setChildTcFlags(bool)));
}

void MvTest::configureMiscMenus()
{
    oneShotTimer = new QTimer(this);
    ui->actionText->setData(0);
    ui->actionVolts_vs_Time->setData(1);

    plotGroup->addAction(ui->actionText);
    plotGroup->addAction(ui->actionVolts_vs_Time);

    connect(plotGroup, SIGNAL(triggered(QAction*)), this, SLOT(setChildPlotType(QAction*)));
    connect(oneShotTimer, SIGNAL(timeout()), this, SLOT(singleShotTimeout()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(showSplash()));
    connect(ui->actionData_Selector, SIGNAL(triggered(bool)), this, SLOT(setChildData()));
}

void MvTest::activeChildSetVisibleMenus(FormTypes curChildType)
{
    bool showScanGroup = true;
    bool showFunctions = true;
    bool showOptions = true;
    bool showUtilities = true;

    switch (curChildType) {
    case FORM_NONE:
        showFunctions = false;
        showScanGroup = false;
        showOptions = false;
        showUtilities = false;
        break;
    case FORM_AIN:
        //showFunctions = false;
        break;
    case FORM_CONF:
        showScanGroup = false;
        showOptions = false;
        showUtilities = false;
        break;
    default:
        break;
    }
    //ui->menuFunction->menuAction()->menu()->setVisible(showFunctions);
    /*ui->menuRange->menuAction()->setVisible(showScanGroup);
    ui->menuPlot_Type->menuAction()->setVisible(showScanGroup);
    ui->menuData_Builder->menuAction()->setVisible(showScanGroup);
    ui->menuTriggering->menuAction()->setVisible(showScanGroup);
    ui->menuUtilities->menuAction()->setVisible(showUtilities);
    ui->menuOptions->menuAction()->setVisible(showOptions); */
}

void MvTest::activeChildSetFuncMenuProps(FormTypes curForm, int curFuncSelected)
{
    switch (curForm) {
    case FORM_AIN:
        ui->actionF1->setData(UL_AIN);
        ui->actionF1->setText("AIn");
        ui->actionF2->setData(UL_AINSCAN);
        ui->actionF2->setText("AInScan");
        ui->actionF3->setData(UL_DAQ_INSCAN);
        ui->actionF3->setText("DaqInScan");
        ui->actionF3->setVisible(true);
        ui->actionF4->setData(UL_TIN);
        ui->actionF4->setText("TIn");
        ui->actionF4->setVisible(true);
        ui->actionF5->setData(UL_TINARRAY);
        ui->actionF5->setText("TInArray");
        ui->actionF5->setVisible(true);
        ui->actionF6->setVisible(false);
        ui->actionF7->setVisible(false);
        //ui->actionWait_for_New_Data->setData(TIN_FF_WAIT_FOR_NEW_DATA);
        //ui->actionWait_for_New_Data->setText("WaitForData");
        break;
    case FORM_AOUT:
        ui->actionF1->setData(UL_AOUT);
        ui->actionF1->setText("AOut");
        ui->actionF2->setData(UL_AOUTSCAN);
        ui->actionF2->setText("AOutScan");
        ui->actionF3->setVisible(false);
        ui->actionF4->setVisible(false);
        ui->actionF5->setVisible(false);
        ui->actionF6->setVisible(false);
        ui->actionF7->setVisible(false);
        break;
    case FORM_DIN:
        ui->actionF1->setData(UL_DCONFIG_PORT);
        ui->actionF1->setText("ConfigPort");
        ui->actionF1->setChecked(true);
        ui->actionF2->setData(UL_DCONFIG_BIT);
        ui->actionF2->setText("ConfigBit");
        ui->actionF3->setData(UL_DIN);
        ui->actionF3->setText("DIn");
        ui->actionF4->setData(UL_DIN32);
        ui->actionF4->setText("DIn32");
        ui->actionF4->setVisible(true);
        ui->actionF5->setData(UL_DINARRAY);
        ui->actionF5->setText("DInArray");
        ui->actionF5->setVisible(true);
        ui->actionF6->setData(UL_DBITIN);
        ui->actionF6->setText("DBitIn");
        ui->actionF6->setVisible(true);
        ui->actionF7->setData(UL_DINSCAN);
        ui->actionF7->setText("DInScan");
        ui->actionF7->setVisible(true);
        break;
    case FORM_CONF:
        ui->actionF1->setData(UL_GET_INFO);
        ui->actionF1->setText("GetInfo");
        ui->actionF1->setChecked(true);
        ui->actionF2->setData(UL_GET_CONF);
        ui->actionF2->setText("GetConfig");
        ui->actionF3->setData(UL_SET_CONF);
        ui->actionF3->setText("SetConfig");
        ui->actionF4->setVisible(false);
        ui->actionF5->setVisible(false);
        ui->actionF6->setVisible(false);
        ui->actionF7->setVisible(false);
        break;
    default:
        break;
    }
    foreach (QAction *funcAction, functionGroup->actions()) {
        if (funcAction->data().toInt() == curFuncSelected) {
            funcAction->setChecked(true);
            break;
        }
    }
}

void MvTest::singleShotTimeout()
{
    switch (mCurTimerJob) {
    case tjSplash:
        mTimesUp = true;
        showSplash();
        break;
    case tjChildStatus:
        if (mCurChild) {
            if (mCurChild->isChildClosed()) {
                activeChildSetVisibleMenus(FORM_NONE);
            }
            activeChildChanged(mCurChild);
            mCurChild = NULL;
        }
        break;
    case tjInitVars:
        refreshDevices();
        break;
    default:
        break;
    }
    mCurTimerJob = tjNone;
}

void MvTest::showHistory()
{
    errDialog->setModal(true);
    errDialog->showHistory();
    errDialog->exec();
}

void MvTest::showSplash()
{
    if(!mTimesUp) {
        mCurTimerJob = tjSplash;
        oneShotTimer->setSingleShot(true);
        //oneShotTimer->setInterval(3000);
        QPixmap pixmap(RESOURCE_STRING);
        mSplash = new QSplashScreen(this);
        mSplash->setPixmap(pixmap);
        mSplash->show();
        qApp->processEvents();
        mSplash->activateWindow();
        QColor textColor;
        QString appVer;
        appVer = "Version " + QApplication::applicationVersion() + "            ";
        textColor = "royalblue";
        mSplash->showMessage(appVer, Qt::AlignVCenter | Qt::AlignRight, textColor);
        oneShotTimer->start(3000);
    } else {
        mSplash->close();
        mTimesUp = false;
        //delete mSplash;
        mCurTimerJob = tjNone;
    }
}

void MvTest::readWindowPosition()
{
    QSettings windowSettings("MCC_" + msAppName, QSettings::IniFormat);
    QVariant autoConnect, icalIgnored;

    windowSettings.beginGroup("mainwindow");

    mIgnoreICal = windowSettings.value("ignoreICal", icalIgnored).toBool();
    mDetectNetwork = windowSettings.value("detectNet", icalIgnored).toBool();
    restoreGeometry(windowSettings.value("geometry", saveGeometry()).toByteArray());
    restoreState(windowSettings.value("savestate", saveState()).toByteArray());
    move(windowSettings.value("pos", pos()).toPoint());
    resize(windowSettings.value("size", size()).toSize());
    if (windowSettings.value("maximized", isMaximized()).toBool())
        showMaximized();

    windowSettings.endGroup();
    ui->actionIgnore_Instacal->setChecked(mIgnoreICal);
    ui->actionNetwork_Detect->setChecked(mDetectNetwork);
}

void MvTest::writeWindowPosition()
{
    QVariant icalIgnored, detectNet;

    mIgnoreICal = ui->actionIgnore_Instacal->isChecked();
    mDetectNetwork = ui->actionNetwork_Detect->isChecked();

    icalIgnored = mIgnoreICal;
    detectNet = mDetectNetwork;
    QSettings windowSettings("MCC_" + msAppName, QSettings::IniFormat);

    windowSettings.beginGroup("mainwindow");

    windowSettings.setValue("ignoreICal", icalIgnored);
    windowSettings.setValue("detectNet", detectNet);
    windowSettings.setValue("geometry", saveGeometry());
    windowSettings.setValue("savestate", saveState());
    windowSettings.setValue("maximized", isMaximized());
    if (!isMaximized()) {
        windowSettings.setValue("pos", pos());
        windowSettings.setValue("size", size());
    }
    windowSettings.endGroup();
}

void MvTest::openFormType(FormTypes formType, QString devUId)
{
    switch (formType) {
    case FORM_AIN:
        createAInChild();
        break;
    case FORM_AOUT:
        createAOutChild();
        break;
    case FORM_DIN:
        createDInChild();
        break;
    case FORM_DOUT:
        break;
    case FORM_CTR:
        break;
    case FORM_MISC:
        break;
    case FORM_CONF:
        createConfigChild();
        break;
    default:
        break;
    }
    foreach (QAction *boardMenu, boardGroup->actions()) {
        QString menuID = boardMenu->data().toString();
        if (menuID == devUId) {
            setCurrentDevice(boardMenu);
            break;
        }
    }
}

void MvTest::callClassConstructors()
{
    libMiscFunctions = new LibMisc;
}
