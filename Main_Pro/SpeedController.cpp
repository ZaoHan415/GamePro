#include "SpeedController.h"

speedcontroller::speedcontroller(QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);
    ui.catSlider->setMinimum(1);
    ui.catSlider->setMaximum(9);
    ui.catSlider->setValue(5);
    ui.miceSlider->setMinimum(1);
    ui.miceSlider->setMaximum(9);
    ui.miceSlider->setValue(5);

    connect(ui.okButton,SIGNAL(clicked()),this,SLOT(onSureSpeed()));
    connect(ui.catSlider,SIGNAL(valueChanged(int)),this,SLOT(setcatspeed(int)));
    connect(ui.miceSlider,SIGNAL(valueChanged(int)),this,SLOT(setmicespeed(int)));

}

speedcontroller::~speedcontroller()
{
}

void speedcontroller::onSureSpeed()
{
    accept();
}

void speedcontroller::setcatspeed(int /*value*/)
{
    int pos = ui.catSlider->value();
    QString str = QString::number(pos);
    ui.catLabel->setText(str);
    catspeed = pos;
}

void speedcontroller::setmicespeed(int /*value*/)
{
    int pos = ui.miceSlider->value();
    QString str = QString::number(pos);
    ui.miceLabel->setText(str);
    micespeed = pos;
}

