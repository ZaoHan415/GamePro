#ifndef END_H
#define END_H
#include <QDialog>
#include "ui_win.h"
#include "ui_lose.h"
#include <QMediaPlayer>

class win : public QDialog
{
    Q_OBJECT

public:
    win(QWidget *parent = Q_NULLPTR,int volume = 50);
    ~win();

    QMediaPlayer *winmusic;

private:
    Ui::win ui;

private slots:
    void onSure();
};

class lose : public QDialog
{
    Q_OBJECT

public:
    lose(QWidget *parent = Q_NULLPTR,int volume = 50);
    ~lose();

    QMediaPlayer *losemusic;

private:
    Ui::lose ui;

private slots:
    void onSure();
};
#endif // END_H
