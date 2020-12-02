#include "formdiscover.h"
#include "ui_formdiscover.h"

FormDiscover::FormDiscover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDiscover)
{
    ui->setupUi(this);

    this->setWindowTitle("Device Discovery");
    cDiscover = MvTest::discoveryObj;
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(boardContextMenu(QPoint)));

    connect(ui->cmdDiscover, SIGNAL(clicked(bool)), this, SLOT(refreshDevices()));
    connect(ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(updateDevDetails()));
    connect(ui->cmdConnect, SIGNAL(clicked(bool)), this, SLOT(connectClicked()));
    connect(ui->cmdDisconnect, SIGNAL(clicked(bool)), this, SLOT(disconnectClicked()));
    connect(ui->cmdIsConnected, SIGNAL(clicked(bool)), this, SLOT(isConnectedClicked()));
    updateList();
}

FormDiscover::~FormDiscover()
{
    delete ui;
}

MvTest *FormDiscover::getMainWindow()
{
    foreach (QWidget *w, QApplication::topLevelWidgets())
        if (QMainWindow* mainWin = qobject_cast<QMainWindow*>(w))
            return qobject_cast<MvTest *>(mainWin);
    return nullptr;
}

void FormDiscover::refreshDevices()
{
    QString boardName, uidKey;
    QString params, devsAdded, devsRemoved, temp;
    int err;
    UlNumDevs numFound;
    QHash<QString, DaqDeviceHandle> oldList;
    DaqDeviceHandle devHandle;
    DaqDeviceInterface mInterfaceType = ANY_IFC;
    Qt::CheckState chkNet, chkBTth;

    ui->lblInfo->setText("Detecting devices...");
    QCoreApplication::processEvents();

    chkNet = ui->lstInterface->item(0)->checkState();
    chkBTth = ui->lstInterface->item(1)->checkState();
    mInterfaceType = USB_IFC;
    if (chkNet == Qt::Checked)
        mInterfaceType = (DaqDeviceInterface)(mInterfaceType | ETHERNET_IFC);
    if (chkBTth == Qt::Checked)
        mInterfaceType = (DaqDeviceInterface)(mInterfaceType | BLUETOOTH_IFC);
    oldList = cDiscover->getListedDevices();
    err = cDiscover->updateInventory(params, mInterfaceType, numFound);
    if (err != MCC_NOERRORS) {
        if (params.contains("Error:")) {
            QStringList paramList;
            QString errNum, errText;
            paramList = params.split("@");
            errText = paramList[1];
            errNum = errText.mid(errText.indexOf(":") + 2);
            ui->lblInfo->setText(ulMiscFunctions->mccGetUlErrorText(errNum.toInt()));
            return;
        }
    }
    mnNumDevs = numFound;
    ui->leNumDevs->setText(QString("%1").arg(numFound));
    devList = cDiscover->getListedDevices();

    if (numFound == 0)
        ui->lblInfo->setText
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
            ulDiscFunctions->mccDisconnectDaqDevice(params, devHandle);
            numRemoved++;
        }
    }

    if (numRemoved > 0) {
        devsRemoved.append("DevNums " + temp + " removed");
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
    ui->lblInfo->setText(devsAdded + devsRemoved);
    updateList();
}

void FormDiscover::updateList()
{
    QString uidKey, boardName;

    MvTest *mainForm = getMainWindow();
    mainForm->updateBoardMenu();
    devList = cDiscover->getListedDevices();
    ui->listWidget->clear();
    foreach (int i, devList.values()) {
        uidKey = devList.key(i);
        boardName = cDiscover->getBoardName(uidKey);
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setData(Qt::UserRole, QVariant(uidKey));
        newItem->setText(boardName);
        ui->listWidget->addItem(newItem);
        ui->listWidget->setCurrentItem(newItem);
    }
}

