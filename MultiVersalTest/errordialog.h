#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "libTypes.h"
//#include "ulPlatform.h"

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(bool historyCleared READ historyCleared WRITE setHistoryCleared NOTIFY historyClearedChanged)

public:
    explicit ErrorDialog(QWidget *parent = 0);
    ~ErrorDialog();

    void setHistoryCleared(bool historyCleared)
    {
        mHistoryCleared = historyCleared;
        emit historyClearedChanged(historyCleared);
    }

    bool historyCleared() { return mHistoryCleared; }

    //void setError(UlError curError, QString funcText, QString time);
    void addFunction(QString funcString);
    void showHistory();
    void setHistSize(int histSize);
    int getHistSize();

private slots:
    void on_cmdOK_clicked();
    void clearHistory();
    void toggleFilterDisplay();
    void selectFilterItems(QListWidgetItem *lstItem);

private:
#ifdef MV_WINDOWS
    //UlMiscWindows       *miscFunctions;
    bool                USING_WINDOWS = true;
#else
    //UlMiscLinux         *miscFunctions;
    bool                USING_WINDOWS = false;
#endif // OS_WIN32

    Ui::ErrorDialog *ui;
    QStringList mFuncHistoryList;
    QStringList mFilterItems;
    QString getErrorText(int errorNumber);
    int mHistorySize = 0;
    bool mHistoryCleared = false;

    void setFilter();
    void configureFilterSelector();

signals:
    void historyClearedChanged(bool);
};

#endif // ERRORDIALOG_H
