#include "MainWindow.h"
#include <QEvent>
#include <QKeyEvent>
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
}

MainWindow::~MainWindow()
{

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        for(int i = -1;i <= 1; i += 2){
            if(m_scene->cat->turnAroundKey(i) == keyEvent->key()){
                m_scene->cat->change_direction(i);
                return true;

            }
            else if(m_scene->mice->turnAroundKey(i) == keyEvent->key()){
                m_scene->mice->change_direction(i);
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
