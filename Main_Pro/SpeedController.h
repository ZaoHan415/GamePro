#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H
#include <QDialog>
#include <qstring.h>
#include "ui_speedcontroller.h"


class speedcontroller : public QDialog
{
    Q_OBJECT

public:
    speedcontroller(QWidget *parent = Q_NULLPTR);
    ~speedcontroller();
    int catspeed;
    int micespeed;

private:
    Ui::speedcontroller ui;

private slots:
    void onSureSpeed();
    void setcatspeed(int value);
    void setmicespeed(int value);
};
#endif // SPEEDCONTROLLER_H
