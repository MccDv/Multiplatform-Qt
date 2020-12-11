#include "errordialog.h"
#include "ui_errordialog.h"

#include "libmisc.h"

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    int fontSize;
    QFont font;

    ui->setupUi(this);
    fontSize = 10;
    font.setPointSize(10);

#ifdef Q_OS_MAC
    fontSize = 12;
    font.setPointSize(12);
    this->setFont(font);
#endif

    ui->txtErrList->setFont(QFont ("Courier", fontSize));
    ui->fraListEdit->setFont(font);
    ui->txtErrList->setStyleSheet("QTextEdit { background-color : white; color : blue; }" );

    connect(ui->cmdClearHistory, SIGNAL(clicked(bool)), this, SLOT(clearHistory()));
    connect(ui->lstFilter, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(selectFilterItems(QListWidgetItem*)));
    connect(ui->cmdFilter, SIGNAL(clicked(bool)), this, SLOT(toggleFilterDisplay()));
    mHistorySize = 50;
    mHistoryCleared = false;
    configureFilterSelector();
    ui->lstFilter->setVisible(false);
    mFilterItems.clear();
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog::addFunction(QString funcString)
{
    QString filterString;

    if (mFilterItems.size()) {
        foreach (filterString, mFilterItems) {
            if (funcString.contains(filterString))
                return;
        }
    }
    mFuncHistoryList.append(funcString);
    if (mFuncHistoryList.size() > mHistorySize)
        mFuncHistoryList.removeFirst();
}

void ErrorDialog::showHistory()
{
    LibMisc             *miscFunctions;

    QStringList funcParts;
    QString fStr, bStr, eStr, tStr, errText;
    QString alertHtml = "<font color=\"Red\">";
    QString notifyHtml = "<font color=\"Blue\">";
    QString infoHtml = "<font color=\"Green\">";
    QString endHtml = "</font><br>";
    QString filterString, str;;
    int errVal;
    bool listFunction;

    ui->txtErrList->clear();
    for (int i = (mFuncHistoryList.size()- 1); i >= 0; i--) {
        listFunction = true;
        QString curHist = mFuncHistoryList.value(i);
        funcParts = curHist.split("\n");
        if (funcParts.size() == 4) {
            tStr = funcParts.at(0);
            bStr = funcParts.at(1);
            fStr = funcParts.at(2);
            eStr = funcParts.at(3);
            errVal = eStr.toInt();
            errText = "";
            foreach (filterString, mFilterItems) {
                if (bStr.contains(filterString)) {
                    listFunction = false;
                    break;
                }
            }
            if (listFunction) {
                str.append(notifyHtml + tStr + endHtml);
                str.append(notifyHtml + bStr + endHtml);
                str.append(infoHtml + fStr + endHtml);
            }
            if (errVal != 0) {
                errText = miscFunctions->mccGetUlErrorText(errVal);
                str.append(alertHtml + errText + endHtml);
            }
        } else {
            str.append(curHist);
        }
    }
    ui->txtErrList->setHtml(str);
    ui->lblNumListed->setText(QString("List size: %1").arg(mFuncHistoryList.size()));
}

void ErrorDialog::configureFilterSelector()
{
    QListWidget *filterWidget;

    filterWidget = ui->lstFilter;
    filterWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    filterWidget->clear();

    if (USING_WINDOWS) {
        filterWidget->addItem("cbGetStatus");
    } else {
        filterWidget->addItem("ulAInScanStatus");
        filterWidget->addItem("ulAOutScanStatus");
        filterWidget->addItem("ulDInScanStatus");
        filterWidget->addItem("ulDOutScanStatus");
        filterWidget->addItem("ulCInScanStatus");
        filterWidget->addItem("ulDaqInScanStatus");
        filterWidget->addItem("ulDaqOutScanStatus");
        filterWidget->addItem("ulAIn");
        filterWidget->addItem("ulTIn");
        filterWidget->addItem("ulAOut");
        filterWidget->addItem("ulDIn");
        filterWidget->addItem("ulDOut");
        filterWidget->addItem("ulDBitIn");
        filterWidget->addItem("ulDBitOut");
        filterWidget->addItem("ulCIn");
        filterWidget->addItem("ulCRead");
        filterWidget->addItem("ulTmrPulseOutStatus");
    }
    filterWidget->setVisible(false);
}

void ErrorDialog::selectFilterItems(QListWidgetItem* lstItem)
{
    QString itemText;

    itemText = lstItem->text();
    if (mFilterItems.contains(itemText))
        lstItem->setSelected(false);
    setFilter();
}

void ErrorDialog::setFilter()
{
    mFilterItems.clear();
    foreach (QListWidgetItem *listItem, ui->lstFilter->selectedItems()) {
        QString filterText = listItem->text();
        mFilterItems.append(filterText);
    }
    ui->lblFilter->setText(QString("%1 Item(s)").arg(mFilterItems.count()));
    showHistory();
}

void ErrorDialog::toggleFilterDisplay()
{
    ui->lstFilter->setVisible(!ui->lstFilter->isVisible());
}

void ErrorDialog::clearHistory()
{
    ui->txtErrList->clear();
    mFuncHistoryList.clear();
    mHistoryCleared = true;
}

void ErrorDialog::setHistSize(int histSize)
{
    mHistorySize = histSize;
}

int ErrorDialog::getHistSize()
{
    return mHistorySize;
}

void ErrorDialog::on_cmdOK_clicked()
{
    mHistorySize = ui->leHistSize->text().toInt();
    this->close();
}
