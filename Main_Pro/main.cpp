#include "MainController.h"
#include "Control.h"
#include "end.h"
#include <QMediaPlayer>
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainController m;
    m.show();
    return a.exec();

}
