#ifndef CONTROL_H
#define CONTROL_H

#include <QDialog>
#include <qstring.h>
#include <QThread>
#include "ui_control.h"
#include "ui_rules.h"
#include "ui_people.h"


class Control: public QDialog
{
    Q_OBJECT

public:
    Control(QWidget *parent = Q_NULLPTR);
    ~Control();
    int bgmVolume{50};
    int isVolume{50};
    int catspeed{5};
    int micespeed{50};
    bool Wopen{false};

private:
    Ui::Control ui;

private slots:
    void onSureM();
    void onSureS();
    void onSureP();
    void onSureR();
    void quit();

};

class Rules: public QDialog
{
    Q_OBJECT

public:
    Rules(QWidget *parent = Q_NULLPTR);
    ~Rules();

private:
    Ui::Rules ui;

private slots:
    void onSure();

};

class People: public QDialog
{
    Q_OBJECT

public:
    People(QWidget *parent = Q_NULLPTR);
    ~People();

private:
    Ui::People ui;

private slots:
    void onSure();

};
#endif // CONTROL_H
