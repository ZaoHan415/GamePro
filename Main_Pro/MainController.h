#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QDialog>
#include <QThread>
#include "ui_MainController.h"
#include "MainWindow.h"
#include "Control.h"

class MainController : public QDialog
{
    Q_OBJECT

public:
    MainController( QWidget *parent = Q_NULLPTR );
    ~MainController();
    MainWindow *w;
    Control *c;

private:
    Ui::MainController ui;

private slots:
    void onSureB();
    void onSureS();
    void onSureQ();
};

#endif // MAINCONTROLLER_H
