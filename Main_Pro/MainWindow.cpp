#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800,600);
    view = new QGraphicsView(this);
    static MainGameScene m_scene;
    view->setScene(&m_scene);
    view->setGeometry(0,0,800,600);
    view->show();
}

MainWindow::~MainWindow()
{

}
