#include "childwindow.h"
#include "formdiscover.h"
/*
#include "formanalogin.h"
#include "formanalogout.h"
#include "formconfig.h"
#include "formdigitalin.h"
*/
ChildWindow::ChildWindow(QWidget *parent, FormTypes frmType) : QMdiSubWindow(parent)
{
    mFormType = frmType;
    switch (frmType) {
    case FORM_NONE:
    case FORM_DISC:
        subwidget = new FormDiscover(this);
        msFormTypeName = "discoverform";
        break;
    case FORM_AIN:
        //subwidget = new FormAnalogIn(this);
        //msFormTypeName = "ainform";
        break;
    case FORM_AOUT:
        //msFormTypeName = "aoutform";
        //subwidget = new FormAnalogOut(this);
        break;
    case FORM_DIN:
        //msFormTypeName = "dinform";
        //subwidget = new FormDigitalIn(this);
        break;
    case FORM_DOUT:
        //msFormTypeName = "doutform";
        //subwidget = new FormMvDevice(this);
        break;
    case FORM_CTR:
        //msFormTypeName = "ctrform";
        //subwidget = new FormMvDevice(this);
        break;
    case FORM_CONF:
        //msFormTypeName = "configform";
        //subwidget = new FormConfig(this);
        break;
    case FORM_MISC:
        //msFormTypeName = "miscform";
        //subwidget = new FormMvDevice(this);
        break;
    case FORM_HIST:
        msFormTypeName = "histform";
        break;
    }
    subwidget->show();
    this->setWidget(subwidget);
    this->adjustSize();
}

void ChildWindow::closeEvent(QCloseEvent *event)
{
    mInstanceClosed = true;
    event->accept();
}
ChildWindow::~ChildWindow()
{
    subwidget->~QWidget();
}

QWidget* ChildWindow::getChildForm()
{
    return subwidget;
}

FormTypes ChildWindow::getFormType()
{
    return mFormType;
}

QString ChildWindow::getFormTypeName()
{
    return msFormTypeName;
}

int ChildWindow::getTypeInstance()
{
    return mTypeInstance;
}

bool ChildWindow::isChildClosed()
{
    return mInstanceClosed;
}
