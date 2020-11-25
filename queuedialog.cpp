#include "queuedialog.h"
#include "ui_queuedialog.h"

QueueDialog::QueueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueueDialog)
{
    ui->setupUi(this);
    //int fontSize;
    QFont font;

    //fontSize = 8;
    font.setPointSize(10);

    ui->fraElements->setFont(font);
    ui->fraQParams->setFont(font);
    ui->lstQueue->setStyleSheet("QListWidget { background-color : white; color : blue; }" );

    ui->cmbRange->addItem("BIP20VOLTS", MCC_BIP20VOLTS);
    ui->cmbRange->addItem("BIP10VOLTS", MCC_BIP10VOLTS);
    ui->cmbRange->addItem("BIP5VOLTS", MCC_BIP5VOLTS);
    ui->cmbRange->addItem("BIP4VOLTS", MCC_BIP4VOLTS);
    ui->cmbRange->addItem("BIP2PT5VOLTS", MCC_BIP2PT5VOLTS);
    ui->cmbRange->addItem("BIP2VOLTS", MCC_BIP2VOLTS);
    ui->cmbRange->addItem("BIP1PT25VOLTS", MCC_BIP1PT25VOLTS);
    ui->cmbRange->addItem("BIP1VOLTS", MCC_BIP1VOLTS);
    ui->cmbRange->addItem("BIPPT625VOLTS", MCC_BIPPT625VOLTS);
    ui->cmbRange->addItem("BIPPT312VOLTS", MCC_BIPPT312VOLTS);
    ui->cmbRange->addItem("BIPPT156VOLTS", MCC_BIPPT156VOLTS);
    ui->cmbRange->addItem("BIPPT078VOLTS", MCC_BIPPT078VOLTS);
    ui->cmbRange->addItem("UNI10VOLTS", MCC_UNI10VOLTS);
    ui->cmbRange->addItem("UNI5VOLTS", MCC_UNI5VOLTS);

    if (inputFunctions) {
        ui->cmbChanType->addItem("Standard", 0);
        ui->cmbChanType->addItem("AnalogDiff", DAQI_ANALOG_DIFF);
        ui->cmbChanType->addItem("AnalogSE", DAQI_ANALOG_SE);
        ui->cmbChanType->addItem("Digital", DAQI_DIGITAL);
        ui->cmbChanType->addItem("Counter16", DAQI_CTR16);
        ui->cmbChanType->addItem("Counter32", DAQI_CTR32);
        //ui->cmbChanType->addItem("Counter48", DAQI_CTR48);
        //ui->cmbChanType->addItem("Dac", DAQI_DAC);

        ui->cmbMode->setVisible(true);
        ui->cmbMode->addItem("Differential", AI_DIFFERENTIAL);
        ui->cmbMode->addItem("Single Ended", AI_SINGLE_ENDED);
    } else {
        //ui->cmbChanType->addItem("AnalogOut", DAQO_ANALOG);
        //ui->cmbChanType->addItem("DigitalOut", DAQO_DIGITAL);
        ui->cmbMode->setVisible(false);
    }

    connect(ui->spnQElements, SIGNAL(valueChanged(int)), this, SLOT(updateNumElements(int)));
    connect(ui->lstQueue, SIGNAL(currentRowChanged(int)), this, SLOT(lstQueueRowSelected(int)));
    connect(ui->cmdLoad, SIGNAL(clicked(bool)), this, SLOT(onLoadQueue()));
    connect(this, SIGNAL(numQueueElementsChanged(int)), this, SLOT(updateNumElements(int)));
    connect(ui->cmbChanType, SIGNAL(currentIndexChanged(int)), this, SLOT(chanTypeSelection(int)));
    connect(ui->cmdAutoFill, SIGNAL(clicked(bool)), this, SLOT(autoFill()));
    connect(ui->cmdDelElement, SIGNAL(clicked(bool)), this, SLOT(deleteElement()));
    connect(ui->cmdSave, SIGNAL(clicked(QAbstractButton*)), this, SLOT(dlgDone()));

    ui->cmdLoad->setEnabled(false);
    ui->cmdDelElement->setEnabled(false);
    ui->cmdAutoFill->setEnabled(false);
}

QueueDialog::~QueueDialog()
{
    delete ui;
}

void QueueDialog::updateNumElements(int newNumElements)
{
    int elementsShown = ui->spnQElements->value();
    if (!elementsShown) {
        ui->cmbChanType->setEnabled(true);
        ui->cmbMode->setEnabled(true);
        ui->cmdLoad->setEnabled(false);
    }
    if (!(elementsShown == newNumElements))
        ui->spnQElements->setValue(newNumElements);
    updateQueueList(newNumElements);
    ui->cmdAutoFill->setEnabled(newNumElements > mRangeList.count());
    mNumQueueElements = newNumElements;
}

void QueueDialog::chanTypeSelection(int selection)
{
    ui->cmbMode->setEnabled(!selection);
}