void FormDiscover::updateDevDetails()
{
    QString interfacStr, uniqueIDStr, params;
    QString prodIDStr, devStr;
    QString dStr = "Device string:";
    QString uidStr = "Unique ID:";
    QString pidStr = "Product ID:";
    QString devHdlStr = "Device handle:";
    QString ifcStr = "Interface:";
    QString tableText;
    int connected = 0;
    int err;

    tableText = "<style> th, td { padding-right: 10px;}</style><tr>";
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    if (curItem) {
        uniqueIDStr = curItem->data(Qt::UserRole).toString();
        DaqDeviceInterface devInterface = cDiscover->getDevInterface(uniqueIDStr);
        ui->cmdCreate->setEnabled(true);
        DaqDeviceHandle devHandle = devList.value(uniqueIDStr);

        switch (devInterface) {
        case USB_IFC:
            interfacStr = "USB";
            break;
        case BLUETOOTH_IFC:
            interfacStr = "Bluetooth";
            break;
        case ETHERNET_IFC:
            interfacStr = "Ethernet";
            break;
        case ANY_IFC:
            interfacStr = "All";
            break;
        }

        uint pId = cDiscover->getProductID(uniqueIDStr);

        prodIDStr = QString::number(pId, 16);
        devStr = cDiscover->getDevString(uniqueIDStr);
        devHdlStr = QString("%1").arg(devHandle);
        msCurDevName = cDiscover->getBoardName(uniqueIDStr);

        tableText.append("<td>" + msCurDevName + "</td><td>[" + devHdlStr + "]</td></tr><tr>");
        tableText.append("<td>" + dStr + "</td><td>" + devStr + "</td></tr><tr>");
        tableText.append("<td>" + uidStr + "</td><td>" + uniqueIDStr + "</td></tr><tr>");
        tableText.append("<td>" + pidStr + "</td><td>0x" + prodIDStr + "</td></tr><tr>");
        tableText.append("<td>" + ifcStr + "</td><td>" + interfacStr + "</td></tr><tr>");
        ui->textEdit->setHtml(tableText);

        err = cDiscover->isDeviceConnected(params, devHandle, uniqueIDStr, connected);
        if (err == MCC_NOERRORS) {
            mDevHandle = devHandle;
            msUniqueId = uniqueIDStr;
        }
        ui->cmdCreate->setEnabled(!connected);
        ui->cmdRelease->setEnabled(connected);
        ui->cmdConnect->setEnabled(!connected);
        ui->cmdDisconnect->setEnabled(connected);
    }
}

void FormDiscover::disconnectClicked()
{
    int err, connected;
    QString params;

    err = cDiscover->disconnectDevice(params, mDevHandle);
    if (err != MCC_NOERRORS)
        return;

    err = cDiscover->isDeviceConnected(params, mDevHandle, msUniqueId, connected);
    ui->cmdConnect->setEnabled(!connected);
    ui->cmdDisconnect->setEnabled(connected);
}

void FormDiscover::connectClicked()
{
    int err, connected;
    QString params;

    err = cDiscover->connectDevice(params, mDevHandle, msUniqueId);
    if (err != MCC_NOERRORS)
        return;

    err = cDiscover->isDeviceConnected(params, mDevHandle, msUniqueId, connected);
    ui->cmdConnect->setEnabled(!connected);
    ui->cmdDisconnect->setEnabled(connected);
}

void FormDiscover::createClicked()
{
    DaqDeviceHandle devHandle;
    QString params;
    MccDaqDeviceDescriptor devDescriptor;

    devDescriptor = cDiscover->getDescriptor(msUniqueId);
    devHandle = cDiscover->createDevice(params, mDevHandle, devDescriptor);
    mDevHandle = devHandle;
}

void FormDiscover::isConnectedClicked()
{
    int err, connected;
    QString params, connectStr;

    err = ulDiscFunctions->mccIsDaqDeviceConnected(params, mDevHandle, msUniqueId, connected);
    if (err != MCC_NOERRORS)
        return;
    connectStr = "not connected";
    if (connected)
        connectStr = "connected";
    ui->lblInfo->setText(msCurDevName + QString(" [%1] is " + connectStr));
    ui->cmdConnect->setEnabled(!connected);
    ui->cmdDisconnect->setEnabled(connected);
}

void FormDiscover::boardContextMenu(QPoint listIndex)
{
    msMenuUId = ui->listWidget->indexAt(listIndex).data(Qt::UserRole).toString();
    QMenu *menu = new QMenu(this);
    menu->addAction(new QAction("AIn", this));
    menu->addAction(new QAction("AOut", this));
    menu->addAction(new QAction("Get Info", this));
    menu->popup(ui->listWidget->viewport()->mapToGlobal(listIndex));

    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(openTestForm(QAction*)));
}

void FormDiscover::openTestForm(QAction *menuAction)
{
    QString typeName = menuAction->text();
    MvTest *mainForm = getMainWindow();
    if (typeName == "AIn")
        mainForm->openFormType(FORM_AIN, msMenuUId);
    if (typeName == "Get Info")
        mainForm->openFormType(FORM_CONF, msMenuUId);
}
