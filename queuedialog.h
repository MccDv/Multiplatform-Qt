#ifndef QUEUEDIALOG_H
#define QUEUEDIALOG_H

#include <QDialog>

#include "ulenum.h"
#include "libutilities.h"

typedef QHash<int, int> chanListType;
typedef QHash<int, int> modeListType;
typedef QHash<int, int> rangeListType;
typedef QHash<int, int> daqOutChanListType;

namespace Ui {
class QueueDialog;
}

class QueueDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(chanListType chanList READ chanList WRITE setChanList NOTIFY chanListChanged)
    Q_PROPERTY(modeListType modeList READ modeList WRITE setModeList NOTIFY modeListChanged)
    Q_PROPERTY(rangeListType rangeList READ rangeList WRITE setRangeList NOTIFY rangeListChanged)
    Q_PROPERTY(int numQueueElements READ numQueueElements WRITE setNumQueueElements NOTIFY numQueueElementsChanged)
    Q_PROPERTY(daqOutChanListType chanOutTypeList READ chanOutTypeList WRITE setChanOutTypeList NOTIFY chanOutTypeListChanged)

public:
    explicit QueueDialog(QWidget *parent = nullptr);
    ~QueueDialog();

    void setChanList(QHash<int, int> chanList)
    {
        mChanList = chanList;
        emit chanListChanged(chanList);
    }

    void setChanTypeList(QHash<int, int> chanTypeList)
    {
        mChanTypeList = chanTypeList;
        emit chanTypeListChanged(chanTypeList);
    }

    void setChanOutTypeList(QHash<int, int> chanOutTypeList)
    {
        mChanOutTypeList = chanOutTypeList;
        emit chanOutTypeListChanged(chanOutTypeList);
    }

    void setModeList(QHash<int, int> modeList)
    {
        mModeList = modeList;
        emit modeListChanged(modeList);
    }

    void setRangeList(QHash<int, int> rangeList)
    {
        mRangeList = rangeList;
        emit rangeListChanged(rangeList);
    }

    void setNumQueueElements(int numElements)
    {
        mNumQueueElements = numElements;
        emit numQueueElementsChanged(numElements);
    }

    QHash<int, int>             chanList() { return mChanList; }
    QHash<int, int>             modeList() { return mModeList; }
    QHash<int, int>           rangeList() {return mRangeList; }
    QHash<int, int>             chanTypeList() { return mChanTypeList; }
    QHash<int, int>             chanOutTypeList() { return mChanOutTypeList; }
    int numQueueElements () { return mNumQueueElements; }

private slots:
    void updateNumElements(int newNumElements);
    void lstQueueRowSelected(int rowSelected);
    void onLoadQueue();
    void chanTypeSelection(int);
    void autoFill();
    void deleteElement();
    void dlgDone();

private:
    LibUtilities *libTestUtils;

    Ui::QueueDialog *ui;

    QHash<int, int>         mChanList;
    QHash<int, int>         mModeList;
    QHash<int, int>       mRangeList;
    QHash<int, int>         mChanTypeList;
    QHash<int, int>         mChanOutTypeList;
    int mCurElement = 0;
    int mNumQueueElements = 0;
    bool inputFunctions = true;
    bool isAutoSet = false;

    void updateQueueList(int newNumElements);

signals:
    void chanListChanged(QHash<int, int>);
    void chanTypeListChanged(QHash<int, int>);
    void chanOutTypeListChanged(QHash<int, int>);
    void modeListChanged(QHash<int, int>);
    void rangeListChanged(QHash<int, int>);
    void numQueueElementsChanged(int);
};

#endif // QUEUEDIALOG_H
