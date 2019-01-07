#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MainGameScene.h"
#include <QGraphicsView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    QGraphicsView *view;
    MainGameScene *m_scene;

signals:
    void VolumeSet(int );
    void stop();


};

#endif // MAINWINDOW_H
