#include "end.h"
#include "MainController.h"
#include "Control.h"
extern Control c;
win::win(QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.w,SIGNAL(clicked()),this,SLOT(onSure()));
}

win::~win()
{

}

void win::onSure()
{
    accept();
}

lose::lose(QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.l,SIGNAL(clicked()),this,SLOT(onSure()));
}

lose::~lose()
{

}

void lose::onSure()
{
    accept();
}
