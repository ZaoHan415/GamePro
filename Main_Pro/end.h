#ifndef END_H
#define END_H
#include <QDialog>
#include "ui_win.h"
#include "ui_lose.h"

class win : public QDialog
{
    Q_OBJECT

public:
    win(QWidget *parent = Q_NULLPTR);
    ~win();

private:
    Ui::win ui;

private slots:
    void onSure();
};

class lose : public QDialog
{
    Q_OBJECT

public:
    lose(QWidget *parent = Q_NULLPTR);
    ~lose();

private:
    Ui::lose ui;

private slots:
    void onSure();
};
#endif // END_H
