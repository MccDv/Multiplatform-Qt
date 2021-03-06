#ifndef FORMDISCOVER_H
#define FORMDISCOVER_H

#include <QWidget>

//#include "../ulPlatform.h"
#include "mccdiscover.h"
//#include "../remotedialog.h"
#include "childwindow.h"
#include "mvEnums.h"
//#include "MvErrorMap.h"
#include "mvtest.h"

namespace Ui {
class FormDiscover;
}

class FormDiscover : public QWidget
{
    Q_OBJECT

public:
    explicit FormDiscover(QWidget *parent = nullptr);
    ~FormDiscover();

private:
    LibMisc *ulMiscFunctions;
    LibDiscover *ulDiscFunctions;

    Ui::FormDiscover *ui;
    MccDiscover *cDiscover;

    unsigned int mnNumDevs;
    DaqDeviceHandle mDevHandle;
    QString msUniqueId, msCurDevName;
    QString msMenuUId;
    QString msProductID;
    QHash<QString, DaqDeviceHandle> devList;

    MvTest *getMainWindow();
    void updateList();

private slots:
    void refreshDevices();
    void updateDevDetails();
    void connectClicked();
    void disconnectClicked();
    void createClicked();
    void isConnectedClicked();
    void boardContextMenu(QPoint listIndex);
    void openTestForm(QAction* menuAction);
    void flashLED();
};

#endif // FORMDISCOVER_H