void QueueDialog::updateQueueList(int newNumElements)
{
    int numElements = mChanList.count();
    bool daqParams, itemsRemoved;
    QString elementDescription, modeArg;

    itemsRemoved = (newNumElements < numElements);
    daqParams = true;
    if (inputFunctions)
        //daqParams = (ui->cmbChanType->currentData().toInt() != 0);
        if (mChanTypeList.count() > 0)
            daqParams = (mChanTypeList.value(0) != 0);
    ui->lstQueue->clear();
    for (int i = 0; i < newNumElements; i++) {
        if (i < numElements) {
            if (mChanList.value(i) < 0)
                elementDescription = QString("%1: chan -1, mode, range").arg(i);
            else {
                if (inputFunctions & !daqParams)
                    modeArg = libTestUtils->getAiInputModeName(mModeList.value(i));
                else if (daqParams) {
                    if (inputFunctions)
                        modeArg = libTestUtils->getDaqIChanTypeNames(mChanTypeList.value(i));
                    else
                        modeArg = libTestUtils->getDaqOChanTypeNames(mChanOutTypeList.value(i));
                    ui->cmbMode->setEnabled(false);
                } else {
                    ui->cmbChanType->setEnabled(false);
                }
                elementDescription = QString("%1: chan %2, %3, %4")
                    .arg(i)
                    .arg(mChanList.value(i))
                    .arg(modeArg)
                    .arg(libTestUtils->getRangeName(mRangeList.value(i)));
            }
            ui->lstQueue->addItem(elementDescription);
        } else {
            elementDescription = QString("%1: chan -1, mode, range").arg(i);
            ui->lstQueue->addItem(elementDescription);
            mChanList.insert(i, -1);
        }
    }
    for (int i = newNumElements; i < numElements; i++) {
        mChanList.remove(i);
        mModeList.remove(i);
        mRangeList.remove(i);
    }
    if (itemsRemoved & newNumElements) {
        mNumQueueElements = newNumElements;
        ui->lstQueue->setCurrentRow(newNumElements - 1);
        mCurElement = newNumElements - 1;
    }
    //removed elements with key of "-1"
    mChanList.remove(-1);
    mChanTypeList.remove(-1);
    mChanOutTypeList.remove(-1);
    mModeList.remove(-1);
    mRangeList.remove(-1);
}

void QueueDialog::lstQueueRowSelected(int rowSelected)
{
    mCurElement = rowSelected;
    ui->cmdLoad->setEnabled(!(rowSelected < 0));
    if (!isAutoSet) {
        if (mChanList.count()) {
            if (!(mChanList[mCurElement]<0)) {
                ui->spnQChan->setValue(mChanList[mCurElement]);
                int offset = 0;
                offset = libTestUtils->getDIChanTypeIndex(mChanTypeList[mCurElement]);
                ui->cmbChanType->setCurrentIndex(offset);
                ui->cmbMode->setCurrentIndex(mModeList[mCurElement]-1);
                int listIndex = 1; //getRangeIndex(mRangeList[mCurElement]);
                ui->cmbRange->setCurrentIndex(listIndex);
            }
        }
    }
}

void QueueDialog::onLoadQueue()
{
    int inputMode;
    int elementRange;
    int chanType;
    int chanOutType;
    QString curMode;
    bool daqParams;

    inputMode = AI_DIFFERENTIAL;
    chanType = DAQI_ANALOG_DIFF;
    //chanOutType = DAQO_ANALOG;
    elementRange = ui->cmbRange->currentData(Qt::UserRole).toInt();
    if (inputFunctions) {
        chanType = ui->cmbChanType->currentData(Qt::UserRole).toInt();
        inputMode = ui->cmbMode->currentData(Qt::UserRole).toInt();
    } else {
        chanOutType = ui->cmbChanType->currentData(Qt::UserRole).toInt();
    }
    int chanVal = ui->spnQChan->value();

    daqParams = true;
    if (inputFunctions) {
        daqParams = (ui->cmbChanType->currentIndex());
        ui->cmbChanType->setEnabled(daqParams);
        curMode = libTestUtils->getDaqIChanTypeNames(chanType);
        if (!daqParams)
            curMode = libTestUtils->getAiInputModeName(inputMode);
    } else {
        ui->cmbChanType->setEnabled(true);
        ui->cmbMode->setEnabled(false);
        curMode = libTestUtils->getDaqOChanTypeNames(chanOutType);
    }
    QString curRange = libTestUtils->getRangeName(elementRange);
    QString curElementStr = QString("%1: chan %2, %3, %4")
            .arg(mCurElement)
            .arg(chanVal)
            .arg(curMode)
            .arg(curRange);
    ui->lstQueue->currentItem()->setText(curElementStr);
    mChanList.insert(mCurElement, chanVal);
    mChanTypeList.insert(mCurElement, chanType);
    mChanOutTypeList.insert(mCurElement, chanOutType);
    mModeList.insert(mCurElement, inputMode);
    mRangeList.insert(mCurElement, elementRange);
}

void QueueDialog::autoFill()
{
    int curQSize, curElements, startChan;
    int chanIndex;

    isAutoSet = true;
    int increment = ui->spnAutoInc->value();
    chanIndex = 0;
    curQSize = mRangeList.size();
    //if (curQSize < 0)
    //    curQSize = 0;
    curElements = ui->spnQElements->value();
    startChan = ui->spnQChan->value();
    for (int element = curQSize; element < curElements; element++) {
        ui->spnQChan->setValue(startChan + chanIndex);
        ui->lstQueue->setCurrentRow(element);
        onLoadQueue();
        chanIndex += increment;
    }
    isAutoSet = false;
    ui->cmdAutoFill->setEnabled(false);
}

void QueueDialog::deleteElement()
{
    int selElement;
    int elementCount;

    elementCount = ui->spnQElements->value();
    selElement = ui->lstQueue->currentIndex().row();
    if (!(selElement<0)) {
        mChanList.remove(selElement);
        mModeList.remove(selElement);
        mRangeList.remove(selElement);
        mChanTypeList.remove(selElement);
        mChanOutTypeList.remove(selElement);
    }
    elementCount -= 1;
    updateNumElements(elementCount);
}

void QueueDialog::dlgDone()
{
    int numSet = ui->spnQElements->value();
    mNumQueueElements = numSet;
    //for (int i = numSet; i < mChanList.count(); i++)
    mChanList.remove(-1);
    mChanTypeList.remove(-1);
    mChanOutTypeList.remove(-1);
    mModeList.remove(-1);
    mRangeList.remove(-1);
}
