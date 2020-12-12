#include "childwindow.h"
#include "formdiscover.h"

#ifdef USE_AIN
#include "formanalogin.h"
#endif  //USE_AIN
#ifdef USE_AOUT
#include "formanalogout.h"
#endif  //USE_AOUT
#ifdef USE_CFG
#include "formconfig.h"
#endif  //USE_CFG
#ifdef USE_DOUT
#include "formdigitalout.h"
#endif
#ifdef USE_DIN
#include "formdigitalin.h"
#endif

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
#ifdef USE_AIN
        subwidget = new FormAnalogIn(this);
#endif
        msFormTypeName = "ainform";
        break;
    case FORM_AOUT:
        msFormTypeName = "aoutform";
#ifdef USE_AOUT
        subwidget = new FormAnalogOut(this);
#endif
        break;
    case FORM_DIN:
        msFormTypeName = "dinform";
#ifdef USE_DIN
        subwidget = new FormDigitalIn(this);
#endif
        break;
    case FORM_DOUT:
        msFormTypeName = "doutform";
#ifdef USE_DOUT
        subwidget = new FormDigitalOut(this);
#endif
        break;
    case FORM_CTR:
        msFormTypeName = "ctrform";
#ifdef USE_CTR
        subwidget = new FormCounter(this);
#endif
        break;
    case FORM_CONF:
        msFormTypeName = "configform";
#ifdef USE_CFG
        subwidget = new FormConfig(this);
#endif
        break;
    case FORM_MISC:
        msFormTypeName = "miscform";
#ifdef USE_MISC
        subwidget = new FormMvDevice(this);
#endif
        break;
    case FORM_HIST:
        msFormTypeName = "histform";
        break;
    }
    if (subwidget) {
        subwidget->show();
        this->setWidget(subwidget);
        this->adjustSize();
    }
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
