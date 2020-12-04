#ifndef MVTEST_H
#define MVTEST_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QSettings>
#include <QTimer>
#include <QSplashScreen>
#include <QMenu>

#include "mvEnums.h"
#include "libenum.h"
#include "childwindow.h"
#include "errordialog.h"
#include "mccdiscover.h"

//#include "../remotedialog.h"
//#include "libsupport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MvTest; }
QT_END_NAMESPACE

class FormMvDevice; //forward declaration

class MvTest : public QMainWindow
{
    Q_OBJECT

public:
    MvTest(QWidget *parent = nullptr);
    ~MvTest();
    void keyPressEvent(QKeyEvent *event);

    void closeEvent(QCloseEvent *event);
    static MccDiscover* discoveryObj;
    static ErrorDialog *errDialogObj;

    void openFormType(FormTypes formType, QString devUId);
    void updateBoardMenu();
    void refreshChildMenu(FormMvDevice *childForm, MenuTypes menuType);

private:
    LibMisc *libMiscFunctions;
    LibDiscover *libDiscFunctions;

    Ui::MvTest *ui;
    QSplashScreen *mSplash;
    //RemoteDialog *remoteDialog;
    MccDiscover *cDiscover;
    ErrorDialog *errDialog;
    ChildWindow *mCurChild = NULL;
    bool mWindowsPlatform = false;
    bool mShowWindows, mShowLinux, mShowRpi;

    QTimer *oneShotTimer;

    QAction *bdAction;
    QActionGroup *boardGroup;
    QActionGroup *functionGroup;
    QActionGroup *rangeGroup;
    QActionGroup *ioOptionGroup;
    QActionGroup *scanOptionGroup;
    QActionGroup *flagOptionGroup;
    QActionGroup *plotGroup;
    QActionGroup *aInputModeGroup;

    TimerJob mCurTimerJob;
    bool mIgnoreICal = false;
    bool mDetectNetwork = false;
    bool mTimesUp = false;
    QHash<QString, DaqDeviceHandle> devList;
    int mFontSize;
    unsigned int mnNumDevs;
    int mOptions = 0;
    int mIoOptions = 0;
    DaqDeviceHandle mDeviceHandle= -1;
    DaqDeviceInterface mInterfaceType = (DaqDeviceInterface)(USB_IFC | BLUETOOTH_IFC);
    QString msAppName;
    QString msBoardName, msUniqueID, msProductID, msProductType;

    void callClassConstructors();
    void configureRangeMenu();
    void configureOptionsMenu();
    void configureMiscMenus();
    void refreshDevices();
    void setChildInt(int paramEnum, int paramValue);
    int getChildInt(int paramEnum);
    void activeChildRefreshDevice(FormMvDevice *curDevForm);
    void activeChildSetVisibleMenus(FormTypes curChildType);
    void activeChildSetFuncMenuProps(FormTypes curForm, int curFuncSelected);
    void readWindowPosition();
    void writeWindowPosition();

private slots:
    void singleShotTimeout();
    void showSplash();
    void showHistory();
    void createDiscChild();
    void createAInChild();
    void createAOutChild();
    void createDInChild();
    void createDOutChild();
    void createCtrChild();
    void createMiscChild();
    void createConfigChild();
    void setCurrentDevice(QAction* curBoardMenu);
    void setChildDevice();
    void activeChildChanged(QMdiSubWindow* activeChild);
    void setChildFunction(QAction* curFuncMenu);
    void setChildRange(QAction* curRangeMenu);
    void setChildData();
    void setChildOption(QAction* curOptionMenu);
    void setChildIoMode(QAction* curIoOptionMenu);
    void setChildPlotType(QAction* plotChoice);
    void setChildInputMode(QAction* inputModeMenu);
    void setChildFlags(QAction* aiFlagMenu);
    void setChildTcFlags(bool enableFlag);
};
#endif // MVTEST_H
