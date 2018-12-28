#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800,600);
    view = new QGraphicsView(this);
    m_scene = new MainGameScene();
    view->setScene(m_scene);
    view->setGeometry(0,0,800,600);
    view->show();
    setFocus();
    setFocusPolicy(Qt::ClickFocus);
    installEventFilter(m_scene);
}

MainWindow::~MainWindow()
{
    QMainWindow* a = static_cast<QMainWindow*>(parent());
    a->show();
}


