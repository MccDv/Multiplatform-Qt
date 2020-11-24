#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QMdiSubWindow>
#include <QList>
#include "mvEnums.h"
#include "ulTypes.h"

namespace Ui {
class ChildWindow;
}

class ChildWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit ChildWindow(QWidget *parent = 0, FormTypes frmType = FORM_AIN);
    ~ChildWindow();
    void closeEvent(QCloseEvent *event);

    QWidget* getChildForm();
    FormTypes getFormType();
    int getTypeInstance();
    QString getFormTypeName();
    bool isChildClosed();

private:
    QWidget *subwidget;
    FormTypes mFormType;
    int mTypeInstance;
    bool mInstanceClosed = false;

protected:
    QString msFormTypeName;

signals:
    void dataChanged(int paramName, QList<QString>paramList);
};

#endif // CHILDWINDOW_H
