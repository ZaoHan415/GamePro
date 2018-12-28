#include "MainController.h"
#include "MainWindow.h"
#include "Control.h"

MainWindow *w;
Control *c;

MainController::MainController( QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);

    connect(ui.BButton,SIGNAL(clicked()),this,SLOT(onSureB()));
    connect(ui.SZ,SIGNAL(clicked()),this,SLOT(onSureS()));
    connect(ui.Quit,SIGNAL(clicked()),this,SLOT(onSureQ()));
}

MainController::~MainController()
{

}

void MainController::onSureB()
{
    w = new MainWindow(this);
    w->show();
    this->hide();
}

void MainController::onSureS()
{
    c = new Control(this);
    c->show();
}

void MainController::onSureQ()
{
    accept();
}
